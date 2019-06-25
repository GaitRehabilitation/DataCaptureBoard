import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_blue/flutter_blue.dart';

class BluetoothSearchRoute extends StatefulWidget {

  @override
  State<StatefulWidget> createState() => new _BluetoothSearchRouteState();
}

class _BluetoothSearchRouteState extends State<BluetoothSearchRoute> {

  FlutterBlue _flutterBlue;
  Map<DeviceIdentifier, BluetoothDevice> _devices = new Map();
  StreamSubscription<ScanResult> _scan;

  _BluetoothSearchRouteState() : super() {
    _flutterBlue = FlutterBlue.instance;
  }

  @override
  void initState() {
    super.initState();
    this._scan = _flutterBlue.scan().listen((scanResult) {
      var device = scanResult.device;
      setState(() {
        _devices.putIfAbsent(device.id, () => device);
      });
    });
  }

  @override
  void deactivate() {
    if (this._scan != null) {
      this._scan.cancel();
    }
    super.deactivate();
  }

  @override
  Widget build(BuildContext context) {
    List<ListTile> tiles = [];
    this._devices.forEach((key, value) {
      tiles.add(_tile(value.name));
    });
    return Scaffold(
        appBar: AppBar(
          title: Text('Bluetooth Devices'),
        ),
        body: Center(child: ListView(children: tiles))
    );
  }

  ListTile _tile(String address) =>
      ListTile(
        title: Text(address,
          style: TextStyle(
              fontWeight: FontWeight.w300,
              fontSize: 20
          ),
        ),
        onTap: () =>
        {
        },
      );
}
