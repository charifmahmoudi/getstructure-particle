
#include "Structure-MQTT-device.h"


// The Photon's onboard LED.
int LED = D7;
// Toggles the LED on/off whenever "toggle" command is received.
bool ledValue = false;
// Used to only send temperature once a second.
int lastUpdate = millis();

// The initialization of your device
GetStructure::Device photon("YOUR-DEVICE-ID", "YOUR-ACCESS-KEY", "YOUR-ACCESS-SECRET");

// Callback signature for Structure subscriptions.
void myCallback(JsonObject& command);

// Callback for Structure subscriptions.
// Receive Your JsonObject from Structure
void myCallback(JsonObject& command) {

    
    // If the command's name is "toggle", flip the LED.
    if(String(command["name"].asString()).equals(String("toggle"))) {
        ledValue = !ledValue;
        digitalWrite(LED, ledValue ? HIGH : LOW);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Starting the Setup");
    pinMode(LED, OUTPUT);
    
    //you can create dynamicly devices using pointers
    //photon = new GetStructure::Device("aaaa", "bbbb", "cccc");
	
	//Connect the photon to Structure broker
	photon.connect(myCallback);
	Serial.println("Setup complete");
}

void loop() {
	int now = millis();
    
    // Publish Light value every second.
    if(now - lastUpdate > 1000) {
        
        lastUpdate = now;
        
        // Build the json payload: { "rawlight" : xxx, "time" : yyy}
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        
        // Gets raw voltage to a light.
        int light = analogRead(A0);
        root["rawlight"] = light;
        root["time"] = lastUpdate;
        
        
       //Publish directly your JsonObject !!!  
       photon.publish(root);
    }
    photon.loop();
    
}


