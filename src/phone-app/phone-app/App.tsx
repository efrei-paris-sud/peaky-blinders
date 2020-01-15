import React, {Component} from 'react';
import {Button, ScrollView, StyleSheet, Text, TextInput, View} from 'react-native';

enum OutputType{SIMPLE, BLINDERS};

export default class App extends  Component{

  outputs: {id: number, name: string, type: OutputType}[] = [
    {id:0, name: 'Lampe 1', type: OutputType.SIMPLE},
    {id:1, name: 'Lampe 2', type: OutputType.SIMPLE},
    {id:2, name: 'Lampe 2', type: OutputType.SIMPLE},
    {id:3, name: 'Lampe 2', type: OutputType.SIMPLE},
    /*{id:32, name: 'Lampe 3', type: OutputType.SIMPLE},
    {id:33, name: 'Lampe 4', type: OutputType.SIMPLE},*/
    //{id:5, name: 'Volets', type: OutputType.BLINDERS},
  ];

  state = {url: 'http://192.168.43.151/switch'}

  constructor(props){super(props)}

  public async sendRequest(target, action){
    console.log("Executing Action : " + action);
    return fetch(this.state.url + '?id=' + target + '&value=' + action);
  }

  render() {
    return (
        <ScrollView>
          <View style={styles.container}>
            <View style={{
              padding: 10,
              margin: 5,
              flex: 1,
              flexDirection: 'row',
              alignItems: 'flex-start',
              justifyContent: 'flex-start'
            }}>
              <TextInput onChangeText={text => {
                this.setState({url: text})
              }} value={this.state.url}/>
            </View>
            {this.outputs.map(value =>
                <View key={value.id} style={{
                  padding: 10,
                  margin: 5,
                  flex: 1,
                  flexDirection: 'row',
                  alignItems: 'flex-start',
                  justifyContent: 'flex-start',
                  backgroundColor: 'rgba(0,0,255,0.3)'
                }}>
                  <Text style={{flex: 3}}>{value.name}</Text>
                  <View style={{flex: 1}}>
                    {value.type === OutputType.BLINDERS &&
                    <>
                      <Button color="green" title={"/\\"} onPress={() => this.sendRequest(value.id, '2')}/>
                      <Button color="red" title={"Stop"} onPress={() => this.sendRequest(value.id, '0')}/>
                      <Button color="green" title={"\\/"} onPress={() => this.sendRequest(value.id, '1')}/>
                    </>
                    }
                    {value.type === OutputType.SIMPLE &&
                    <>
                      <Button title={"On"} onPress={() => this.sendRequest(value.id, '1')}/>
                      <Button color="red" title={"Off"} onPress={() => this.sendRequest(value.id, '0')}/>
                    </>
                    }
                  </View>
                </View>
            )}
          </View>
        </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    justifyContent: 'center',
    alignItems: 'center',
    flexDirection: 'column',
    paddingTop: 30
  },
});
