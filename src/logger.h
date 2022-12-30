#pragma once

//debug level definitions in ascending order:
#define DEBUG 1
#define INFO 2
#define WARN 3
#define CRITICAL 4

//technical spec:
#define BAUD_RATE 115200

/**
 * user defined configuration:
 * If you want to debug via serial port at all, uncomment "USE_DEBUG".
 * Set "USE_LOG_LEVEL" to show the messages with according level(and higher)
 */
#define USE_LOGGER
#define USE_LOG_LEVEL INFO

#ifdef USE_LOGGER
    #include "Arduino.h"
    #define log_begin Serial.begin(BAUD_RATE);

    void __log_print_stump(){
        Serial.print(__FILE__);
        Serial.print(":");
        Serial.println(__LINE__);
        Serial.print("\t");
    }

    void print_ln(const char* msg){
        Serial.println(msg);
    }
    void print(const char* msg){
        Serial.print(msg);
    }

    #if DEBUG >= USE_LOG_LEVEL
        #define log_debug(x)    print("[DEBUG] ");     __log_print_stump();    println(x)
    #endif
    #if INFO >= USE_LOG_LEVEL
        #define log_info(x)     print("[INFO] ");      __log_print_stump();    println(x)
    #endif
    #if WARN >= USE_LOG_LEVEL
        #define log_warn(x)     print("[WARN] ");      __log_print_stump();    println(x)
    #endif
    #if CRITICAL >= USE_LOG_LEVEL
        #define log_critical(x) print("[CRITICAL] ");  __log_print_stump();    println(x)
    #endif
#endif

//definiere als leer, wenn nicht definiert
#ifndef log_debug(x)
    #define log_debug(x)
#endif

#ifndef log_info(x)
    #define log_info(x)
#endif

#ifndef log_warn(x)
    #define log_warn(x)
#endif

#ifndef log_critical(x)
    #define log_critical(x)
#endif
