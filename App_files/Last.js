import {Text, View, TouchableOpacity} from 'react-native';
import styles from './Styles';

import React, {Component} from 'react';
import {connect} from 'react-redux';
import {read, send, setTara} from './actions';

class Load extends Component {
  constructor(props) {
    super(props);
    this.sendReadWeight = this.sendReadWeight.bind(this);
    this.sendEmpty = this.sendEmpty.bind(this);
    this.addLoad = this.addLoad.bind(this);
    this.removeLoad = this.removeLoad.bind(this);
    this.taration = this.taration.bind(this);
  }

  sendReadWeight() {
    this.props.read(2);
    this.props.send('orez', 3);
    this.props.read(3);
  }

  addLoad() {
    let tempload = parseInt(this.props.totalload, 10);
    let tempweight = this.props.weight - this.props.tara;
    let tempres = tempload + +tempweight;
    this.props.send(tempres, 2);
    this.props.read(2);
  }

  removeLoad() {
    let tempload = this.props.totalload;
    let tempweight = this.props.weight - this.props.tara;
    let tempres = tempload - tempweight;
    this.props.send(tempres, 2);
    this.props.read(2);
  }

  sendEmpty() {
    this.props.send('fuun', 1);
    this.props.read(2);
  }

  taration() {
    let temp = this.props.weight;
    this.props.tar(temp);
  }
  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.header}>
          Nuværende last {'\n'} {this.props.totalload} Kg{' '}
        </Text>
        <Text style={styles.resText}>
          {this.props.weight - this.props.tara} kg
        </Text>
        <TouchableOpacity style={styles.startBtn} onPress={this.sendReadWeight}>
          <Text style={styles.startText}>Indlæs Vægt</Text>
        </TouchableOpacity>
        <View style={styles.containerLast}>
          <TouchableOpacity style={styles.underBtn} onPress={this.addLoad}>
            <Text style={styles.startText}>Tilføj vægt</Text>
          </TouchableOpacity>
          <TouchableOpacity style={styles.underBtn} onPress={this.removeLoad}>
            <Text style={styles.startText}>Fjern vægt</Text>
          </TouchableOpacity>
        </View>
        <View style={styles.containerLast}>
          <TouchableOpacity style={styles.underBtn} onPress={this.taration}>
            <Text style={styles.startText}>TARA</Text>
          </TouchableOpacity>
        </View>
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
    status: state.BLEs.status,
    weight: state.BLEs.weight,
    str: state.BLEs.str,
    char: state.BLEs.char,
    totalload: state.BLEs.totalload,
    tara: state.BLEs.tara,
    cal: state.BLEs.cal,
  };
}

const mapDispatchToProps = (dispatch) => ({
  send: (str, char) => dispatch(send(str, char)),
  read: (char) => dispatch(read(char)),
  tar: (tara) => dispatch(setTara(tara)),
});
export default connect(mapStateToProps, mapDispatchToProps)(Load);
