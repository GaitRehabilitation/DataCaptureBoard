import 'package:app/presentation/sensor_list.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';

class HomeState extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return Scaffold(
      appBar: AppBar(
        title: Text('Home'),
      ),
      body: Center(
        child:
        Column(
            children: <Widget>[
              SensorList(),
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
                      onPressed: () {},
                      child: Text(
                          'Start'
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