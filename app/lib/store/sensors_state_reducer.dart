
import 'package:app/models/sensor.dart';
import 'package:redux/redux.dart';

class LoadSensorAction {
  final List<Sensor> sensors;

  LoadSensorAction(this.sensors);

  @override
  String toString() => 'LoadSensorAction{sensors: $sensors}';

}

class AddSensorAction {
  final Sensor sensor;

  AddSensorAction(this.sensor);

  @override
  String toString() => 'AddSensorAction{sensor: $sensor}';

}

class RemoveSensorAction {
  final Sensor sensor;

  RemoveSensorAction(this.sensor);

  @override
  String toString() => 'RemoveSensorAction{sensor: $sensor}';
}



final sensorsReducer = combineReducers<List<Sensor>>([
  TypedReducer<List<Sensor>,LoadSensorAction>(_setSensor),
  TypedReducer<List<Sensor>,AddSensorAction>(_addSensor),
  TypedReducer<List<Sensor>,RemoveSensorAction>(_removeSensor)
]);


List<Sensor> _setSensor(List<Sensor> sensors, LoadSensorAction action){
  return action.sensors;
}

List<Sensor> _addSensor(List<Sensor> sensors, AddSensorAction action ){
  List<Sensor> result = List.from(sensors);
  result.add(action.sensor);
  return result;
}

List<Sensor> _removeSensor(List<Sensor> sensors, RemoveSensorAction action) {
  List<Sensor> result = List.from(sensors);
  result.remove(action.sensor);
  return result;
}

