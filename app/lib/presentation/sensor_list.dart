import 'package:app/models/sensor.dart';
import 'package:app/store/app_state.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:redux/redux.dart';


class SensorList extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return StoreConnector<AppState, List<Sensor>>(
        converter: (store) {
          return store.state.sensors;
        },
        builder: (context, vm) {
          List<Widget> tiles = [];
          for (Sensor sensor in vm) {
            tiles.add(_tile(sensor));
          }
          return Column(children: tiles);
        }
    );
  }

  Widget _tile(Sensor sensor) =>
      Text(sensor.deviceId.toString(),
        style: TextStyle(
            fontWeight: FontWeight.w300,
            fontSize: 20
        ),
      );
}

