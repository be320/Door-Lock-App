import React, {useState} from 'react';
import {
  StyleSheet,
  View,
  Text,
  TouchableOpacity,
  TextInput,
  KeyboardAvoidingView,
  TouchableWithoutFeedback,
  Keyboard,
} from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import Digit from '../sideComponents/Digit';
import ActionButton from '../sideComponents/ActionButton';

const Keypad = props => {
  const [first, setFirst] = useState('_');
  const [second, setSecond] = useState('_');
  const [third, setThird] = useState('_');
  const [fourth, setFourth] = useState('_');
  const [counter, setCounter] = useState(1);
  const [code,setCode] = useState({  }) 

  const digit = text => {
    switch(counter)
    {
        case 1:
            setFirst(text) 
            setCounter(counter+1)
            break;
        case 2:
            setSecond(text)  
            setCounter(counter+1)
            break;   
        case 3:
            setThird(text)
            setCounter(counter+1)
            break;
        case 4:
            setFourth(text) 
            setCounter(counter+1)
            break;      
        default:
            break;
    }


  };

  const back =  () => 
  {
    switch(counter)
    {
        case 2:
            setFirst("_") 
            setCounter(counter-1)
            break;
        case 3:
            setSecond("_")  
            setCounter(counter-1)
            break;   
        case 4:
            setThird("_")
            setCounter(counter-1)
            break;
        case 5:
            setFourth("_") 
            setCounter(counter-1)
            break;      
        default:
            break;
    }
  };

  const done =  () => 
  {
        if(first=="_"||second=="_"||third=="_"||fourth=="_")
        {   
        }
        else
        {
            setFirst(Number(first))
            setSecond(Number(second))
            setThird(Number(third))
            setFourth(Number(fourth))
            setCode(
                {
                    first:first,
                    second:second,
                    third:third,
                    fourth:fourth,
                }
            )
            console.log(code)
        }
  };

  return (
    <View style={styles.container}>
      <View style={styles.head}>
        <Text style={styles.label}>Check - In</Text>
      </View>

      <View style={styles.row}>
        <View style={styles.screen}>
          <Text style={styles.text}>{first}</Text>
        </View>
        <View style={styles.screen}>
          <Text style={styles.text}>{second}</Text>
        </View>
        <View style={styles.screen}>
          <Text style={styles.text}>{third}</Text>
        </View>
        <View style={styles.screen}>
          <Text style={styles.text}>{fourth}</Text>
        </View>
      </View>

      <View style={styles.border}></View>

      <View style={styles.row}>
        <Digit pressed={digit} text="1" />
        <Digit pressed={digit} text="2" />
        <Digit pressed={digit} text="3" />
      </View>

      <View style={styles.row}>
        <Digit pressed={digit} text="4" />
        <Digit pressed={digit} text="5" />
        <Digit pressed={digit} text="6" />
      </View>

      <View style={styles.row}>
        <Digit pressed={digit} text="7" />
        <Digit pressed={digit} text="8" />
        <Digit pressed={digit} text="9" />
      </View>

      <View style={styles.row}>
        <ActionButton pressed={back} text="backspace" />
        <Digit pressed={digit} text="0" />
        <ActionButton pressed={done} text="check-circle" />
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flexDirection: 'column',
    backgroundColor: '#305e6e',
    height: '100%',
  },
  screen: {
    height: 50,
    width: '10%',
    alignSelf: 'center',
    backgroundColor: '#305e6e',
    margin: 20,
    marginBottom: 0,
    borderRadius: 50,
  },
  row: {
    alignSelf: 'center',
    flexDirection: 'row',
  },
  head: {
    alignSelf: 'center',
    marginTop: 20,
    marginBottom: 0,
  },
  label: {
    color: '#fff',
    fontSize: 30,
  },
  text: {
    fontSize: 40,
    color: '#f2f4f5',
    marginLeft: 9,
    marginTop: -2,
  },
  border: {
    height: 3,
    width: '50%',
    alignSelf: 'center',
    backgroundColor: '#099677',
    margin: 20,
    borderRadius: 30,
  },
});

export default Keypad;
