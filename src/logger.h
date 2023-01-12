#pragma once

//debug level definitions in ascending order:
#define DEBUG 1
#define INFO 2
#define WARN 3
#define CRITICAL 4

//technical spec:
#define BAUD_RATE 38400
#define LOGGER_MAX_MESSAGE_LENGTH 150

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
 * If you want to use this logger without Arduino 
 */
#define USE_LOGGER
#define USE_LOG_LEVEL DEBUG

//#undef ARDUINO
#ifndef PRINT_METHOD
    #ifdef ARDUINO
        #include "Arduino.h"
        #define log_begin() while (!Serial) Serial.begin(BAUD_RATE); logf_info("Serial connection initialized, logging enabled, loglevel: %d", USE_LOG_LEVEL);
        #define PRINT_METHOD(x) Serial.print(x);
        #define MILLIS_FUNCTION millis()
    #else
        #error please define the "PRINT_METHOD" which will be used for printing/logging your messages.(in case of Arduino this defaults to Serial.print(x))
        #undef USE_LOGGER
    #endif
#endif

#ifdef USE_LOGGER
        #include <stdio.h>      //vsnprintf, vsnprintf_P
        #include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

        void __printf(const char* msg, ...){
            char buf[LOGGER_MAX_MESSAGE_LENGTH];
            va_list args;
            va_start(args, msg);
            vsnprintf(buf, sizeof(buf), msg, args);
            va_end(args);
            PRINT_METHOD(msg);
            PRINT_METHOD("\r\n");
        }

        void __printf_P(const char* msg, ...){
            char buf[LOGGER_MAX_MESSAGE_LENGTH];
            va_list args;
            va_start(args, msg);
            vsnprintf_P(buf, sizeof(buf), msg, args);
            va_end(args);
            PRINT_METHOD(msg);
            PRINT_METHOD("\r\n");
        }
        
        void __print(const char* msg){
            PRINT_METHOD(msg);
        }
        void __print(int msg){
            __printf("%d", msg);
        }
        void __print(long msg){
            __printf("%d", msg);
        }
        void __print(unsigned int msg){
            __printf("%u", msg);
        }
        void __print(unsigned long msg){
            __printf("%u", msg);
        }
        void __print(float msg){
            __printf("%f", msg);
        }
        void __print(double msg){
            __printf("%f", msg);
        }
        void __println(const char* msg){
            PRINT_METHOD(msg);
            PRINT_METHOD("\r\n");
        }

        #if DEBUG >= USE_LOG_LEVEL
            #ifdef MILLIS_FUNCTION
                #define DEBUG_FORMAT __printf_P(PSTR("[DEBUG] time: %lu; %s:%d\r\n\t"), MILLIS_FUNCTION(), __FILE__, __LINE__);
            #elif
                #define DEBUG_FORMAT __printf_P(P_STR("[DEBUG] %s:%s\r\n\t"), __FILE__, __LINE__);
            #endif
            #define log_debug(x)             DEBUG_FORMAT __println(x);
            #define logf_debug(x, args...)   DEBUG_FORMAT __printf(x, args);
            #define logf_P_debug(x, args...) DEBUG_FORMAT __printf_P(x, args);
        #endif

        #if INFO >= USE_LOG_LEVEL
            #define INFO_FORMAT __print("[INFO] ");
            #define log_info(x)             INFO_FORMAT; __println(x);
            #define logf_info(x, args...)   INFO_FORMAT; __printf(x, args);
            #define logf_P_info(x, args...) INFO_FORMAT; __printf_P(x, args);
        #endif
        #if WARN >= USE_LOG_LEVEL
            #ifdef MILLIS_FUNCTION
                #define WARN_FORMAT __printf_P(PSTR("[WARN] time: %lu; %s:%d\r\n\t"), MILLIS_FUNCTION, __FILE__, __LINE__);
            #elif
                #define WARN_FORMAT __printf_P(P_STR("[WARN] %s:%s\r\n\t"), __FILE__, __LINE__);
            #endif
            #define log_warn(x)             WARN_FORMAT __println(x);
            #define logf_warn(x, args...)   WARN_FORMAT __printf(x, args);
            #define logf_P_warn(x, args...) WARN_FORMAT __printf_P(x, args);
        #endif
        #if CRITICAL >= USE_LOG_LEVEL
            #ifdef MILLIS_FUNCTION
                #define CRITICAL_FORMAT __printf_P(PSTR("[CRITICAL] time: %lu; %s:%d\r\n\t"), MILLIS_FUNCTION(), __FILE__, __LINE__);
            #elif
                #define CRITICAL_FORMAT __printf(P_STR("[CRITICAL] %s:%s\r\n\t"), __FILE__, __LINE__);
            #endif
            #define log_critical(x)             CRITICAL_FORMAT; __println(x);
            #define logf_critical(x, args...)   CRITICAL_FORMAT; __printf(x, args);
            #define logf_P_critical(x, args...) CRITICAL_FORMAT; __printf_P(x, args);
        #endif
    #else
        #ifndef log_begin
            #define log_begin()
        #endif
        #ifndef log_debug
            #define log_debug(x)
            #define logf_debug(x, args...)
        #endif

        #ifndef log_info
            #define log_info(x)
            #define logf_info(x, args...)
        #endif
        #ifndef log_warn
            #define log_warn(x)
            #define logf_warn(x, args...)
        #endif
        #ifndef log_critical
            #define log_critical(x)
            #define logf_critical(x, args...)
        #endif
#endif
