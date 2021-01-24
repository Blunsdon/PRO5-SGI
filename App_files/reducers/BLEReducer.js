import update from 'immutability-helper';

const INITIAL_STATE = {
  BLEList: [],
  connectedDevice: {},
  connectedDeviceServices: [],
  connectedServiceCharacteristics: [],
  selectedService: {},
  selectedCharacteristic: {},
  status: 'disconnected',
  weight: 'Not measured',
  totalload: 0,
  char: 0,
  str: 0,
  tara: 0,
  cal: 1.0,
  noload: 0,
  withload: 0,
  load: 0,
  num1: 0,
  num2: 0,
  num3: 0,
  calWeight: 0,
};

const BLEReducer = (state = INITIAL_STATE, action) => {
  switch (action.type) {
    case 'ADD_BLE':
      if (
        state.BLEList.some(
          (device) =>
            device.id === action.device.id ||
            !action.device.isConnectable ||
            action.device.name === null,
        )
      ) {
        return state;
      } else {
        return update(state, {
          BLEList: {$set: [...state.BLEList, action.device]},
        });
      }
    case 'CONNECTED_DEVICE':
      return update(state, {connectedDevice: {$set: action.connectedDevice}});
    case 'CONNECTED_SERVICES':
      return update(state, {
        connectedDeviceServices: {$set: action.connectedDeviceServices},
      });
    case 'SELECTED_SERVICE':
      return update(state, {selectedService: {$set: action.selectedService}});
    case 'SELECTED_CHARACTERISTIC':
      return update(state, {
        selectedCharacteristic: {$set: action.selectedCharacteristic},
      });
    case 'CONNECTED_CHARACTERISTICS':
      return update(state, {
        connectedServiceCharacteristics: {
          $set: action.connectedServiceCharacteristics,
        },
      });
    case 'CHANGE_STATUS':
      return update(state, {status: {$set: action.status}});
    case 'Reading_Load':
      return update(state, {totalload: {$set: action.totalload}});
    case 'TARA':
      return update(state, {tara: {$set: action.tara}});
    case 'Read_new_value':
      return update(state, {weight: {$set: action.weight}});
    case 'Read_new_Calvalue':
      console.log('calWeight');
      return update(state, {calWeight: {$set: action.calWeight}});
    case 'CHANGED_NUM':
      return update(state, {
        changedNum: {$set: action.send},
      });
    case 'Cal1':
      console.log('cal1');
      return update(state, {num1: {$set: action.num1}});
    case 'Cal2':
      console.log('cal2');
      return update(state, {num2: {$set: action.num2}});
    case 'Cal3':
      console.log('cal3');
      return update(state, {num3: {$set: action.num3}});
    case 'Cal_Read':
      console.log('cal');
      return update(state, {cal: {$set: action.cal}});
    default:
      return state;
  }
};

export default BLEReducer;
