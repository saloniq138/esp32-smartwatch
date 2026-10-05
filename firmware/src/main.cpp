#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <time.h>
#include <Preferences.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <NimBLEDevice.h>
#include <IRremote.hpp>
#include "config.h"

Adafruit_ST7789 display(TFT_CS,TFT_DC,TFT_RST);
NimBLECharacteristic* tx=nullptr;
Preferences prefs;
bool bleConnected=false, wifiConnected=false;
String title="No media",artist="",playState="Paused";
uint32_t pos=0,dur=0;
int volume=50;
int theme=0, wallpaper=0;

enum Page{HOME,MEDIA,MENU,IR,SETTINGS,WIFI_PAGE,TV_REMOTE}; Page page=HOME;
int menuIndex=0;

const uint16_t BG[4]={ST77XX_BLACK,0x001F,0x7800,0x07E0};
const uint16_t FG[4]={ST77XX_WHITE,ST77XX_WHITE,ST77XX_WHITE,ST77XX_BLACK};

String cut(String s,int n){return s.length()<=n?s:s.substring(0,n-1)+"~";}

void safePrefsBegin(){ static bool started=false; if(!started){prefs.begin("watch",false); started=true;} }
void savePrefs(){safePrefsBegin(); prefs.putInt("theme",theme);prefs.putInt("wall",wallpaper);}
void drawBackground(){display.fillScreen(BG[theme]);if(wallpaper==1){for(int y=0;y<280;y+=20)display.drawFastHLine(0,y,240,FG[theme]);}else if(wallpaper==2){for(int x=0;x<240;x+=20)display.drawFastVLine(x,0,280,FG[theme]);}else if(wallpaper==3){for(int r=10;r<150;r+=25)display.drawCircle(120,140,r,FG[theme]);}}

void home(){
 drawBackground(); display.setTextColor(FG[theme]); display.setTextSize(5); display.setCursor(25,72);
 struct tm t; if(getLocalTime(&t,10)){display.printf("%02d:%02d",t.tm_hour,t.tm_min);}
 else display.printf("--:--");
 display.setTextSize(1);display.setCursor(10,12);display.printf("SALONIQ  %s",wifiConnected?"WiFi":"OFF");
 display.setCursor(10,258);display.printf("BLE:%s  VOL:%d%%",bleConnected?"OK":"--",volume);
}
void media(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("MEDIA");
 display.setCursor(8,45);display.print(cut(title,18));display.setTextSize(1);display.setCursor(8,72);display.print(cut(artist,30));
 display.setCursor(8,98);display.print(playState);display.drawRect(8,125,224,8,FG[theme]);
 if(dur)display.fillRect(8,125,min(224UL,224UL*pos/dur),8,FG[theme]);
 display.setCursor(8,155);display.printf("VOL %d%%",volume);display.setCursor(8,190);display.print("SELECT play  L/R track");
 display.setCursor(8,215);display.print("UP/DOWN volume");
}
void menuPage(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("MENU");
 const char* a[]={"Home","Media","IR Remote","Settings","WiFi","TV Remote"};
 for(int i=0;i<6;i++){display.setCursor(10,42+i*36);display.print(i==menuIndex?"> ":"  ");display.print(a[i]);}
}
void settingsPage(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("SETTINGS");
 display.setTextSize(1);display.setCursor(10,55);display.printf("Theme: %d   Wallpaper: %d",theme+1,wallpaper);
 display.setCursor(10,85);display.print("UP/DOWN: theme");
 display.setCursor(10,105);display.print("LEFT/RIGHT: wallpaper");
 display.setCursor(10,135);display.print("ACTION: save");
 display.setCursor(10,165);display.print("BACK: home");
}
void wifiPage(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("WIFI");
 display.setTextSize(1);display.setCursor(10,55);display.print(wifiConnected?"CONNECTED":"NOT CONNECTED");
 if(wifiConnected){display.setCursor(10,80);display.print(WiFi.localIP());}
 display.setCursor(10,125);display.print("Use Android app to configure");
 display.setCursor(10,145);display.print("SSID/password.");
}
void irPage(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("IR");
 display.setTextSize(1);display.setCursor(10,55);display.print("ACTION = learning request");
 display.setCursor(10,75);display.print("Received IR data goes to phone");
 display.setCursor(10,105);display.print("TV Remote page can store");
 display.setCursor(10,125);display.print("named commands in future.");
}
void tvPage(){
 drawBackground();display.setTextColor(FG[theme]);display.setTextSize(2);display.setCursor(8,8);display.print("TV REMOTE");
 display.setTextSize(1);display.setCursor(10,55);display.print("UP/DOWN channel");
 display.setCursor(10,75);display.print("LEFT/RIGHT volume");
 display.setCursor(10,95);display.print("SELECT power");
 display.setCursor(10,115);display.print("ACTION mute");
}
void draw(){if(page==HOME)home();else if(page==MEDIA)media();else if(page==MENU)menuPage();else if(page==SETTINGS)settingsPage();else if(page==WIFI_PAGE)wifiPage();else if(page==TV_REMOTE)tvPage();else irPage();}

void sendCmd(String s){if(bleConnected){s+="\n";tx->setValue(s.c_str());tx->notify();}}

void parse(String s){
 s.trim();
 if(s=="MEDIA:PLAY"){playState="Playing";draw();}
 else if(s=="MEDIA:PAUSE"){playState="Paused";draw();}
 else if(s=="MEDIA:PLAYPAUSE"){sendCmd(playState=="Playing"?"MEDIA:PAUSE":"MEDIA:PLAY");}
 else if(s=="MEDIA:VOLUP"){volume=min(100,volume+5);draw();}
 else if(s=="MEDIA:VOLDOWN"){volume=max(0,volume-5);draw();}
 else if(s=="SCREEN:MEDIA"){page=MEDIA;draw();}
 else if(s=="SCREEN:HOME"){page=HOME;draw();}
 else if(s.startsWith("WIFI_SSID:")){safePrefsBegin();prefs.putString("ssid",s.substring(10));}\n else if(s.startsWith("WIFI_PASS:")){safePrefsBegin();prefs.putString("pass",s.substring(10));}\n else if(s=="WIFI_CONNECT"){wifiConnectSaved();draw();}\n else if(s.startsWith("THEME:")){theme=constrain(s.substring(6).toInt(),0,3);savePrefs();draw();}
 else if(s.startsWith("WALL:")){wallpaper=constrain(s.substring(5).toInt(),0,3);savePrefs();draw();}
 else if(s.startsWith("META:")){
  String x=s.substring(5);int a=x.indexOf('|'),b=x.indexOf('|',a+1),c=x.indexOf('|',b+1),d=x.indexOf('|',c+1);
  if(a>0&&b>a&&c>b&&d>c){title=x.substring(0,a);artist=x.substring(a+1,b);playState=x.substring(b+1,c);pos=x.substring(c+1,d).toInt();dur=x.substring(d+1).toInt();draw();}
 }
}

class ServerCB:public NimBLEServerCallbacks{
 void onConnect(NimBLEServer*,NimBLEConnInfo&)override{bleConnected=true;draw();}
 void onDisconnect(NimBLEServer*,NimBLEConnInfo&,int)override{bleConnected=false;NimBLEDevice::startAdvertising();draw();}
};
class RxCB:public NimBLECharacteristicCallbacks{void onWrite(NimBLECharacteristic*c,NimBLEConnInfo&)override{parse(c->getValue().c_str());}};

void ble(){
 NimBLEDevice::init(BLE_DEVICE_NAME);auto*s=NimBLEDevice::createServer();s->setCallbacks(new ServerCB());
 auto*svc=s->createService(BLE_SERVICE_UUID);
 auto*rx=svc->createCharacteristic(BLE_RX_UUID,NIMBLE_PROPERTY::WRITE|NIMBLE_PROPERTY::WRITE_NR);
 tx=svc->createCharacteristic(BLE_TX_UUID,NIMBLE_PROPERTY::NOTIFY|NIMBLE_PROPERTY::READ);
 rx->setCallbacks(new RxCB());svc->start();auto*a=NimBLEDevice::getAdvertising();a->addServiceUUID(BLE_SERVICE_UUID);a->setName(BLE_DEVICE_NAME);a->start();
}
void wifiConnectSaved(){
 safePrefsBegin();theme=prefs.getInt("theme",0);wallpaper=prefs.getInt("wall",0);
 String ssid=prefs.getString("ssid",""),pass=prefs.getString("pass","");
 if(ssid.length()){WiFi.mode(WIFI_STA);WiFi.setHostname(WIFI_HOSTNAME);WiFi.begin(ssid.c_str(),pass.c_str());for(int i=0;i<30&&WiFi.status()!=WL_CONNECTED;i++)delay(250);wifiConnected=WiFi.status()==WL_CONNECTED;}
 configTime(3600,3600,"pool.ntp.org","time.nist.gov");
}
void setup(){
 Serial.begin(115200);
 safePrefsBegin();pinMode(TFT_BL,OUTPUT);digitalWrite(TFT_BL,HIGH);
 pinMode(BTN_UP,INPUT_PULLUP);pinMode(BTN_DOWN,INPUT_PULLUP);pinMode(BTN_LEFT,INPUT_PULLUP);pinMode(BTN_RIGHT,INPUT_PULLUP);
 pinMode(BTN_SELECT,INPUT_PULLUP);pinMode(BTN_BACK,INPUT_PULLUP);pinMode(BTN_MENU,INPUT_PULLUP);pinMode(BTN_ACTION,INPUT_PULLUP);
 SPI.begin(TFT_SCLK,-1,TFT_MOSI,TFT_CS);display.init(240,280);display.setRotation(0);
 wifiConnectSaved();ble();IrReceiver.begin(IR_RECV_PIN,ENABLE_LED_FEEDBACK);IrSender.begin(IR_SEND_PIN);draw();
}
bool last[8]={1,1,1,1,1,1,1,1};
int pins[8]={BTN_UP,BTN_DOWN,BTN_LEFT,BTN_RIGHT,BTN_SELECT,BTN_BACK,BTN_MENU,BTN_ACTION};

void loop(){
 bool now[8];for(int i=0;i<8;i++)now[i]=digitalRead(pins[i]);
 if(last[0]&&!now[0]){if(page==MEDIA)sendCmd("MEDIA:VOLUP");else if(page==MENU)menuIndex=(menuIndex+5)%6;else if(page==SETTINGS)theme=(theme+1)%4;else if(page==TV_REMOTE)sendCmd("IR:TV:CHUP");draw();}
 if(last[1]&&!now[1]){if(page==MEDIA)sendCmd("MEDIA:VOLDOWN");else if(page==MENU)menuIndex=(menuIndex+1)%6;else if(page==SETTINGS)theme=(theme+3)%4;else if(page==TV_REMOTE)sendCmd("IR:TV:CHDOWN");draw();}
 if(last[2]&&!now[2]){if(page==MEDIA)sendCmd("MEDIA:PREV");else if(page==SETTINGS)wallpaper=(wallpaper+3)%4;else if(page==TV_REMOTE)sendCmd("IR:TV:VOLDOWN");draw();}
 if(last[3]&&!now[3]){if(page==MEDIA)sendCmd("MEDIA:NEXT");else if(page==SETTINGS)wallpaper=(wallpaper+1)%4;else if(page==TV_REMOTE)sendCmd("IR:TV:VOLUP");draw();}
 if(last[4]&&!now[4]){if(page==HOME)page=MEDIA;else if(page==MEDIA)sendCmd("MEDIA:PLAYPAUSE");else if(page==MENU){switch(menuIndex){case 0:page=HOME;break;case 1:page=MEDIA;break;case 2:page=IR;break;case 3:page=SETTINGS;break;case 4:page=WIFI_PAGE;break;case 5:page=TV_REMOTE;break;}}else if(page==IR)sendCmd("IR:LEARN");else if(page==SETTINGS){savePrefs();}else if(page==TV_REMOTE)sendCmd("IR:TV:POWER");draw();}
 if(last[5]&&!now[5]){page=HOME;draw();}
 if(last[6]&&!now[6]){page=MENU;draw();}
 if(last[7]&&!now[7]){if(page==IR)sendCmd("IR:LEARN");else if(page==TV_REMOTE)sendCmd("IR:TV:MUTE");else if(page==SETTINGS)savePrefs();draw();}
 for(int i=0;i<8;i++)last[i]=now[i];
 if(IrReceiver.decode()){sendCmd(String("IR:RAW:")+String(IrReceiver.decodedIRData.decodedRawData,HEX));IrReceiver.resume();}
 delay(30);
}
