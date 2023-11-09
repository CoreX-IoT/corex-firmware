#ifndef COREX_H
#define COREX_H

#include "CoreXClient.h"
#include "CoreXTimer.h"


#endif

// Check board
#if defined(ESP8266)
    #include <ESP8266WiFi.h>
#elif defined(ESP32)
    #include <WiFi.h>
#endif