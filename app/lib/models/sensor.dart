import 'package:flutter/cupertino.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'dart:developer' as developer;

class SensorController {
  SensorController();
  bool isExpanded = false;
  TextEditingController name = new TextEditingController();
}

abstract class Sensor {
  BluetoothDevice _device = null;
  Map<Guid,BluetoothService> _services = Map();
  final SensorController controller = new SensorController();
  Sensor(BluetoothDevice device): _device = device;

  Future<void> connectAndDiscover() async{
    await _device.connect();
    List<BluetoothService> services = await _device.discoverServices();
    for(BluetoothService service in services){
      Guid uuid = service.uuid;
      developer.log("device: $deviceId discover-serivce: $uuid");
      this._services.putIfAbsent(uuid, () => service);
    }
  }

  void disconnect(){
    _device.disconnect();
  }

  bool hasService(Guid uuid){
    return _services.containsKey(uuid);
  }


  BluetoothService getService(Guid uuid){
    return _services[uuid];
  }

  BluetoothDevice get device{
    return _device;
  }

  get deviceId{
    return _device.id;
  }

  @override
  String toString() => "Sensor(id: $deviceId)";

}