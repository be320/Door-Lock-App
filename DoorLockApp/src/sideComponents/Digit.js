import React from 'react'
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
const Digit = ({text,pressed}) =>
 {
    return (
       <View>
            <TouchableOpacity
   style={{
       borderWidth:4,
       borderColor:'#099677',
       alignItems:'center',
       justifyContent:'center',
       width:100,
       height:100,
       backgroundColor:'#5c9b98',
       borderRadius:50,
       margin:10
     }}
     onPress={()=>pressed(text)}
 >
     <Text style={styles.text}>{text}</Text>
 </TouchableOpacity>
       </View>
    )
}


const styles = StyleSheet.create({
   text:{
       fontSize:40,
       color:"#fff"
   }
    })

export default Digit