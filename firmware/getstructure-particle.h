#ifndef GET_GESTURE_PARTICLE
#define GET_GESTURE_PARTICLE

#if defined(SPARK) || (PLATFORM_ID==88)
#include "spark_wiring_string.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_usbserial.h"
#elif defined(ARDUINO)
#include "Client.h"
#endif


// MQTT_MAX_PACKET_SIZE : Maximum packet size
// this size is total of [MQTT Header(Max:5byte) + Topic Name Length + Topic Name + Message ID(QoS1|2) + Payload]
#define MQTT_MAX_PACKET_SIZE 255

// MQTT_KEEPALIVE : keepAlive interval in Seconds
#define MQTT_KEEPALIVE 15

#define MQTTPROTOCOLVERSION 3
#define MQTTCONNECT     1 << 4  // Client request to connect to Server
#define MQTTCONNACK     2 << 4  // Connect Acknowledgment
#define MQTTPUBLISH     3 << 4  // Publish message
#define MQTTPUBACK      4 << 4  // Publish Acknowledgment
#define MQTTPUBREC      5 << 4  // Publish Received (assured delivery part 1)
#define MQTTPUBREL      6 << 4  // Publish Release (assured delivery part 2)
#define MQTTPUBCOMP     7 << 4  // Publish Complete (assured delivery part 3)
#define MQTTSUBSCRIBE   8 << 4  // Client Subscribe request
#define MQTTSUBACK      9 << 4  // Subscribe Acknowledgment
#define MQTTUNSUBSCRIBE 10 << 4 // Client Unsubscribe request
#define MQTTUNSUBACK    11 << 4 // Unsubscribe Acknowledgment
#define MQTTPINGREQ     12 << 4 // PING Request
#define MQTTPINGRESP    13 << 4 // PING Response
#define MQTTDISCONNECT  14 << 4 // Client is Disconnecting
#define MQTTReserved    15 << 4 // Reserved


#include "SparkJson/SparkJson.h"
#define STRUCTURE_BROKER "broker.getstructure.io"


namespace GetStructure
{
    class Device;
    class MQTT {
    /** types */
    public:
    typedef enum{
        QOS0 = 0,
        QOS1 = 1,
        QOS2 = 2,
    }EMQTT_QOS;
    
    private:
    #if defined(SPARK) || (PLATFORM_ID==88)
        TCPClient *_client;
    #elif defined(ARDUINO)
        Client *_client;
    #endif
        uint8_t buffer[MQTT_MAX_PACKET_SIZE];
        uint16_t nextMsgId;
        unsigned long lastOutActivity;
        unsigned long lastInActivity;
        bool pingOutstanding;
        //void (Device::*callback)(char*,uint8_t*,unsigned int);
        //MqttCallback callback;
        //typedef void (Device::*MqttQosCallback)(unsigned int);
        bool isQosCallback = false;
        uint16_t readPacket(uint8_t*);
        uint8_t readByte();
        bool write(uint8_t header, uint8_t* buf, uint16_t length);
        uint16_t writeString(const char* string, uint8_t* buf, uint16_t pos);
        String domain;
        uint8_t *ip;
        uint16_t port;
        Device *device;
    
    public:
        MQTT();
        bool connect(const char *, const char *, const char *);
        bool connect(const char *, const char *, EMQTT_QOS, uint8_t, const char *);
        bool connect(const char *, const char *, const char *, const char *, EMQTT_QOS, uint8_t, const char*);
        void disconnect();
        
        bool publish(const char *, const char *);
        bool publish(const char *, const char *, EMQTT_QOS, uint16_t *messageid);
        bool publish(const char *, const uint8_t *, unsigned int);
        bool publish(const char *, const uint8_t *, unsigned int, EMQTT_QOS, uint16_t *messageid);
        bool publish(const char *, const uint8_t *, unsigned int, bool);
        bool publish(const char *, const uint8_t *, unsigned int, bool, EMQTT_QOS, uint16_t *messageid);
        void setQosCallback();
        bool publishRelease(uint16_t messageid);
    
        bool subscribe(const char *);
        bool subscribe(const char *, EMQTT_QOS);
        bool unsubscribe(const char *);
        bool loop();
        bool isConnected();
        void setDevice(Device* device);
    };
  class Device
  {
    private:
      String deviceId;
	  String accessKey;
	  String accessSecret;
	  // Topic used to subscribe to Structure commands.
      String topicCommand;
	  // Topic used to publish state to Structure.
      String topicState;
	  // MQTT client.
	  GetStructure::MQTT client;
	  
	  void (*callback)(JsonObject&);
      
	  //void (Device::*mqttCallback)(char*,uint8_t*,unsigned int);
      
    public:
      Device(char* deviceId, char* accessKey, char* accessSecret);
	  // Callback signature for MQTT subscriptions.
	  void mqttCallback(char* topic, byte* payload, unsigned int length);
	  void mqttQosCallback(unsigned int qos);
	  bool publish(JsonObject& payload);
	  void connect(void (*callback)(JsonObject&));
      String getDeviceId();
	  bool loop();
	  bool isConnected();
  };
}

#endif
