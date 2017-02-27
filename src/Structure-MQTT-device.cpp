#include "Structure-MQTT-device.h"



// Constructor
GetStructure::Device::Device(char * deviceId, char * accessKey, char * accessSecret)
{
    Serial.println("Initialization of the device");
 // Topic used to subscribe to Losant commands.
topicCommand = String::format("losant/%s/command", deviceId);

// Topic used to publish state to Losant.
topicState = String::format("losant/%s/state", deviceId);
this->deviceId = String(deviceId);
this->accessKey = String(accessKey);
this->accessSecret = String(accessSecret);
this->client.setDevice(this);
 
}
void GetStructure::Device::mqttCallback(char* topic, byte* payload, unsigned int length) {
    
    // Parse the command payload.
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject& command = jsonBuffer.parseObject((char*)payload);
	this->callback(command);

}
void GetStructure::Device::mqttQosCallback(unsigned int qos) {
    
    // TODO: .
    

}


// Connects to the Losant MQTT broker.
void GetStructure::Device::connect(void (*callback)(JsonObject&)) {
    
    this->callback = callback;
    while(!client.isConnected()) {
        client.connect(
            deviceId,
            accessKey,
            accessSecret);
            
        if(client.isConnected()) {
            client.subscribe(topicCommand);
        }
        else {
            delay(500);
        }
    }
}
bool GetStructure::Device::loop(){
	if (!client.isConnected()) {
        connect(callback);
    }

    // Loop the MQTT client.
    return client.loop();
	
}
bool GetStructure::Device::isConnected(){
	return client.isConnected();
}
bool GetStructure::Device::publish(JsonObject& payload){
	// enables data format required by Losant plateform
	StaticJsonBuffer<300> jsonBuffer;
	JsonObject& data = jsonBuffer.createObject();
	data["data"] = payload;
	char buffer[300];
    data.printTo(buffer, sizeof(buffer));

    return client.publish(topicState, buffer);
}