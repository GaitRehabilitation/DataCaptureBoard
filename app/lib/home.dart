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
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  RaisedButton(
                    onPressed: () {},
                    child: Text(
                        'Start'
                    ),
                  ),
                  RaisedButton(
                    onPressed: () {},
                    child: Text(
                        'Stop'
                    ),
                  )
                ],
              )
            ]
        ),
      ),
    );
  }
}