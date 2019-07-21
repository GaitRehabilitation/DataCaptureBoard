import 'package:app/models/gait_data_capture.dart';
import 'package:app/models/sensor.dart';
import 'package:app/store/app_state.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_redux/flutter_redux.dart';


class SensorList extends StatefulWidget{
  SensorList({Key key}): super(key: key);

  @override
  State<StatefulWidget> createState() => _SensorList();
}

class OnTryConfigure extends Notification {
  const OnTryConfigure();
}

class _SensorList extends State<SensorList> {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return null;
  }
//  @override
//  Widget build(BuildContext context) {
//    return SingleChildScrollView(
//      child: Container(
//        child: _buildPanel(),
//      ),
//    );
//  }
//
//  Widget _buildPanel() {
//    return StoreConnector<AppState, List<Sensor>>(
//        converter: (store) {
//          return store.state.sensors;
//        },
//        builder: (context, List<Sensor> vm) {
//          return ExpansionPanelList(
//              expansionCallback: (int index, bool isExpanded) {
//                setState(() {
//                  vm[index].controller.isExpanded = !isExpanded;
//                });
//              },
//              children:
//              vm.map<ExpansionPanel>((Sensor sensor) {
//                List<Widget> widgets = [];
//
//                // check if gait controller
//                if (sensor.controller is GaitDataCpatureController) {
//                  widgets = _dataCaptureControllerWidgets(sensor);
//                }
//
//                return ExpansionPanel(
//                    headerBuilder: (BuildContext context, bool isExpanded) {
//                      return ListTile(
//                        trailing: Icon(Icons.delete),
//                        title: Text(sensor.device.id.toString()),
//                      );
//                    }, body: Column(
//                  children: widgets,
//                ),
//                    isExpanded: sensor.controller.isExpanded);
//              }).toList()
//          );
//        });
//  }
//
//  List<Widget> _dataCaptureControllerWidgets(Sensor sensor) {
//    GaitDataCpatureController controller = sensor.controller;
//    return [TextField(
//      controller: controller.name,
//      decoration: InputDecoration(
//          border: OutlineInputBorder(),
//          labelText: "title"
//      ),
//    ),
//      RaisedButton(
//        child: Text("Ping"),
//        onPressed: () {
//          if (sensor is GaitDataCapture) {
//            sensor.pingDevice();
//          }
//        },
//      )
//    ];
//  }
}