#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <NimBLEDevice.h>
#include <IRremote.hpp>
#include "config.h"

Adafruit_ST7789 display(TFT_CS,TFT_DC,TFT_RST);
NimBLECharacteristic* tx=nullptr;
bool connected=false;
String title="Waiting for phone",artist="",playState="Paused";
uint32_t pos=0,dur=0;
int volume=50;
enum Page{HOME,MEDIA,MENU,IR}; Page page=HOME;
int menu=0;

void home(){display.fillScreen(ST77XX_BLACK);display.setTextColor(ST77XX_WHITE);display.setTextSize(4);display.setCursor(28,70);display.printf("%02lu:%02lu",(millis()/3600000UL)%24,(millis()/60000UL)%60);display.setTextSize(1);display.setCursor(8,220);display.printf("BLE %s  VOL %d",connected?"OK":"--",volume);}
String cut(String s,int n){return s.length()<=n?s:s.substring(0,n-1)+"~";}
void media(){display.fillScreen(ST77XX_BLACK);display.setTextColor(ST77XX_WHITE);display.setTextSize(2);display.setCursor(8,8);display.print("MEDIA");display.setCursor(8,45);display.print(cut(title,18));display.setTextSize(1);display.setCursor(8,72);display.print(cut(artist,30));display.setCursor(8,100);display.print(playState);display.drawRect(8,125,224,8,ST77XX_WHITE);if(dur)display.fillRect(8,125,min(224UL,224UL*pos/dur),8,ST77XX_WHITE);display.setCursor(8,160);display.printf("VOL %d%%",volume);display.setCursor(8,200);display.print("UP/DOWN volume  SELECT play");}
void menuPage(){display.fillScreen(ST77XX_BLACK);display.setTextColor(ST77XX_WHITE);display.setTextSize(2);display.setCursor(8,8);display.print("MENU");const char* a[]={"Home","Media","IR Remote","Battery"};for(int i=0;i<4;i++){display.setCursor(12,48+i*38);display.print(i==menu?"> ":"  ");display.print(a[i]);}}
void ir(){display.fillScreen(ST77XX_BLACK);display.setTextColor(ST77XX_WHITE);display.setTextSize(2);display.setCursor(10,10);display.print("IR REMOTE");display.setTextSize(1);display.setCursor(10,55);display.print("Press SELECT to request learning.");display.setCursor(10,75);display.print("Received IR frames are sent to phone.");}
void draw(){if(page==HOME)home();else if(page==MEDIA)media();else if(page==MENU)menuPage();else ir();}
void send(String s){if(connected){s+="\n";tx->setValue(s.c_str());tx->notify();}}
void parse(String s){s.trim();if(s=="MEDIA:PLAY"){playState="Playing";draw();}else if(s=="MEDIA:PAUSE"){playState="Paused";draw();}else if(s=="MEDIA:PLAYPAUSE"){send(playState=="Playing"?"MEDIA:PAUSE":"MEDIA:PLAY");}else if(s=="MEDIA:VOLUP"){volume=min(100,volume+5);draw();}else if(s=="MEDIA:VOLDOWN"){volume=max(0,volume-5);draw();}else if(s.startsWith("META:")){String x=s.substring(5);int a=x.indexOf('|'),b=x.indexOf('|',a+1),c=x.indexOf('|',b+1),d=x.indexOf('|',c+1);if(a>0&&b>a&&c>b&&d>c){title=x.substring(0,a);artist=x.substring(a+1,b);playState=x.substring(b+1,c);pos=x.substring(c+1,d).toInt();dur=x.substring(d+1).toInt();draw();}}else if(s.startsWith("BAT:")){}else if(s=="SCREEN:MEDIA"){page=MEDIA;draw();}else if(s=="SCREEN:HOME"){page=HOME;draw();}}
class ServerCB:public NimBLEServerCallbacks{void onConnect(NimBLEServer*,NimBLEConnInfo&)override{connected=true;draw();}void onDisconnect(NimBLEServer*,NimBLEConnInfo&,int)override{connected=false;NimBLEDevice::startAdvertising();draw();}};
class RxCB:public NimBLECharacteristicCallbacks{void onWrite(NimBLECharacteristic*c,NimBLEConnInfo&)override{String s=c->getValue().c_str();parse(s);}};
void ble(){NimBLEDevice::init(BLE_DEVICE_NAME);auto*s=NimBLEDevice::createServer();s->setCallbacks(new ServerCB());auto*svc=s->createService(BLE_SERVICE_UUID);auto*rx=svc->createCharacteristic(BLE_RX_UUID,NIMBLE_PROPERTY::WRITE|NIMBLE_PROPERTY::WRITE_NR);tx=svc->createCharacteristic(BLE_TX_UUID,NIMBLE_PROPERTY::NOTIFY|NIMBLE_PROPERTY::READ);rx->setCallbacks(new RxCB());svc->start();auto*a=NimBLEDevice::getAdvertising();a->addServiceUUID(BLE_SERVICE_UUID);a->setName(BLE_DEVICE_NAME);a->start();}
bool u=1,d=1,sel=1,b=1;
void setup(){Serial.begin(115200);pinMode(TFT_BL,OUTPUT);digitalWrite(TFT_BL,HIGH);pinMode(BTN_UP,INPUT_PULLUP);pinMode(BTN_DOWN,INPUT_PULLUP);pinMode(BTN_SELECT,INPUT_PULLUP);pinMode(BTN_BACK,INPUT_PULLUP);SPI.begin(TFT_SCLK,-1,TFT_MOSI,TFT_CS);display.init(240,240);display.setRotation(0);ble();IrReceiver.begin(IR_RECV_PIN,ENABLE_LED_FEEDBACK);IrSender.begin(IR_SEND_PIN);draw();}
void loop(){bool nu=digitalRead(BTN_UP),nd=digitalRead(BTN_DOWN),ns=digitalRead(BTN_SELECT),nb=digitalRead(BTN_BACK);if(u&&!nu){if(page==MEDIA)send("MEDIA:VOLUP");else if(page==MENU)menu=(menu+3)%4;draw();}if(d&&!nd){if(page==MEDIA)send("MEDIA:VOLDOWN");else if(page==MENU)menu=(menu+1)%4;draw();}if(sel&&!ns){if(page==HOME)page=MEDIA;else if(page==MEDIA)send("MEDIA:PLAYPAUSE");else if(page==MENU){page=(Page)menu;}else send("IR:LEARN");draw();}if(b&&!nb){page=HOME;draw();}u=nu;d=nd;sel=ns;b=nb;if(IrReceiver.decode()){send(String("IR:RAW:")+String(IrReceiver.decodedIRData.decodedRawData,HEX));IrReceiver.resume();}delay(30);}
