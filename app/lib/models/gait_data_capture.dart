import 'dart:typed_data';

import 'package:app/models/sensor.dart';
import 'package:flutter_blue/flutter_blue.dart';

enum SessionStatus{
  NONE,
  START_LOGGING,
  STOP_LOGGING,
  SET_DESCRIPTION,
  STOPPED_LOGGING
}

class GaitDataCapture extends Sensor {
  static Guid DATA_LOGGER_SERVICE_UUID = Guid(
      "5d0c2b5b-6600-4e2a-8ac9-5e58b794e17b");
  static Guid DATA_LOGGER_CONFIGURE_UUID = Guid(
      "a1c37b04-c732-44b3-8a21-bbc4710feca0");

  GaitDataCapture(BluetoothDevice device) : super(device);

  BluetoothCharacteristic _configureCharacteristic = null;

  @override
  void connectAndDiscover() async {
    super.connectAndDiscover();
    BluetoothService service = this.getService(DATA_LOGGER_SERVICE_UUID);
    for(BluetoothCharacteristic characteristic in service.characteristics) {
      if (characteristic.uuid == DATA_LOGGER_CONFIGURE_UUID) {
        _configureCharacteristic = characteristic;
      }
    }
  }

  void createPacket(ByteBuffer buffer, SessionStatus status){
    var view = new ByteData.view(buffer);
    int index = 0;
    view.setUint16(index += 2, status.index);

  }

  void startLogger() {
    Uint8List buffer = new Uint8List(100);

  }
}