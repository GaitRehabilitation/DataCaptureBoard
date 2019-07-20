import 'package:app/models/sensor.dart';
import 'package:app/store/app_state.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_redux/flutter_redux.dart';


class SensorList extends StatefulWidget{
  @override
  State<StatefulWidget> createState() => _SensorList();

}

class _SensorList extends State<SensorList> {
  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Container(
        child: _buildPanel(),
      ),
    );
  }

  Widget _buildPanel() {
    return StoreConnector<AppState, List<Sensor>>(
        converter: (store) {
          return store.state.sensors;
        },
        builder: (context, List<Sensor> vm) {
          List<ExpansionPanel>  panels = vm.map<ExpansionPanel>((Sensor sensor){
            return new ExpansionPanel(headerBuilder: (BuildContext context, bool isExpanded){
              return ListTile(
                title: Text(sensor.device.id.toString()),
              );
            }, body: ListTile(
              title: Text(sensor.device.id.toString()),
            ));
          });

        return ExpansionPanelList(
            expansionCallback: (int index, bool isExpanded) {
              return vm[index].isExpanded;

            },
            children: panels
        );
      });
  }
}