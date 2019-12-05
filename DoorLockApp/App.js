import React,{useEffect} from 'react';
import Keypad from './src/modules/Keypad';
import firebase from 'firebase';
import SplashScreen from 'react-native-splash-screen';

const App = () => {
  useEffect(() => {
    SplashScreen.hide();
  });

  return <Keypad />;
};

export default App;
