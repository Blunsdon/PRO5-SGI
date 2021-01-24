import {StyleSheet} from 'react-native';

export default StyleSheet.create({
  container: {
    flex: 3,
    backgroundColor: '#004F5A',
    alignItems: 'center',
    justifyContent: 'center',
  },

  containerIndstillinger: {
    flex: 4,
    backgroundColor: '#004F5A',
    alignItems: 'center',
    justifyContent: 'flex-start',
  },

  containerLast: {
    flexDirection: 'row',
    flex: 1,
    backgroundColor: '#004F5A',
    alignItems: 'center',
    justifyContent: 'center',
  },

  containerRes: {
    //height: "10%"
    flexDirection: 'row',
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'space-around',
  },

  header: {
    fontWeight: 'bold',
    color: 'white',
    fontSize: 30,
    margin: 5,
  },

  startBtn: {
    flex: 1,
    maxHeight: '10%',
    //height: "10%",
    backgroundColor: '#f15a22',
    borderRadius: 50,
    //padding: 5,
    width: '70%',
    alignItems: 'center',
    marginTop: 50,
    justifyContent: 'center',
  },
  kalBtn: {
    flex: 0.1,
    maxHeight: '10%',
    backgroundColor: '#f15a22',
    borderRadius: 50,
    //padding: 5,
    width: '70%',
    alignItems: 'center',
    marginTop: 50,
    justifyContent: 'center',
  },

  resBtn: {
    flex: 1,
    maxHeight: '10%',
    backgroundColor: '#f15a22',
    borderRadius: 50,
    //padding: 5,
    width: '20%',
    alignItems: 'center',
    marginTop: 50,
    justifyContent: 'center',
  },

  underBtn: {
    minHeight: '40%',
    width: '35%',
    backgroundColor: '#f15a22',
    borderRadius: 50,
    justifyContent: 'center',
    //alignContent: "center",
    alignSelf: 'center',
    margin: '1%',
  },

  startText: {
    textAlign: 'center',
    color: 'white',
    fontSize: 20,
  },

  resText: {
    flex: 1,
    width: '70%',
    textAlign: 'center',
    color: '#818181',
    fontSize: 20,
    backgroundColor: 'white',
    maxHeight: '10%',
  },

  infoText: {
    color: 'white',
    fontSize: 16,
    alignItems: 'center',
    textAlign: 'left',
    margin: 5,
  },
  textInput: {
    padding: 8,
    width: '40%',
    backgroundColor: 'white',
    borderRadius: 10,
  },
});
