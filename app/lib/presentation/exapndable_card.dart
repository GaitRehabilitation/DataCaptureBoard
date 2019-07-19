import 'package:flutter/material.dart';

class ExpandableCard extends StatefulWidget{
  const ExpandableCard({
    Key key,
    this.child
  }):super(key:key);

  final Widget child;

  @override
  State<StatefulWidget> createState() => new _ExpandableCardState();
}

class _ExpandableCardState extends State<ExpandableCard> {
  bool _toggle;

  @override
  Widget build(BuildContext context) {
    List<Widget> widgets = [];
    widgets.add(FlatButton(
      onPressed: () {
        setState(() {
          _toggle != _toggle;
        });
      },
      child: Text("Toggle"),
    ));
    if (_toggle) {
      widgets.add(widget.child);
    }
    return Card(
        child:
        Column(children: widgets)
    );
  }
}
