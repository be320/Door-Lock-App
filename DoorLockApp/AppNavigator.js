import React from 'react';
import {createAppContainer} from 'react-navigation';
import {createStackNavigator} from 'react-navigation-stack';
import Keypad from './src/modules/Keypad';

const AppNavigator = createStackNavigator(
  {
    Keypad: {screen: Keypad},
  },
  {
    headerMode: 'none',
    initialRouteName: 'Keypad',
  },
);

export default createAppContainer(AppNavigator);
