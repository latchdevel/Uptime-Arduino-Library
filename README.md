# Uptime Lighted
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)
[![Compile Tests](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/CompileTests.yml/badge.svg)](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/CompileTests.yml)
[![Native Tests](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/NativeTests.yml/badge.svg)](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/NativeTests.yml)
[![Arduino Lint](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/ArduinoLint.yml/badge.svg)](https://github.com/latchdevel/Uptime-Arduino-Library/actions/workflows/ArduinoLint.yml)

Streamlined "uptime" library for Arduino to get the device runtime.

This header-only library implements "uptime" functionality using Arduino's internal milliseconds counter returned by the "millis()" function, available on all Arduino platforms.

The Arduino "millis()" function returns the **32-bit milliseconds counter** whose value is the number of milliseconds elapsed since startup.
The maximum value of this counter is (2^32)-1 = 4294967295 milliseconds, which resets after 49 days, 17 hours, 2 minutes, 47 seconds, and 295 milliseconds.

The Uptime Arduino Library uses a **32-bit seconds counter** to store the number of seconds elapsed since startup, which is reset after 4294967295 seconds, more than 136 years.

## Usage
The `uptime()` function updates counters and returns a human-readable "uptime" string, from **"00:00:00"** to the maximum **"49710d 06:28:15"**.
This function, or `update()`, must be called frequently to update the counters, at least once every 49.7 days.
```c++
const char* uptime(void); 
```
**Example:**
```c++
#include <Uptime.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println( uptime() );
  delay(1000);
}
```

**Output:**
```
00:00:00
00:00:01 
00:00:02
...
23:59:59
1d 00:00:00
1d 00:00:01
...
```

Try running this simple example on Arduino UNO here: [**WOKWI Uptime-Arduino-Library-Simple-Example**](https://wokwi.com/projects/414108225387053057)

Or try running the full example on Arduino UNO here: [**WOKWI Uptime-Arduino-Library-Complete-Example**](https://wokwi.com/projects/414108308610447361)

Or try running the full example on native platform here: [**ONLINE CPP non-Arduino Complete Example**](https://www.online-cpp.com/NIlDZ8UMSb)

## Similar libraries
 - **Arduino UpTime** https://github.com/jozef/Arduino-UpTime
 - **Uptime Library** https://github.com/YiannisBourkelis/Uptime-Library
 - **Uptime** https://github.com/XbergCode/Uptime

# License
Copyright (c) 2024 Jorge Rivera. All right reserved.

License GNU Lesser General Public License v3.0.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

See the [LICENSE](LICENSE.txt) file for license rights and limitations (lgpl-3.0).