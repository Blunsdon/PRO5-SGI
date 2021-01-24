
import {Text, View, TouchableOpacity} from 'react-native';
import styles from './Styles';

import React, {Component} from 'react';
import {connect} from 'react-redux';
import {connectedDevice} from './actions';

class Settings extends Component {
  constructor(props) {
    super(props);
  }
  render() {
    return (
      <View style={styles.containerIndstillinger}>
        <Text style={styles.header}>Angiv nyt sensor ID</Text>
        <Text style={styles.resText}>{this.props.connectedDevice.id}</Text>
        <TouchableOpacity
          style={styles.kalBtn}
          onPress={() => this.props.navigation.navigate('Calibration')}>
          <Text style={styles.startText}>Kalibrer</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.kalBtn}
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
  };
}

const mapDispatchToProps = (dispatch) => ({

});
export default connect(mapStateToProps, mapDispatchToProps)(Settings);