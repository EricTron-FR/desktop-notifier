# GlowBox - Desktop Notification Light

A simple and clean desktop notifier made with an ESP32 and a red LED. When you receive a notification (or trigger any webhook), the LED glows through the minimalist diffused panel.

![GlowBox](images/glowbox.gif) 

## 🔔 How it works

The ESP32 runs a basic webserver with a `/notify` endpoint. Call this URL from your phone, home automation, or any service, and the LED lights up. That's it!

## ✨ Use Cases

- Get a visual alert for phone notifications (Line, Messenger, WhatsApp...)
- Monitor your server (ping when it goes down)
- E-commerce alerts (new order = LED blinks)
- Home automation triggers
- Discord/Slack mentions
- Really, anything that can send an HTTP request!

## 📦 What you need

**Electronics:**
- ESP32 WROOM board
- Red LED (5mm)
- 220Ω resistor
- Some jumper wires
- USB cable

**3D Printing:**
- Download the STL files from [MakerWorld](https://makerworld.com/fr/models/1897218-desktop-notifier-with-esp32-vroom#profileId-2032782)

## 🔌 Wiring

Simple circuit - just 3 connections:
```
GPIO 23 → 220Ω Resistor → LED (+) long leg
LED (-) short leg → GND
```

![Wiring Diagram](images/wiring.png) 

## 🛠️ Assembly

1. Print the case (white PLA) and front panel (black PLA) - or any color you want!
2. Solder your LED + resistor + wires
3. Put the LED diffuser ring into the front panel (face down)
4. Add the LED holder on top
5. Screw the ESP32 into the case base
6. Clip the LED into the holder
7. Close everything up (no screws needed for the case!)

## 💻 Software Setup

1. Download `GlowBox.ino` from this repository
2. Open in Arduino IDE
3. Install ESP32 board support if needed:
   - File → Preferences → Additional Board Manager URLs
   - Add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools → Board → Boards Manager → Search "ESP32" → Install
4. Change your WiFi credentials in the code:
```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
```
5. Select your board: Tools → Board → ESP32 Arduino → ESP32 Dev Module
6. Upload to the ESP32
7. Open Serial Monitor (Tools → Serial Monitor, set to 115200 baud)
8. Note your ESP32's IP address (displayed in Serial Monitor)

## 📱 Phone Setup (Android)

Using the **Automate** app (free on Play Store):

1. Install Automate and grant notification access
2. Create a new Flow with these blocks:
   - **Notification posted** (filter which apps you want)
   - **HTTP request**:
     - Method: GET
     - URL: `http://YOUR_ESP32_IP/notify`
   - Connect the output back to "Notification posted" (loop)
3. Save and start the Flow

![Automate Flow](images/automate.png) 

**iOS users:** Use the Shortcuts app with "When I receive a notification" automation.

## 🧪 Testing

Open your browser and go to:
```
http://YOUR_ESP32_IP/notify
```

The LED should blink 3 times!

## 📝 Notes

- The case clips together - only the ESP32 needs screws
- LED diffuses really well through white PLA (print the circle at 1-2 layers thickness)
- Runs great on a Raspberry Pi USB port or any 5V source
- You can customize the code for different blink patterns

## 🔧 Customization

Want different blink patterns? Edit the `handleNotification()` function:
```cpp
// Single long blink
digitalWrite(LED_PIN, HIGH);
delay(1000);
digitalWrite(LED_PIN, LOW);

// Fast blinks
for(int i = 0; i < 10; i++) {
  digitalWrite(LED_PIN, HIGH);
  delay(50);
  digitalWrite(LED_PIN, LOW);
  delay(50);
}
```

## 📄 License

Feel free to use, modify, and share!

## 🙏 Credits

Design and code by [Erryon3D](https://makerworld.com/@Erryon3D)

---

**Questions?** Open an issue or find me on MakerWorld!
