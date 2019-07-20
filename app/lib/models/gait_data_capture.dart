import 'dart:typed_data';

import 'package:app/models/sensor.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'dart:convert';

enum SessionStatus{
  NONE,
  START_LOGGING,
  STOP_LOGGING,
  SET_DESCRIPTION,
  STOPPED_LOGGING
}

class GaitDataCapture extends Sensor {
  static Guid DATA_LOGGER_SERVICE_UUID = Guid("5d0c2b5b-6600-4e2a-8ac9-5e58b794e17b");
  static Guid DATA_LOGGER_CONFIGURE_UUID = Guid("a1c37b04-c732-44b3-8a21-bbc4710feca0");

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

  Uint8List createConfigurePacket(Uint8List payload, SessionStatus status) {
    Uint8List result = new Uint8List(payload.length + 4);
    var view = new ByteData.view(result.buffer);
    // session status
    view.setUint16(0, status.index);
    // size of the payload
    view.setUint16(2, payload.length, Endian.little);
    for(int i = 0; i < payload.length; i++){
      view.setUint8(4 + i,payload[i]);
    }
    return result;
  }

  void stopLogging() async {
    List<int> result = createConfigurePacket(
        new Uint8List(0), SessionStatus.STOP_LOGGING);
    await _configureCharacteristic.write(result);
  }

  void startLogging(String token, String name) async {
    if (token.length > 10) {
      throw Exception("illegal token size is 10");
    }
    token.padRight(10, ' ');
    name += '\0';

    Uint8List namePayload = AsciiEncoder().convert(name);
    Uint8List tokenPayload = AsciiEncoder().convert(token);
    assert(tokenPayload.length == 10);

    Uint8List payload = Uint8List(
        4 + namePayload.length + tokenPayload.length);
    ByteData data = ByteData.view(payload.buffer);
    DateTime time = DateTime.now();
    // epoch
    data.setUint32(0, time.millisecondsSinceEpoch);
    //token payload
    payload.setAll(4, tokenPayload);
    //name of the payload
    payload.setAll(4 + tokenPayload.length, namePayload);

    List<int> result = createConfigurePacket(
        payload, SessionStatus.START_LOGGING).toList();

    await _configureCharacteristic.write(result);
  }
}