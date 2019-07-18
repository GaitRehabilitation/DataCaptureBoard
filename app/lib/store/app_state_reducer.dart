
import 'package:app/store/sensors_state_reducer.dart';
import 'package:app/store/app_state.dart';

AppState appReducer (AppState state, action) {
  return AppState(
    sensors: sensorsReducer(state.sensors,action)
  );
}