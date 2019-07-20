import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';

typedef void OnPressed(BluetoothDevice);

class BluetoothDeviceList extends StatefulWidget {
  final OnPressed onPressed;
  final List<DeviceIdentifier> blacklist;
  final Stream<ScanResult> stream;

  BluetoothDeviceList({key: Key, this.onPressed, this.blacklist, this.stream})
      : super(key: key);

  @override
  State<StatefulWidget> createState() => _BluetoothDeviceListState();
}

class _BluetoothDeviceListState extends State<BluetoothDeviceList> {
  Map<DeviceIdentifier, BluetoothDevice> _devices = new Map();
  StreamSubscription<ScanResult> _streamSubscription;

  @override
  void initState() {
    super.initState();
    this._streamSubscription =  widget.stream.listen((scanResult){
      var device = scanResult.device;
      setState(() {
        _devices.putIfAbsent(device.id, () => device);
      });
    });
  }

  @override
  void deactivate() async {
    super.deactivate();
    await _streamSubscription.cancel();
  }

  ListTile _tile(BluetoothDevice device) {
    String name = device.name;
    DeviceIdentifier identifier = device.id;
    return ListTile(
      title: Text("$identifier ($name)",
        style: TextStyle(
            fontWeight: FontWeight.w300,
            fontSize: 20
        ),
      ),
      onTap: () {
        this.widget.onPressed(device);
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    List<ListTile> tiles = [];
    this._devices.forEach((key, value) {
//      if(!identifiers.contains(key)) {
        tiles.add(_tile(value));
//      }
    });
    return ListView(children: <Widget>[]);
  }

}