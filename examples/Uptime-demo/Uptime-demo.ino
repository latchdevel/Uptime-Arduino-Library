/*
   Example of using the "Uptime Arduino Library" to track and display device runtime.
   
   Copyright (c) 2024 Jorge Rivera. https://github.com/latchdevel/Uptime-Arduino-Library
   License GNU Lesser General Public License v3.0.
*/

#include <Uptime.h>

void setup() {

   Serial.begin(115200);
   Serial.println("Begin!");
   
   for (int i = 0; i<3 ; i++){
      Serial.print(uptime());
      Serial.print(" seconds:");
      Serial.print(update());
      Serial.print(" millis:");
      Serial.println(millis());
      delay(1000);
   }

   Serial.println("\nJumping forward to one hour");
   Uptime::setMillis(3600*1000UL);

   for (int i = 0; i<3 ; i++){
      Serial.print(uptime());
      Serial.print(" seconds:");
      Serial.print(update());
      Serial.print(" millis:");
      Serial.println(millis());
      delay(1000);
   }

   Serial.println("\nJumping back to five minutes");
   Uptime::setMillis(300*1000UL);

   for (int i = 0; i<3 ; i++){
      Serial.print(uptime());
      Serial.print(" seconds:");
      Serial.print(update());
      Serial.print(" millis:");
      Serial.println(millis());
      delay(1000);
   }

   Serial.println("\nJumping forward to just before the end of one period");
   Uptime::setMillis((Uptime::PERIOD-1)*1000UL);

   for (int i = 0; i<3 ; i++){
      Serial.print(uptime());
      Serial.print(" seconds:");
      Serial.print(update());
      Serial.print(" millis:");
      Serial.println(millis());
      delay(1000);
   }

   Serial.println("\nJumping back to just before the end of one day");
   Uptime::setMillis((24*3600UL*1000UL)-1000);

   for (int i = 0; i<3 ; i++){
      Serial.print(uptime());
      Serial.print(" seconds:");
      Serial.print(update());
      Serial.print(" millis:");
      Serial.println(millis());
      delay(1000);
   }

   Serial.println("End.");
   Serial.flush(); 
}

void loop() {}

/* The output should be similar to this:

Begin!
00:00:00 seconds:0 millis:1
00:00:01 seconds:1 millis:1001
00:00:02 seconds:2 millis:2001

Jumping forward to one hour
01:00:00 seconds:3600 millis:3600001
01:00:01 seconds:3601 millis:3601002
01:00:02 seconds:3602 millis:3602004

Jumping back to five minutes
00:05:00 seconds:300 millis:300001
00:05:01 seconds:301 millis:301003
00:05:02 seconds:302 millis:302003

Jumping forward to just before the end of one period
49d 17:02:46 seconds:4294966 millis:4294966530
49d 17:02:47 seconds:4294967 millis:235
49d 17:02:48 seconds:4294968 millis:1237

Jumping back to just before the end of one day
23:59:59 seconds:86399 millis:86399001
1d 00:00:00 seconds:86400 millis:86400003
1d 00:00:01 seconds:86401 millis:86401004
End.

*/
