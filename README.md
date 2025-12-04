<!-- TITLE -->
<h1 align="center">📸 ESP32-CAM-CH340 V01 — Configuration & Compatibility Guide</h1>

<p align="center">
  <strong>A complete, verified configuration for the ESP32-S-CAM-CH340 V01 (non-AI Thinker) board</strong><br>
  Fixes the <code>ESP_ERR_NOT_SUPPORTED</code>, <code>0x106</code>, and unsupported camera errors.
</p>

<p align="center">
  <img src="images/board_front.jpg" height="220" alt="Board Front">
  <img src="images/board_back.jpg" height="220" alt="Board Back">
</p>

---

## 🏷️ Badges

<p align="center">
  <img src="https://img.shields.io/badge/Board-ESP32--CAM--CH340_V01-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Verified%20Working-brightgreen?style=for-the-badge">
  <img src="https://img.shields.io/badge/Camera-OV2640-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Requires-Custom%20Pins-critical?style=for-the-badge">
</p>

---

# ⚠️ Critical Notice

This guide is **ONLY** for the **ESP32-S-CAM-CH340 V01** board.  
Using AI Thinker pinouts will cause:

```
E (39) camera: Detected camera not supported.
E (39) camera: Camera probe failed with error 0x106
Camera init failed with error 0x106
```

---

# 🔍 Hardware Identification

Verify ALL fields below match your board:

| Feature | What to Look For |
|--------|------------------|
| **Main Chip** | ESP-32S (printed on RF shield) |
| **Board Revision** | V01 near GPIO pins |
| **USB Interface** | Built-in CH340 (Micro-USB port) |
| **Common Markings** | ESP32-CAM, ESP32-CAM-MB, OV2640 |

---

# 🚀 Quick Start Checklist

✔ Use the **custom** `camera_pins_v01.h`  
✔ Select **AI Thinker ESP32-CAM** in Arduino IDE  
✔ Follow the **special upload sequence**  
✔ Power with **5V / 2A** (not USB from a PC)

---

# 📁 Repository Structure

```
ESP32-CAM-CH340-V01-Guide/
├── README.md
├── camera_pins_v01.h
├── images/
│   ├── board_front.jpg
│   └── board_back.jpg
└── examples/
    └── BasicWebServer.ino
```

---

# 🔧 Custom Pin Configuration (Required Fix)

**Why?**  
The V01 board uses **GPIO0 for XCLK**, not GPIO21 like AI Thinker boards.

## Step 1 — Create `camera_pins_v01.h`

```cpp
// camera_pins_v01.h
// ESP32-S-CAM-CH340 V01 Custom Configuration
// XCLK MUST be GPIO0 (NOT GPIO21)

#if defined(CAMERA_MODEL_ESP32S_V01_CH340)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define LED_GPIO_NUM      4
#endif
```

---

# 🛠️ Step 2 — Modify Arduino Example

Open:  
**File → Examples → ESP32 → Camera → CameraWebServer**

### Replace camera model section with:

```cpp
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_AI_THINKER
#define CAMERA_MODEL_ESP32S_V01_CH340
```

### Add include at the top:

```cpp
#include "camera_pins_v01.h"
```

---

# ⚙️ Step 3 — Arduino IDE Configuration

| Setting | Value |
|--------|-------|
| **Board** | AI Thinker ESP32-CAM |
| **Partition Scheme** | Huge APP (3MB No OTA / 1MB SPIFFS) |
| **Flash Frequency** | 40MHz |
| **Upload Speed** | 115200 |
| **Core Debug Level** | None |

---

# 🚨 Step 4 — Special Upload Sequence

GPIO0 is used for XCLK → Board cannot enter flash mode normally.

Follow this EXACTLY:

1. Short **IO0 → GND**  
2. Press **RESET**  
3. Click **Upload** in Arduino IDE  
4. When IDE shows **Connecting…**, remove IO0-GND short  
5. Board reboots → camera initializes ✔

---

# ⚡ Troubleshooting

| Problem | Solution |
|---------|----------|
| **Camera init failed** | Reseat ribbon + use 5V/2A power |
| **No serial port (Linux)** | Install CH340: `sudo apt install ch34x` |
| **PSRAM not detected** | Use *Huge APP* partition |
| **Random reboots** | Power instability → must use proper adapter |

---

# 🤝 Contributing & Support

Found a different board revision? Please help!

- Open an Issue with **front/back board photos**  
- Share your **working pinout**  
- Submit Pull Requests with improvements  

### If requesting help, include:

📸 Photos of your board  
📝 Serial Monitor error messages  
⚙️ Your Arduino IDE configuration  
📂 Your `camera_pins_v01.h`  

---

<h3 align="center">⭐ If this repo helped you, consider giving it a star!</h3>

