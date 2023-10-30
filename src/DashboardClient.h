#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

// include functional API if possible. remove min and max macros for some
// platforms as they will be defined again by Arduino later
#if defined(ESP8266) || (defined ESP32)
#include <functional>
#define MQTT_HAS_FUNCTIONAL 1
#elif defined(__has_include)
#if __has_include(<functional>)
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif
#include <functional>
#define MQTT_HAS_FUNCTIONAL 1
#else
#define MQTT_HAS_FUNCTIONAL 0
#endif
#else
#define MQTT_HAS_FUNCTIONAL 0
#endif

#include <Arduino.h>
#include <Client.h>
#include <Stream.h>

extern "C" {
#include "lwmqtt/lwmqtt.h"
}

typedef uint32_t (*DashboardClockSource)();

typedef struct {
  uint32_t start;
  uint32_t timeout;
  DashboardClockSource millis;
} lwmqtt_arduino_timer_t;

typedef struct {
  Client *client;
} lwmqtt_arduino_network_t;

class Dashboard;

typedef void (*DashboardCallbackSimple)(String &topic, String &payload);
typedef void (*DashboardCallbackAdvanced)(Dashboard *client, char topic[], char bytes[], int length);
#if MQTT_HAS_FUNCTIONAL
typedef std::function<void(String &topic, String &payload)> DashboardCallbackSimpleFunction;
typedef std::function<void(Dashboard *client, char topic[], char bytes[], int length)>
    DashboardCallbackAdvancedFunction;
#endif

typedef struct {
  Dashboard *client = nullptr;
  DashboardCallbackSimple simple = nullptr;
  DashboardCallbackAdvanced advanced = nullptr;
#if MQTT_HAS_FUNCTIONAL
  DashboardCallbackSimpleFunction functionSimple = nullptr;
  DashboardCallbackAdvancedFunction functionAdvanced = nullptr;
#endif
} DashboardCallback;

class Dashboard {
 private:
  size_t bufSize = 0;
  uint8_t *readBuf = nullptr;
  uint8_t *writeBuf = nullptr;

  uint16_t keepAlive = 10;
  bool cleanSession = true;
  uint32_t timeout = 1000;

  Client *netClient = nullptr;
  const char *hostname = nullptr;
  IPAddress address;
  int port = 0;
  lwmqtt_will_t *will = nullptr;
  DashboardCallback callback;

  lwmqtt_arduino_network_t network = {nullptr};
  lwmqtt_arduino_timer_t timer1 = {0, 0, nullptr};
  lwmqtt_arduino_timer_t timer2 = {0, 0, nullptr};
  lwmqtt_client_t client = lwmqtt_client_t();

  bool _connected = false;
  lwmqtt_return_code_t _returnCode = (lwmqtt_return_code_t)0;
  lwmqtt_err_t _lastError = (lwmqtt_err_t)0;

 public:
  void *ref = nullptr;

  explicit Dashboard(int bufSize = 128);

  ~Dashboard();

  void begin(Client &_client);
  void begin(const char _hostname[], Client &_client) { this->begin(_hostname, 1883, _client); }
  void begin(const char _hostname[], int _port, Client &_client) {
    this->begin(_client);
    this->setHost(_hostname, _port);
  }
  void begin(IPAddress _address, Client &_client) { this->begin(_address, 1883, _client); }
  void begin(IPAddress _address, int _port, Client &_client) {
    this->begin(_client);
    this->setHost(_address, _port);
  }

  void onMessage(DashboardCallbackSimple cb);
  void onMessageAdvanced(DashboardCallbackAdvanced cb);
#if MQTT_HAS_FUNCTIONAL
  void onMessage(DashboardCallbackSimpleFunction cb);
  void onMessageAdvanced(DashboardCallbackAdvancedFunction cb);
#endif

  void setClockSource(DashboardClockSource cb);

  void setHost(const char _hostname[]) { this->setHost(_hostname, 1883); }
  void setHost(const char hostname[], int port);
  void setHost(IPAddress _address) { this->setHost(_address, 1883); }
  void setHost(IPAddress _address, int port);

  void setWill(const char topic[]) { this->setWill(topic, ""); }
  void setWill(const char topic[], const char payload[]) { this->setWill(topic, payload, false, 0); }
  void setWill(const char topic[], const char payload[], bool retained, int qos);
  void clearWill();

  void setKeepAlive(int keepAlive);
  void setCleanSession(bool cleanSession);
  void setTimeout(int timeout);

  void setOptions(int _keepAlive, bool _cleanSession, int _timeout) {
    this->setKeepAlive(_keepAlive);
    this->setCleanSession(_cleanSession);
    this->setTimeout(_timeout);
  }

  bool connect(const char clientId[], bool skip = false) { return this->connect(clientId, nullptr, nullptr, skip); }
  bool connect(const char clientId[], const char username[], bool skip = false) {
    return this->connect(clientId, username, nullptr, skip);
  }
  bool connect(const char clientID[], const char username[], const char password[], bool skip = false);

  bool publish(const String &authProject, const String &topic) { 
    return this->publish((authProject +"/"+topic).c_str(), ""); 
  }
  bool publish(const char topic[]) { 
    return this->publish(topic, "");
  }
  bool publish(const String &authProject, const String &topic, const String &payload) {
    return this->publish((authProject +"/"+topic).c_str(), payload.c_str(), true, 1);
  }
  bool publish(const String &authProject, const String &topic, const String &payload, bool retained, int qos) {
    return this->publish((authProject +"/"+topic).c_str(), payload.c_str(), retained, qos);
  }
  bool publish(const char topic[], const String &payload) {
    return this->publish(topic, payload.c_str(), true, 1);
  }
  bool publish(const char topic[], const String &payload, bool retained, int qos) {
    return this->publish(topic, payload.c_str(), retained, qos);
  }
  bool publish(const char topic[], const char payload[]) {
    return this->publish(topic, (char *)payload, (int)strlen(payload), true, 1);
  }
  bool publish(const char topic[], const char payload[], bool retained, int qos) {
    return this->publish(topic, (char *)payload, (int)strlen(payload), retained, qos);
  }
  bool publish(const char topic[], const char payload[], int length) {
    return this->publish(topic, payload, length, false, 0);
  }
  bool publish(const char topic[], const char payload[], int length, bool retained, int qos);

  bool subscribe(const String &topic) { return this->subscribe(topic.c_str(), 1); }
  bool subscribe(const String &topic, int qos) { return this->subscribe(topic.c_str(), qos); }
  bool subscribe(const char topic[]) { return this->subscribe(topic, 1); }
  bool subscribe(const char topic[], int qos);

  bool unsubscribe(const String &topic) { return this->unsubscribe(topic.c_str()); }
  bool unsubscribe(const char topic[]);

  bool loop();
  bool connected();

  lwmqtt_err_t lastError() { return this->_lastError; }
  lwmqtt_return_code_t returnCode() { return this->_returnCode; }

  bool disconnect();

 private:
  void close();
};

#endif