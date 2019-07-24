import 'dart:convert';

import 'package:app/store/app_state.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_redux/flutter_redux.dart';

import 'models/gait_data_capture.dart';
import 'models/sensor.dart';
import 'package:app/helpers.dart';

class HomeState extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => _HomeState();
}

class _HomeState extends State<HomeState>{
  bool isLogging = false;

  List<Widget> _gaitDataCaptureWidget(Sensor sensor) {
    return [TextField(
      controller: sensor.controller.name,
      decoration: InputDecoration(
          border: OutlineInputBorder(),
          labelText: "title"
      ),
      onChanged: (newValue){
        setState(() {});
      },
    ),
      RaisedButton(
        child: Text("Ping"),
        onPressed: () {
          if (sensor is GaitDataCapture) {
            sensor.pingDevice();
          }
        },
      )
    ];
  }

  List<Widget> _panel(Sensor sensor){
    if (sensor is GaitDataCapture) {
      return _gaitDataCaptureWidget(sensor);
    }
    return [];
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Home'),
      ),
      body: Center(
        child:
        Column(
            children: <Widget>[
              StoreConnector<AppState,List<Sensor>>(
                converter: (store) => store.state.sensors,
                builder: (context,List<Sensor> sensors){
                  return ExpansionPanelList(
                    expansionCallback: (int index, bool isExpanded) => setState(() {sensors[index].controller.isExpanded = !isExpanded; }),
                    children: sensors.map<ExpansionPanel>((Sensor sensor) {
                      return ExpansionPanel(
                        headerBuilder: (BuildContext context, bool isExpanded) {
                          return ListTile(
                            trailing: Icon(Icons.delete),
                            title: Text(sensor.controller.name.text),
                            subtitle: Text(sensor.device.id.toString()),
                          );
                        },
                        isExpanded: sensor.controller.isExpanded,
                        body: Column(children: _panel(sensor))
                      );
                    }).toList(),
                  );
                },
              ),
              Align(
                  alignment: Alignment.centerLeft,
                  child: RaisedButton(
                    onPressed: () {
                      Navigator.pushNamed(context, '/search');
                    },
                    child: Text(
                        "Add Sensor"
                    ),
                  )
              ),
              Divider(),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  Expanded(child:
                    RaisedButton(
                      onPressed: ()async {
                        List<Sensor> sensors = StoreProvider
                            .of<AppState>(context)
                            .state
                            .sensors;


                        String tokens = helpers.alphaLower() +
                            helpers.numeric() + helpers.alphaUpper();
                        String group = helpers.generateToken(5, tokens);

                        for (Sensor sensor in sensors) {
                          String name = sensor.controller.name.text;
                          String key = helpers.generateToken(5, tokens);
                          if (sensor is GaitDataCapture) {
                            await sensor.writeName(name);
                            await sensor.startLogging(group + key);
                          }
                        }
                      },
                      child: Text(
                        'Start'
                      ),
                    )
                  ),
                  Expanded(child:
                    RaisedButton(
                      onPressed: ()async {
                        List<Sensor> sensors = StoreProvider
                            .of<AppState>(context)
                            .state
                            .sensors;

                        for (Sensor sensor in sensors) {
                          if (sensor is GaitDataCapture) {
                            await sensor.stopLogging();
                          }
                        }
                      },
                      child: Text(
                        'Stop'
                      ),
                    )
                  )
                ],
              )
            ]
        ),
      ),
    );
  }

}