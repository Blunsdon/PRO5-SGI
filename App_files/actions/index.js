import Base64 from '../Base64';

import {Buffer} from 'buffer';

// Marcs nye UUIDer
const service = '8FBF4200-D0CF-413B-8C2E-4A81554E1377';

/*
#define CUSTOM_SERVICE_UUID               0x4200
// empty characteristic uuid
#define EMPTY_VALUE_CHAR_UUID             0x4201  
// load characteristic uuid
#define LOAD_VALUE_CHAR_UUID              0x4202 
// get weight characteristic uuid
#define GET_VALUE_CHAR_UUID               0x4203 
// calibration characteristic uuid
#define CALI_VALUE_CHAR_UUID              0x4204 
*/

export const addBLE = (device) => ({
  type: 'ADD_BLE',
  device,
});

export const changedNum = (str) => ({
  type: 'CHANGED_NUM',
  str: str,
});

export const CalValue = (cal) => ({
  type: 'Cal_Read',
  cal: cal,
});

export const readValue = (weight, cal) => ({
  type: 'Read_new_value',
  weight: ((weight * 0.6 * 6 * cal) / 16384).toFixed(0),
});

export const readCal = (calWeight) => ({
  type: 'Read_new_Calvalue',
  calWeight: calWeight,
});
//((calWeight * 0.6 * 6) / 16384).toFixed(4)
export const readLoad = (totalload) => ({
  type: 'Reading_Load',
  totalload: totalload,
});

export const connectedDevice = (device) => ({
  type: 'CONNECTED_DEVICE',
  connectedDevice: device,
});

export const connectedDeviceServices = (services) => ({
  type: 'Services',
  connectedDeviceServices: services,
});

export const connectedServiceCharacteristics = (characteristics) => ({
  type: 'Characteristics',
  connectedDeviceCharacteristics: characteristics,
});

export const changeStatus = (status) => ({
  type: 'CHANGE_STATUS',
  status: status,
});

export const setTara = (tara) => ({
  type: 'TARA',
  tara: tara,
});

export const cal1 = (num1) => ({
  type: 'Cal1',
  num1: num1,
});

export const cal2 = (num2) => ({
  type: 'Cal2',
  num2: num2,
});

export const cal3 = (num3) => ({
  type: 'Cal3',
  num3: num3,
});

//some thunks to control the BLE Device

//on android device, we should ask permission

export const startScan = () => {
  return (dispatch, getState, DeviceManager) => {
    const subscription = DeviceManager.onStateChange((state) => {
      if (state === 'PoweredOn') {
        dispatch(scan());
        subscription.remove();
      }
    }, true);
  };
};

export const scan = (s) => {
  const ScanOptions = {ScanMode: 'LowLatency'}; // Low Latency scan mode
  const periph = 'SGI';
  return (dispatch, getState, DeviceManager) => {
    DeviceManager.startDeviceScan(null, ScanOptions, (error, device) => {
      dispatch(changeStatus('Scanning'));
      if (error) {
        console.log(error);
      }
      if (device !== null && device.name !== null) {
        if (device.name.slice(0, 3) === periph) {
          dispatch(addBLE(device));
        }
      }
    });
  };
};

export const getServiceCharacteristics = (service) => {
  return (dispatch, getState, DeviceManager) => {
    let state = getState();
    DeviceManager.characteristicsForDevice(
      state.BLEs.connectedDevice.id,
      service.uuid,
    ).then((characteristics) => {
      dispatch(connectedServiceCharacteristics(characteristics));
    });
  };
};
// timeout: 5000,
//autoConnect: true
export const connectDevice = (device) => {
  const ConnectionOptions = {timeout: 7000};
  return async (dispatch, getState, DeviceManager) => {
    console.log('Connecting');
    dispatch(changeStatus('Connecting'));
    DeviceManager.stopDeviceScan();
    device
      .connect(ConnectionOptions)
      .then((device) => {
        console.log('Discovering');
        dispatch(changeStatus('Discovering'));
        let characteristics = device.discoverAllServicesAndCharacteristics();
        dispatch(connectedDevice(device));
        return characteristics;
      })
      .then((device) => {
        let services = device.services(device);
        dispatch(changeStatus('Setting Notifications'));
        return services;
      })
      .then((services) => {
        dispatch(connectedDeviceServices(services));
      })
      .then(
        (device) => {
          console.log('listening');
          dispatch(changeStatus('Listening'));
          dispatch(read(4));
          dispatch(read(2));
          return device;
        },
        (error) => {
          console.log(this._logError('SCAN', error));
        },
      );
  };
};

export const send = (str, char) => {
  return (dispatch, getState, DeviceManager) => {
    const state = getState();
    console.log('Sending: ', str);
    try {
      let charWrite = '8FBF420' + char + '-D0CF-413B-8C2E-4A81554E1377';
      if (char === 4 || char === 2) {
        const temp = Buffer.alloc(2);
        temp.writeUInt16LE(10 * str, 0);
        console.log('Sending Cal: ', str);
        state.BLEs.connectedDevice
          .writeCharacteristicWithResponseForService(
            service,
            charWrite,
            temp.toString('base64'),
          )
          .then((data) => {
            if (char === 4) {
              // Calibration
              let temp = Buffer.from(data.value, 'base64').readUInt16LE(0);
              console.log('Char sent 4: ', parseInt(temp, 16));
            }
            if (char === 2) {
              // TotalLoad
              let temp = Buffer.from(data.value, 'base64').readUInt16LE(0);
              console.log('Char sent 2: ', parseInt(temp, 16));
              dispatch(changeStatus('Read_Load'));
            }
          });
        dispatch(changeStatus('Read_new_load'));
      } else {
        let base64 = Base64.btoa(unescape(encodeURIComponent(str)));
        state.BLEs.connectedDevice
          .writeCharacteristicWithResponseForService(service, charWrite, base64)
          .then((data) => {
            let base64 = Base64.atob(escape(decodeURIComponent(data.value)));
            console.log('DATA fra send: ', base64);
          });
        if (char === 1) {
          // Empty
          dispatch(changeStatus('Read_new_load'));
        }

        if (char === 3) {
          // Currrent load
          dispatch(changeStatus('Read_new_value'));
        }
      }
      return true;
    } catch (error) {
      console.log('update Error:', error);
      return false;
    }
  };
};

export const read = (char) => {
  return (dispatch, getState, DeviceManager) => {
    const state = getState();
    let charRead = '8FBF420' + char + '-D0CF-413B-8C2E-4A81554E1377';
    try {
      state.BLEs.connectedDevice
        .readCharacteristicForService(service, charRead)
        .then((data) => {
          let temp = Buffer.from(data.value, 'base64').readUInt16LE(0);
          return temp;
        })
        .then((temp) => {
          if (char === 4) {
            // Cal value
            console.log('Char 4 read: ', temp / 10);
            dispatch(changeStatus('Read_Cal'));
            dispatch(CalValue(temp / 10));
          }
          if (char === 3) {
            // Currrent load
            console.log('read calWeight: ', temp);
            dispatch(changeStatus('Read_new_value'));
            dispatch(readCal(temp.toFixed(4)));
            dispatch(readValue(temp, state.BLEs.cal));
          }
          if (char === 2) {
            // Total load
            console.log('Char 2 read: ', temp / 10);
            if (isNaN(temp)) {
              temp = 0;
            }
            dispatch(changeStatus('Read_new_load'));
            dispatch(readLoad(temp / 10));
          }
        });

      return true;
    } catch (error) {
      console.log('read error: ', error);
      return false;
    }
  };
};
