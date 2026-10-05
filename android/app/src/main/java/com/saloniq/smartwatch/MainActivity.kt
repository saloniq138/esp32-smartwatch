package com.saloniq.smartwatch
import android.Manifest
import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

class MainActivity:AppCompatActivity(){
 override fun onCreate(b:Bundle?){super.onCreate(b)
  val l=LinearLayout(this).apply{orientation=LinearLayout.VERTICAL;setPadding(24,24,24,24)}
  val status=TextView(this).apply{text="Saloniq Watch\nNot connected";textSize=20f}
  l.addView(status)
  l.addView(Button(this).apply{text="Connect";setOnClickListener{WatchBle.connect(this@MainActivity);status.text="Scanning for Saloniq Watch…"}})
  l.addView(Button(this).apply{text="Enable media access";setOnClickListener{startActivity(Intent("android.settings.ACTION_NOTIFICATION_LISTENER_SETTINGS"))}})
  val r=LinearLayout(this)
  listOf("Previous" to "MEDIA:PREV","Play/Pause" to "MEDIA:PLAYPAUSE","Next" to "MEDIA:NEXT").forEach{(t,c)->r.addView(Button(this).apply{text=t;setOnClickListener{WatchBle.send(c)}})}
  l.addView(r);setContentView(l)
  if(Build.VERSION.SDK_INT>=31)requestPermissions(arrayOf(Manifest.permission.BLUETOOTH_SCAN,Manifest.permission.BLUETOOTH_CONNECT),10)
 }
}
