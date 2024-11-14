/*
   Test the example of using the "Uptime Arduino Library" on a non-Arduino platform.

   Build: g++ -std=c++11 -Wall -Wextra -Wpedantic -I../.. Uptime-demo.cpp -o Uptime-demo
   
   Copyright (c) 2024 Jorge Rivera. https://github.com/latchdevel/Uptime-Arduino-Library
   License GNU Lesser General Public License v3.0.
*/

#if !defined(ARDUINO)

#include <iostream>     // Header that defines the standard input/output stream objects
#include <chrono>       // Flexible collection of types that track time with varying degrees of precision
#include <thread>       // Threads enable programs to execute across several processor cores.

// Simulated Arduino "time" functions
int64_t t_start;  // Absolute start time for millis()
uint32_t r_start; // Relative start time for millis()

// Function to get the time in milliseconds since the system started
int64_t systemMillis(void) { 
   using namespace std::chrono;

   return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count(); 
}

// Returns the number of milliseconds elapsed since it started running
// ensuring the value is cast to 32 bits by using the uint32_t type
unsigned long millis(void) {
   return static_cast<uint32_t>(systemMillis() - t_start + r_start);
}

// Pauses the program for the specified amount of time in milliseconds
void delay(unsigned long ms) { 
   using namespace std::chrono;
   using namespace std::this_thread;
   
   sleep_for(milliseconds(ms)); 
}

// Custom function to set an arbitrary millis() value for testing purposes
__attribute__((weak)) void setMillisCustom(uint32_t new_millis) {
   // Set absolute start time to now
   t_start = systemMillis();

   // Set relative start time to new millis
   r_start = new_millis;
}

// Basic simulated Arduino Serial object for printing to "std::cout" using C++ iostream
struct {
   void begin(int) {}
   void end() {}
   void setTimeout(long) {} 
   void flush() { std::cout.flush(); }
   bool available() { return false; }
   int read() { return -1; }
   bool availableForWrite() { return true; }
   void write(uint8_t value) { std::cout << value; }
   template<typename T> void print(const T& value) { std::cout << value; }
   template<typename T> void println(const T& value) { std::cout << value << std::endl; }
   void println() { std::cout << std::endl; }
   operator bool() const { return true; }
} Serial;

// Main Arduino functions
void setup(void);
void loop(void);

#include "Uptime-demo.ino"

int main(){
   // Set absolute start time for millis()
   t_start = systemMillis();

   // Set relative start time for millis()
   r_start = 0;

   // Call the Arduino setup() function once
   setup();

   // Call the Arduino loop() function ~~constantly~~ once
   loop(); // for (;;) loop();

   return 0;
}
#endif
