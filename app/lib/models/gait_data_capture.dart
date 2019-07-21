import 'dart:typed_data';

import 'package:app/models/sensor.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'dart:convert';


enum SessionStatus{
  NONE,
  START_LOGGING,
  STOP_LOGGING,
  PING_LOGGING,
  SET_DESCRIPTION,
  STOPPED_LOGGING
}

class GaitDataCapture extends Sensor {
  static Guid DATA_LOGGER_SERVICE_UUID = Guid("7be194b7-585e-c98a-2a4e-00665b2b0c5d");
  static Guid DATA_LOGGER_CONFIGURE_UUID = Guid("a0ec0f71-c4bb-218a-b344-32c7047bc3a1");
  static Guid DATA_LOGGER_CONFIGURE_NAME_UUID = Guid("43512ebd-c8da-ccb9-a94e-8ce99a8be26a");

  GaitDataCapture(BluetoothDevice device) : super(device){}

  BluetoothCharacteristic _configureCharacteristic = null;
  BluetoothCharacteristic _nameCharacteristic = null;


  @override
  Future<void> connectAndDiscover() async {
    await super.connectAndDiscover();
    BluetoothService service = this.getService(DATA_LOGGER_SERVICE_UUID);
    for(BluetoothCharacteristic characteristic in service.characteristics) {
      if (characteristic.uuid == DATA_LOGGER_CONFIGURE_UUID) {
        _configureCharacteristic = characteristic;
      }
      if (characteristic.uuid == DATA_LOGGER_CONFIGURE_NAME_UUID) {
        _nameCharacteristic = characteristic;
      }
    }
  }

  Uint8List createConfigurePacket(Uint8List payload, SessionStatus status) {
    Uint8List result = new Uint8List(payload.length + 1);
    var view = new ByteData.view(result.buffer);
    // size of the payload
    view.setUint8(0, status.index);
    for(int i = 0; i < payload.length; i++){
      view.setUint8(1 + i,payload[i]);
    }
    return result;
  }

  void stopLogging() async {
    List<int> result = createConfigurePacket(
        new Uint8List(0), SessionStatus.STOP_LOGGING);
    await _configureCharacteristic.write(result);
  }

  void pingDevice() async{
    List<int> result =  createConfigurePacket(Uint8List(0), SessionStatus.PING_LOGGING);
    await _configureCharacteristic.write(result);
  }

  Future<void> writeName(String name) async{
    Uint8List namePayload = AsciiEncoder().convert(name);
    await _nameCharacteristic.write(namePayload);
  }

  Future<void> startLogging(String token) async {
    if (token.length > 10) {
      throw Exception("illegal token size is 10");
    }
    token.padRight(10, ' ');

    Uint8List tokenPayload = AsciiEncoder().convert(token);
    assert(tokenPayload.length == 10);

    Uint8List payload = Uint8List(4 + tokenPayload.length);
    ByteData data = ByteData.view(payload.buffer);
    DateTime time = DateTime.now();
    // epoch
    data.setUint32(0, time.millisecondsSinceEpoch,Endian.little);
    //token payload
    payload.setAll(4, tokenPayload);

    List<int> result = createConfigurePacket(payload, SessionStatus.START_LOGGING).toList();
    await _configureCharacteristic.write(result);
  }
}