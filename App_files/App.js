import React from 'react';

import {Provider} from 'react-redux';
import {createStore, applyMiddleware} from 'redux';
import rootReducer from './reducers/index';
import thunk from 'redux-thunk';

import {BleManager} from 'react-native-ble-plx';
import {PermissionsAndroid, Platform} from 'react-native';

import {createAppContainer} from 'react-navigation';
import {createStackNavigator} from 'react-navigation-stack';
import Main from './Main';
import Unload from './Aflast';
import Load from './Last';
import Calibration from './Kalibrering';
import Settings from './Indstillinger';
import BLEList from './BLEList';

const MainNavigator = createStackNavigator(
  {
    Home: {screen: Main},
    List: {screen: BLEList},
    Settings: {screen: Settings},
    Unload: {screen: Unload},
    Load: {screen: Load},
    Calibration: {screen: Calibration},
  },
  {
    headerMode: 'none',
  },
);

const requestLocationPermission = async () => {
  try {
    const granted = await PermissionsAndroid.request(
      PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION,
    );
    if (granted === PermissionsAndroid.RESULTS.GRANTED) {
      console.log('Location permission for bluetooth scanning granted');
      return true;
    } else {
      console.log('Location permission for bluetooth scanning revoked');
      return false;
    }
  } catch (err) {
    console.warn(err);
    return false;
  }
};


const DeviceManager = new BleManager();

let Navigation = createAppContainer(MainNavigator);

const store = createStore(
  rootReducer,
  applyMiddleware(thunk.withExtraArgument(DeviceManager)),
);

const App: () => React$Node = () => {
  requestLocationPermission();
  return (
    <>
      <Provider store={store}>
        <Navigation />
      </Provider>
    </>
  );
};
export default App;
