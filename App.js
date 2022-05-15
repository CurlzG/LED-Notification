import { StatusBar } from 'expo-status-bar';
import React, { useState, useEffect} from "react";

import { StyleSheet,Button, Text, View } from 'react-native';
import {Picker} from '@react-native-picker/picker';
import firebase from 'firebase';
import 'firebase/database';
//Fire base Configureation
const firebaseConfig = {
  apiKey: "API Key",
  authDomain: "Auth Domain",
  databaseURL: "DataBase URL",
  projectId: "Project ID",
  storageBucket: "Storage Bucket",
  messagingSenderId: "Messaging Sender ID",
  appId: "App ID",
  measurementId: "Measurement ID"
};

if (!firebase.apps.length) {
  firebase.initializeApp(firebaseConfig);
}else {
  firebase.app();
}
firebase.firestore().settings({ experimentalForceLongPolling: true });

export default function App() {
  //On Picker having the first value be per1
  const [selectedValue, setSelectedValue] = useState("per1");
  const [per1, setper1] = useState("");
  const [per2, setper2] = useState("");
  const [per3, setper3] = useState("");


  //Update Firebase database to highlight an led
  const updateFD = () => {
    firebase.database().ref().child(selectedValue).set("P1");
    check();
  }  
  //Undo Firebase databse to turn off the led
  const undoFD = () => {
    firebase.database().ref().child(selectedValue).set("-");
    check();
  }

  //Check the Firebase database
  const check = () =>{
    firebase.database().ref().get().then((snapshot) =>{
      const values = Object.values(snapshot.val());
        if(values[0] != '-'){
          setper3("per3 is Calling");
        }else {
          setper3("");
        }
      
      
          if(values[1] != '-'){
            setper2("per2 is Calling");
          } else {
            setper2("");
          }
          if(values[2] != '-'){
            setper1("per1 is Calling");
          } else {
            setper1("");
          }
             
          
      
      
    
    });
     
  }
  useEffect(() => {
    check();
    return;
    },[]);
  return (
    <View style={styles.container}>
      <Picker
        selectedValue={selectedValue}
        style={{ height: 50, width: 150 }}
        onValueChange={(itemValue, itemIndex) => setSelectedValue(itemValue)}
      >
        <Picker.Item label="per1" value="per1" />
        <Picker.Item label="per2" value="per2" />
        <Picker.Item label="per3" value="per3" />
  
        
      </Picker>
      <View style={styles.space} />
      <Text> {per1}</Text>
      <View style={styles.space} />
      <Text> {per3}</Text>
      <View style={styles.space} />
      <Text> {per2}</Text>
      <View style={styles.space} />
      <Button
        title="Set Call"
        onPress={() => updateFD() }
      />
 <View style={styles.space} />
            <Button
        title="Undo Call"
        onPress={() => undoFD() }
      />
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  space: {
    width: 20, // or whatever size you need
    height: 20,
  },
});
