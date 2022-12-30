#pragma once

//debug level definitions in ascending order:
#define DEBUG 1
#define INFO 2
#define WARN 3
#define CRITICAL 4

//technical spec:
#define BAUD_RATE 115200

/**
 * available functions: 
 * log_begin() starts the Serial communication.
 * log_xxx() logs a message on the defined log level.
 * 
 * log_begin()
 * log_debug(x)
 * log_info(x)
 * log_warn(x)
 * log_critical(x)
 *
 * user defined configuration:
 * If you want to debug via serial port at all, uncomment "USE_DEBUG".
 * Set "USE_LOG_LEVEL" to show the messages with according level(and higher)
 */
#define USE_LOGGER
#define USE_LOG_LEVEL INFO


/**
 * Implementation part
 * At the moment totally relies on HardwareSerial.h...
 */

#ifdef USE_LOGGER
    #include "HardwareSerial.h"
    #include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

    void __log_print_stump(){
        Serial.print(__FILE__);
        Serial.print(":");
        Serial.println(__LINE__);
        Serial.print("\t");
    }

    void __print_ln(const char* msg){
        Serial.println(msg);
    }
    void __print(const char* msg){
        Serial.print(msg);
    }

    #define log_begin() while (!Serial) Serial.begin(BAUD_RATE); log_debug("Serial connection initialized!");

    #if DEBUG >= USE_LOG_LEVEL
        #define log_debug(x)                Serial.print("[DEBUG] ");     __log_print_stump();   Serial.println(x);
        #define logf_debug(x, args...)      Serial.print("[DEBUG] ");     __log_print_stump();   Serial.printf(x, args); Serial.println();
    #endif

    #if INFO >= USE_LOG_LEVEL
        #define log_info(x)                 Serial.print("[INFO] ");      __log_print_stump();   Serial.println(x);
        #define logf_info(x, args...)       Serial.print("[INFO] ");      __log_print_stump();   Serial.printf(x, args); Serial.println();
    #endif
    #if WARN >= USE_LOG_LEVEL
        #define log_warn(x)                 Serial.print("[WARN] ");      __log_print_stump();   Serial.println(x);
        #define logf_warn(x, args...)       Serial.print("[WARN] ");      __log_print_stump();   Serial.printf(x, args); Serial.println();
    #endif
    #if CRITICAL >= USE_LOG_LEVEL
        #define log_critical(x)             Serial.print("[CRITICAL] ");  __log_print_stump();   Serial.println(x);
        #define logf_critical(x, args...)   Serial.print("[CRITICAL] ");  __log_print_stump();   Serial.printf(x, args); Serial.println();
    #endif
#endif

#ifndef log_begin()
    #define log_begin()
#endif
#ifndef log_debug(x)
    #define log_debug(x)
    #define logf_debug(x, args...)
#endif

#ifndef log_info(x)
    #define log_info(x)
    #define logf_info(x, args...)
#endif
#ifndef log_warn(x)
    #define log_warn(x)
    #define logf_warn(x, args...)
#endif
#ifndef log_critical(x)
    #define log_critical(x)
    #define logf_critical(x, args...)
#endif