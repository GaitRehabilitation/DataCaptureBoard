import 'package:app/bluetooth_search_route.dart';
import 'package:app/home.dart';
import 'package:app/store/app_state.dart';
import 'package:flutter/material.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:redux/redux.dart';
import 'package:app/store/app_state_reducer.dart';

void main() => runApp(App());

class App extends StatelessWidget {
  final Store<AppState> _store;

  App({Key key})
      : _store = Store<AppState>(
      appReducer,
      initialState: new AppState()
  ),super(key: key) {
  }

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return StoreProvider(
      store: _store,
      child: MaterialApp(
        title: 'Flutter Demo',
        theme: ThemeData(
          primarySwatch: Colors.blue,
        ),
        routes: {
          '/': (context) => HomeState(),
          '/search': (context) => BluetoothSearchRoute()
        },
      ),
    );
  }
}