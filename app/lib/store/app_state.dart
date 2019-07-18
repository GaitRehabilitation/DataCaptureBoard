
import 'package:app/models/sensor.dart';

class AppState{
  final List<Sensor> sensors;

  AppState({
    this.sensors = const []
  });

  @override
  bool operator ==(other) {
    identical(this,other) ||
    other is AppState &&
    this.sensors == other.sensors;
  }

  @override
  String toString() => 'AppState(sensors: $sensors)';

}