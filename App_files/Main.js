import React, {Component} from 'react';
import {Text, View, Animated, TouchableOpacity} from 'react-native';
import styles from './Styles';
import {writeCharacteristic, send, read} from './actions';


import {connect} from 'react-redux';
import {connectedDevice} from './actions';

class Main extends Component {
  constructor(props) {
    super(props);
    this.sendReadWeight = this.sendReadWeight.bind(this);
    this.getCal = this.getCal.bind(this);
  }

  sendReadWeight() {
    this.props.send('orez', 3);
    this.props.read(3);
    console.log('Calweight', this.props.calWeight);
    console.log('Calweight * calfactor', this.props.calWeight * this.props.cal);
  }

  getCal() {
    this.props.read(4);
  }

  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.header}>Sense-Tech{'\n'}BT Scale</Text>
        <Text style={styles.infoText}>Status: {this.props.status}</Text>
        <TouchableOpacity
          onPress={() => this.props.navigation.navigate('List')}>
          <Text style={styles.infoText}>
            Unit: {this.props.connectedDevice.name}
          </Text>
        </TouchableOpacity>
        <Text style={styles.resText}>{this.props.weight} kg</Text>
        <TouchableOpacity style={styles.startBtn} onPress={this.sendReadWeight}>
          <Text style={styles.startText}>Indlæs Vægt</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.startBtn}
          onPress={() => this.props.navigation.navigate('Load')}>
          <Text style={styles.startText}>Last</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.startBtn}
          onPress={() => this.props.navigation.navigate('Unload')}>
          <Text style={styles.startText}>Aflast</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.startBtn}
          onPress={() => this.props.navigation.navigate('Settings')}>
          <Text style={styles.startText}>Indstillinger</Text>
        </TouchableOpacity>
      </View>
    );
  }
}

function mapStateToProps(state) {
  return {
    connectedDevice: state.BLEs.connectedDevice,
    status: state.BLEs.status,
    weight: state.BLEs.weight,
    str: state.BLEs.str,
    char: state.BLEs.char,
    cal: state.BLEs.cal,
    calWeight: state.BLEs.calWeight,
  };
}

const mapDispatchToProps = (dispatch) => ({
  send: (str, char) => dispatch(send(str, char)),
  read: (char) => dispatch(read(char)),
});
export default connect(mapStateToProps, mapDispatchToProps)(Main);
