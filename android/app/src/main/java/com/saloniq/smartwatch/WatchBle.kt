package com.saloniq.smartwatch
import android.bluetooth.*
import android.content.Context
import android.os.Handler
import android.os.Looper
import java.util.UUID

object WatchBle{
 private val svc=UUID.fromString("6e400001-b5a3-f393-e0a9-e50e24dcca9e")
 private val rx=UUID.fromString("6e400002-b5a3-f393-e0a9-e50e24dcca9e")
 private var gatt:BluetoothGatt?=null
 fun connect(ctx:Context){
  val a=ctx.getSystemService(BluetoothManager::class.java).adapter ?: return
  val s=a.bluetoothLeScanner ?: return
  val cb=object:android.bluetooth.le.ScanCallback(){
   override fun onScanResult(t:Int,r:android.bluetooth.le.ScanResult){
    if(r.device.name=="Saloniq Watch"){s.stopScan(this);gatt=r.device.connectGatt(ctx,false,gattCb,BluetoothDevice.TRANSPORT_LE)}
   }
  }
  s.startScan(cb);Handler(Looper.getMainLooper()).postDelayed({s.stopScan(cb)},10000)
 }
 private val gattCb=object:BluetoothGattCallback(){
  override fun onConnectionStateChange(g:BluetoothGatt,status:Int,state:Int){if(state==BluetoothProfile.STATE_CONNECTED)g.discoverServices()}
 }
 fun send(cmd:String){
  val g=gatt ?: return
  val c=g.getService(svc)?.getCharacteristic(rx) ?: return
  c.writeType=BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE
  c.value=(cmd+"\n").toByteArray()
  g.writeCharacteristic(c)
 }
}
