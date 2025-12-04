# ESP32-CAM-CH340-V01-Guide
⚠️ BOARD IDENTIFICATION IS CRITICAL
Your board is NOT a standard AI Thinker ESP32-CAM. If you have an "ESP-32S" chip, a "V01" marking, and a built-in CH340 USB chip, this guide is for you.

Common symptoms of using the wrong configuration:

E (xx) camera: Detected camera not supported.

Camera probe failed with error 0x106

Camera works in bootloader but fails in normal mode

🛠️ The Fix: Custom Pin Configuration
The core issue is the XCLK pin. Most guides use GPIO21, but your V01 board uses GPIO0.

Step 1: Create Custom Pin File
Create a file called camera_pins_v01.h in your project folder 
Step 2: Modify CameraWebServer Example
Open Arduino IDE

Go to: File > Examples > ESP32 > Camera > CameraWebServer

Find this section (around line 30-50):

cpp
// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_AI_THINKER
// ... etc ...
Comment out ALL lines and add your custom model:

cpp
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_AI_THINKER
#define CAMERA_MODEL_ESP32S_V01_CH340  // ADD THIS LINE
Add include at the top of the sketch (after other includes):

cpp
#include "camera_pins_v01.h"
Step 3: Configure Arduino IDE
Setting	Value
Board	AI Thinker ESP32-CAM
Partition Scheme	Huge APP (3MB No OTA/1MB SPIFFS)
Flash Frequency	40MHz
Upload Speed	115200
Step 4: Upload Sequence (CRITICAL!)
Because GPIO0 is used for XCLK, you MUST follow this sequence:

Short IO0 to GND on the board

Press RESET button

Start upload in Arduino IDE

Remove IO0-GND short when IDE says "Connecting..."

Board will reboot and camera should work

🔍 Troubleshooting
Problem	Solution
"Camera init failed"	Check cable connection; ensure 5V/2A power
No /dev/ttyUSB* on Linux	Install CH340 driver: sudo apt install ch34x
WiFi unstable	Add external antenna to u.FL connector
PSRAM not detected	Verify Partition Scheme is "Huge APP"
📁 Repository Files
text
ESP32-CAM-CH340-V01-Guide/
├── README.md                    # This guide
├── camera_pins_v01.h            # Custom pin configuration
├── images/                      # Board photos for identification
│   ├── front_view.jpg
│   └── back_view.jpg
└── examples/
    └── BasicCameraExample.ino   # Minimal working example
🤝 Contributing
Found another variation of this board? Please open an Issue or Pull Request with:

Clear photos of your board (front/back)

What configuration worked for you

Serial monitor output

