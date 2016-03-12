# getstructure-particle
A [Particle Builder](https://build.particle.io/build)  library for integration with [Structure](https://www.getstructure.io/)

## About

This library serves as a wrapper for the [MQTT library](https://github.com/hirotakaster/MQTT) for the integration with [Structure](https://www.getstructure.io/) Broker.
It offers simplified methodes and an Device object to comunicate with [Structure](https://www.getstructure.io/)

## Getting started
A [getting started](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d) tutorial is availible at [Hackster.io](https://www.hackster.io/)

[https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d)

This  [getting started](https://www.hackster.io/charifmahmoudi/ez-device-lib-to-connect-particle-board-to-structure-0e624d) tutorial describes all the steps needed to integrates the library in your project.

## Dependencies

This library depends on the [SPARKJSON](https://github.com/menan/SparkJson) library that is availible as community library in the [Particle Builder](https://build.particle.io/build) 

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



Simplified Json-based push methode and callback

## Thanks
Thanks to Brandon Cannaday [@TheReddest](https://twitter.com/TheReddest) for his [Blog Article](https://www.getstructure.io/blog/how-to-connect-a-particle-photon-to-the-structure-iot-platform)

Thanks to GetStructure.io team for their free kits :D

## Questions ?
Send me a tweet to @CharifUs :)
