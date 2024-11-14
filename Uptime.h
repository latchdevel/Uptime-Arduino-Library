/*
   Streamlined "uptime" library for Arduino to get the device runtime.

   Copyright (c) 2024 Jorge Rivera. https://github.com/latchdevel/Uptime-Arduino-Library
   License GNU Lesser General Public License v3.0.

   This header-only library implements "uptime" functionality using Arduino's internal milliseconds
   counter returned by the "millis()" function available on all Arduino platforms.

   The Arduino "millis()" function returns a 32-bit milliseconds counter whose value is the number 
   of milliseconds elapsed since startup. The maximum value of this counter is (2^32)-1 = 4294967295
   milliseconds, which resets after 49 days, 17 hours, 2 minutes, 47 seconds, and 295 milliseconds.

   The Uptime static class uses a 32-bit seconds counter "uptime_seconds" to store the number of
   seconds elapsed since startup, which is reset after 4294967295 seconds, more than 136 years.

   The "uptime()" function updates the counters and returns a human-readable "uptime" string as
   a const char*, from "00:00:00" to the maximum "49710d 06:28:15".

   The "update()" function updates the counters and returns the 32-bit seconds counter as a uint32_t.

   This functions must be called frequently to update the counters, at least once every 49.7 days.
*/

#ifndef UPTIME_H_
#define UPTIME_H_

#ifndef UPTIME_BUFFER_SIZE
#define UPTIME_BUFFER_SIZE 16
#endif

#include <stdio.h>   // snprintf()
#include <stdint.h>  // uint32_t

// Arduino millis() function from wiring.c
extern unsigned long millis(void);

// Custom definable function for non-Arduino platforms to set an arbitrary millis() value for testing purposes
void setMillisCustom(uint32_t new_millis) __attribute__((weak));

// Pure static class "Uptime" for the Arduino development environment
class Uptime {
   private:
      static char buffer[UPTIME_BUFFER_SIZE];
      static volatile uint16_t period_counter;      // Number of completed periods of 49.7 days, up to a maximum of 1000
      static volatile uint32_t uptime_seconds;      // Number of seconds elapsed since start, up to 4294967295, more than 136 years

   public:
      static constexpr float PERIOD{4294967.295};   // Number of seconds in a period of 49 days, 17 hours, 2 minutes, 47 seconds, and 295 miliseconds

      // Update and get seconds counter, from millis() as default
      static uint32_t update(uint32_t current_millis = millis()) {

         // Get current seconds from the given milliseconds
         uint32_t current_seconds{current_millis / 1000U}; 

         // Check if the current seconds are within the current period
         if ( uptime_seconds > ((period_counter * PERIOD) + current_seconds)) {

            // Otherwise, increment the period counter (object of volatile-qualified type)
            period_counter = period_counter + 1;
         }

         // Update seconds counter (object of volatile-qualified type)
         uptime_seconds = (period_counter * PERIOD) + current_seconds;

         // Return seconds counter
         return uptime_seconds;
      }

      // Converts any seconds counter to a human-readable "uptime" const char* string
      // from "00:00:00" to maximum "49710d 06:28:15", more than 136 years.
      static const char* toString(uint32_t uptime) {

         uint32_t tmp_uptime{uptime};
         uint8_t     seconds;
         uint8_t     minutes;
         uint8_t       hours;
         uint16_t       days;

         seconds    = tmp_uptime % 60;
         tmp_uptime = tmp_uptime / 60;

         minutes    = tmp_uptime % 60;
         tmp_uptime = tmp_uptime / 60;

         hours      = tmp_uptime % 24;
         days       = tmp_uptime / 24;

         if (days>0) {
            snprintf(buffer, sizeof(buffer), "%dd %02d:%02d:%02d", days, hours, minutes, seconds);
         } else {
            snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);
         }
                                                                                                         
         return buffer;
      }

      // Get the "uptime" const char* string from the updated seconds counter
      static const char* uptime(void) {
         return toString(update());
      }

      // Set the millis() counter "timer0_millis" to any value for testing purposes
      static void setMillis(uint32_t new_millis) {

         // Call a custom function for non-Arduino platforms if it has been defined
         #pragma GCC diagnostic push 
         #pragma GCC diagnostic ignored "-Waddress"
         if (setMillisCustom) {
            setMillisCustom(new_millis);
         } else {
            #if defined(__AVR__)
               extern volatile unsigned long timer0_millis;
               // Ensure this cannot be disrupted
               uint8_t oldSREG = SREG;
               cli();
                  timer0_millis = new_millis;
               SREG = oldSREG;
            #else
               #if defined(ARDUINO)
                  #pragma message("Non-AVR Arduino platform - Disabling setMillis()")
               #endif  
            #endif 
         }
         #pragma GCC diagnostic pop

         // Reset main counters
         period_counter = 0;
         uptime_seconds = 0;
      } 
};

// Initialize static class member variables
volatile uint32_t Uptime::uptime_seconds{0};
volatile uint16_t Uptime::period_counter{0};
char Uptime::buffer[UPTIME_BUFFER_SIZE]{0};

// "Trailing return type" functions for the main "class methods"
auto update(void) -> uint32_t{return Uptime::update();}
auto uptime(void) -> const char*{return Uptime::uptime();}

#endif // UPTIME_H_
