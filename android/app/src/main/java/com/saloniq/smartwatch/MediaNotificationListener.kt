package com.saloniq.smartwatch
import android.service.notification.NotificationListenerService
import android.service.notification.StatusBarNotification
import android.media.session.*
import android.content.ComponentName
import android.media.MediaMetadata

class MediaNotificationListener:NotificationListenerService(){
 companion object{
  private var active:MediaController?=null
  fun onWatchCommand(cmd:String){
   val c=active?:return
   when(cmd){
    "MEDIA:PLAY"->c.transportControls.play()
    "MEDIA:PAUSE"->c.transportControls.pause()
    "MEDIA:PLAYPAUSE"->if(c.playbackState?.state==PlaybackState.STATE_PLAYING)c.transportControls.pause()else c.transportControls.play()
    "MEDIA:NEXT"->c.transportControls.skipToNext()
    "MEDIA:PREV"->c.transportControls.skipToPrevious()
    "MEDIA:VOLUP","MEDIA:VOLDOWN"->{}
   }
  }
 }
 private lateinit var mgr:MediaSessionManager
 override fun onListenerConnected(){mgr=getSystemService(MediaSessionManager::class.java);update()}
 override fun onNotificationPosted(s:StatusBarNotification){update()}
 private fun update(){
  val list=try{mgr.getActiveSessions(ComponentName(this,MediaNotificationListener::class.java))}catch(e:SecurityException){return}
  val c=list.firstOrNull()?:return
  active=c
  val m=c.metadata?:return
  val t=(m.getString(MediaMetadata.METADATA_KEY_TITLE)?:"Unknown").replace("|","/")
  val a=(m.getString(MediaMetadata.METADATA_KEY_ARTIST)?:"").replace("|","/")
  val p=c.playbackState?.position?:0L
  val d=m.getLong(MediaMetadata.METADATA_KEY_DURATION)
  val state=if(c.playbackState?.state==PlaybackState.STATE_PLAYING)"Playing" else "Paused"
  WatchBle.send("META:$t|$a|$state|$p|$d")
 }
}
