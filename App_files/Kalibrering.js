import {Text, View, TouchableOpacity, TextInput} from 'react-native';
import styles from './Styles';

import React, {Component} from 'react';
import {connect} from 'react-redux';
import {send, read, cal1, cal2, cal3, CalValue} from './actions';

class Calibration extends Component {
  constructor(props) {
    super(props);
    this.withoutLoad = this.withoutLoad.bind(this);
    this.withLoad = this.withLoad.bind(this);
    this.onTextChanged = this.onTextChanged.bind(this);
    this.calTheCalFac = this.calTheCalFac.bind(this);
  }

  withoutLoad() {
    this.props.send('orez', 3);
    this.props.read(3);
  }

  withLoad() {
    let temp = this.props.calWeight;
    console.log('Calweight noload', temp);
    this.props.cal1(temp);
    this.props.send('orez', 3);
    this.props.read(3);
  }

  onTextChanged(temp) {
    console.log('Text', temp);
    this.props.cal3(temp);
  }

  calTheCalFac() {
    let temp = this.props.calWeight;
    this.props.cal2(temp);
    console.log('Noload', this.props.num1); //måling uden load
    console.log('Withload', temp);
    console.log('Load', this.props.num3);
    temp = temp - this.props.num1; // måling med load - måling uden load
    console.log('Calc caltemp', temp);
    temp = this.props.num3 / temp; // ref / loadmåling
    console.log('Cal', temp);
    this.props.CalValue(temp);
    this.props.send(temp, 4);
  }

  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.infoText}>
          Fjern al belastning {'\n'}Tryk derefter på "Uden lod"{'\n'}Monter
          kalibreringslod og tryk på "Med lod"
          {'\n'}Tryk til sidst på det hvide felt, indtast vægt i hele kilo og
          tryk på "Færdig."
        </Text>
        <Text style={styles.resText}>{this.props.calWeight} kg</Text>
        <TouchableOpacity style={styles.startBtn} onPress={this.withoutLoad}>
          <Text style={styles.startText}>Uden lod</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.startBtn} onPress={this.withLoad}>
          <Text style={styles.startText}>Med lod</Text>
        </TouchableOpacity>
        <TextInput
          style={styles.textInput}
          keyboardType="numeric"
          onChangeText={(text) => this.onTextChanged(text)}
        />

        <TouchableOpacity style={styles.startBtn} onPress={this.calTheCalFac}>
          <Text style={styles.startText}>Færdig</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.startBtn}
          onPress={() => this.props.navigation.goBack()}>
          <Text style={styles.startText}>Tilbage</Text>
        </TouchableOpacity>
      </View>
    );
  }
}

function mapStateToProps(state) {
  return {
    connectedDevice: state.BLEs.connectedDevice,
    status: state.BLEs.status,
    calWeight: state.BLEs.calWeight,
    str: state.BLEs.str,
    char: state.BLEs.char,
    totalload: state.BLEs.totalload,
    tara: state.BLEs.tara,
    num1: state.BLEs.num1,
    num2: state.BLEs.num2,
    num3: state.BLEs.num3,
    cal: state.BLEs.cal,
  };
}

const mapDispatchToProps = (dispatch) => ({
  send: (str, char) => dispatch(send(str, char)),
  read: (char) => dispatch(read(char)),
  cal1: (num1) => dispatch(cal1(num1)),
  cal2: (num2) => dispatch(cal2(num2)),
  cal3: (num3) => dispatch(cal3(num3)),
  CalValue: (cal) => dispatch(CalValue(cal)),
});
export default connect(mapStateToProps, mapDispatchToProps)(Calibration);
