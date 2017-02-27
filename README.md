# getstructure-particle
A [Particle Builder](https://build.particle.io/build)  library for integration with [Losant](https://www.losant.com/)

## About

This library serves as a wrapper for the [MQTT library](https://github.com/hirotakaster/MQTT) for the integration with [Losant](https://www.losant.com/) Broker.
It offers simplified methods and an Device object to communicate with [Losant](https://www.losant.com/)

## Getting started
A [getting started](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d) tutorial is available at [Hackster.io](https://www.hackster.io/)

[https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d)

This  [getting started](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d) tutorial describes all the steps needed to integrates the library in your project.

## Dependencies

This library depends on the [SPARKJSON](https://github.com/menan/SparkJson) library that is available as community library in the [Particle Builder](https://build.particle.io/build)
**v2 update** Library is added as dependency using the new particle Libraries v2 feature

## Features

The getstructure-particle library offers multiples cool features:




The callback method support directly JSon object. so you do not have to deal with boring char * and convert them by yourself.
```
// Callback for Structure subscriptions.
// Receive Your JsonObject from GetStructure.io
void myCallback(JsonObject& command) {
    // If the command's name is "toggle", flip the LED.
    if(String(command["name"].asString()).equals(String("toggle"))) {
        ledValue = !ledValue;
        digitalWrite(LED, ledValue ? HIGH : LOW);
    }
}
```
**Device** Object that associate a photon to the **Device** at [Structure](https://www.getstructure.io/)

Is a wrapper for all the MQTT communication. It provides simply an object GetStructure::Device that you deal with. and it represents the devices on [Structure](https://www.getstructure.io/) application.

```
// The initialization of your device
GetStructure::Device photon("YOUR-DEVICE-ID", "YOUR-ACCESS-KEY", "YOUR-ACCESS-SECRET");
```
Just create your Json object and it send it for your to Structure application.
```
StaticJsonBuffer<100> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
...
//Publish directly your JsonObject !!!
photon.publish(root);
```



Simplified Json-based push method and callback

## Thanks
Thanks to Brandon Cannaday [@TheReddest](https://twitter.com/TheReddest) for his [Blog Article](https://www.getstructure.io/blog/how-to-connect-a-particle-photon-to-the-structure-iot-platform)

Thanks to GetStructure.io team for their free kits :D

## Questions ?
Send me a tweet to @CharifUs :)

## Troubleshoot

### SparkJson missing
```
Structure-MQTT-device/Structure-MQTT-device.h:38:33: fatal error: SparkJson/SparkJson.h: No such file or directory
 #include "SparkJson/SparkJson.h"
```
You need to add SPARKJSON library also from the community libraries to your project.



