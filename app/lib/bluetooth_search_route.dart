import 'dart:async';

import 'package:app/store/app_state.dart';
import 'package:app/store/sensors_state_reducer.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:flutter_redux/flutter_redux.dart';

import 'models/gait_data_capture.dart';
import 'models/sensor.dart';

class BluetoothSearchRoute extends StatefulWidget {

  @override
  State<StatefulWidget> createState() => new _BluetoothSearchRouteState();
}

typedef AddSensorCallback = void Function(Sensor sensor);

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
    _flutterBlue.stopScan();
    super.deactivate();
  }

  @override
  Widget build(BuildContext context) {
    return StoreConnector<AppState,_modelView>(
      converter: (store) {
        return _modelView(
          sensorCallback: (Sensor sensor) => store.dispatch(AddSensorAction(sensor)),
          sensors: store.state.sensors
        );
      },
      builder: (context,mv){
        List<DeviceIdentifier> identifiers = [];
        for(Sensor s in mv.sensors){
          identifiers.add(s.device.id);
        }
        List<ListTile> tiles = [];
        this._devices.forEach((key, value) {
          if(!identifiers.contains(key)) {
            tiles.add(_tile(value, mv.sensorCallback));
          }
        });
        return Scaffold(
            appBar: AppBar(
              title: Text('Bluetooth Devices'),
            ),
            body:  Center(child: ListView(children: tiles))
        );
      },
    );
  }

  ListTile _tile(BluetoothDevice device,AddSensorCallback callback) {
    String name = device.name;
    DeviceIdentifier identifier = device.id;
    return ListTile(
      title: Text("$identifier ($name)",
        style: TextStyle(
            fontWeight: FontWeight.w300,
            fontSize: 20
        ),
      ),
      onTap: () async {
        GaitDataCapture capture = GaitDataCapture(device);
        await capture.connectAndDiscover();
        callback(capture);
        Navigator.pop(context);
      },
    );
  }
}

class _modelView{
  final AddSensorCallback sensorCallback;
  List<Sensor> sensors;
  _modelView({
    this.sensorCallback,
    this.sensors
  });
}
