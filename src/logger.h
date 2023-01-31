#pragma once

//debug level definitions in ascending order:
#define DEBUG 1
#define INFO 2
#define WARN 3
#define CRITICAL 4

//technical spec:
#ifndef BAUD_RATE
    #define BAUD_RATE 115200
#endif
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
 * If you want to use this logger without Arduino, simply do the following lines:
 * Remember to 
 * __________
 * #define USE_LOGGER
 * #define USE_LOG_LEVEL DEBUG          //or a different log level (see above). This will display the messages of this and higher levels.
 * #define PRINT_FUNCTION Serial.print  //a printfunction (Arduino's as example)
 * #define MILLIS_FUNCTION millis       //function for timestamp. Expected as milliseconds since boot, but everything else should work as well
 *___________
 */
#ifndef PRINT_FUNCTION
    #ifdef ARDUINO
        #include "Arduino.h"
        #define log_begin() while (!Serial) Serial.begin(BAUD_RATE); logf_info("Serial connection initialized, logging enabled, loglevel: %d", USE_LOG_LEVEL);
        #define PRINT_FUNCTION Serial.print;
        #define MILLIS_FUNCTION millis
    #else
        #error please define the "PRINT_FUNCTION" which will be used for printing/logging your messages.(in case of Arduino this defaults to Serial.print(x))
        #warning to get a custom setup running, you will need the following:
        #warning Remember to initiate the connection in case of Serial connections. This will not be done by this logger!
        #warning #define USE_LOGGER                   //to enable the logger at all
        #warning #define USE_LOG_LEVEL DEBUG          //or a different log level (see above). This will print the messages of this and higher log levels.
        #warning #define PRINT_FUNCTION Serial.print  //a printfunction (Arduino's as example)
        #warning #define MILLIS_FUNCTION millis       //function for timestamp. Expected as milliseconds since boot, but everything else should work as well
        #undef USE_LOGGER
    #endif
#endif

#ifdef USE_LOGGER
        #include <stdio.h>      //vsnprintf
        #include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

        extern void __printf(const char* msg, ...){
            char buf[LOGGER_MAX_MESSAGE_LENGTH];
            va_list args;
            va_start(args, msg);
            vsnprintf(buf, sizeof(buf), msg, args);
            va_end(args);
            PRINT_FUNCTION(buf);
        }
        
        void __print(const char* msg){
            PRINT_FUNCTION(msg);
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
        extern void __println(const char* msg){
            PRINT_FUNCTION(msg);
            PRINT_FUNCTION("\r\n");
        }

        #if DEBUG >= USE_LOG_LEVEL
            #ifndef DEBUG_FORMAT
                #ifdef MILLIS_FUNCTION
                    #define DEBUG_FORMAT __printf("[DEBUG] time: %lu; %s:%d\n\r\t", MILLIS_FUNCTION(), __FILE__, __LINE__);
                #else
                    #define DEBUG_FORMAT __printf("[DEBUG] %s:%s\n\r\t", __FILE__, __LINE__);
                #endif
            #endif
            #define log_debug(x)             DEBUG_FORMAT; __print(x);
            #define log_debug_ln(x)          DEBUG_FORMAT; __println(x);
            #define logf_debug(x, args...)   DEBUG_FORMAT; __printf(x, args);
        #endif

        #if INFO >= USE_LOG_LEVEL
            #ifndef INFO_FORMAT
                #define INFO_FORMAT __print("[INFO] ");
            #endif
            #define log_info(x)             INFO_FORMAT; __print(x);
            #define log_info_ln(x)          INFO_FORMAT; __println(x);
            #define logf_info(x, args...)   INFO_FORMAT; __printf(x, args);
        #endif
        #if WARN >= USE_LOG_LEVEL
            #ifndef WARN_FORMAT
                #ifdef MILLIS_FUNCTION
                    #define WARN_FORMAT __printf("[WARN] time: %lu; %s:%d\r\n\t", MILLIS_FUNCTION(), __FILE__, __LINE__);
                #else
                    #define WARN_FORMAT __printf("[WARN] %s:%s\r\n\t", __FILE__, __LINE__);
                #endif
            #endif
            #define log_warn(x)             WARN_FORMAT; __print(x);
            #define log_warn_ln(x)          WARN_FORMAT; __println(x);
            #define logf_warn(x, args...)   WARN_FORMAT; __printf(x, args);
        #endif
        #if CRITICAL >= USE_LOG_LEVEL
            #ifndef CRITICAL_FORMAT
                #ifdef MILLIS_FUNCTION
                    #define CRITICAL_FORMAT __printf("[CRITICAL] time: %lu; %s:%d\r\n\t", MILLIS_FUNCTION(), __FILE__, __LINE__);
                #else
                    #define CRITICAL_FORMAT __printf("[CRITICAL] %s:%s\r\n\t", __FILE__, __LINE__);
                #endif
            #endif
            #define log_critical(x)             CRITICAL_FORMAT; __print(x);
            #define log_critical_ln(x)          CRITICAL_FORMAT; __println(x);
            #define logf_critical(x, args...)   CRITICAL_FORMAT; __printf(x, args);
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
