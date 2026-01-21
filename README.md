# Mago de Voz *(Wizard of Voz)*
Este repositorio contiene el firmware para dos dispositivos de CAA (Comunicación Aumentativa y Alternativa) que funcionan como teclados HID de Bluetooth de Bajo Consumo (BLE). Ambos diseños usan botones externos grandes para enviar comandos de navegación de arriba/abajo/izquierda/derecha/clic. El proyecto admite dos configuraciones: primero, una versión con cable, donde los cinco botones se conectan a una sola carcasa del dispositivo, y una versión de hub y radios, donde los controles se dividen en tres módulos: un hub de un solo botón (clic) y dos radios de dos botones (arriba/abajo e izquierda/derecha).
*This repository contains the firmware for two AAC (Augmentative and Alternative Communication) devices that function as Bluetooth Low Energy (BLE) HID keyboards. Both designs use large external buttons to send up/down/left/right/click navigation commands. The project supports two configurations. First, a wired version, where all five buttons connect to a single device enclosure, and a hub-and-spoke version, where the controls are split across three modules—one single-button hub (click) and two two-button spokes (up/down and left/right).*

## What This Does
- **Spoke(s):** small button modules that detect button presses and send signals to the hub via MAC codes
- **Hub:** receives button messages from spokes and outputs keyboard events to the phone via BLE HID

## Features
- Up/Down/Left/Right/Enter navigation controls
- Wireless communication between spokes and hub for hub-and-spoke configuration
- Simple button debouncing logic
- Built for accessibility, reliable phone control, and accessibility

## Hardware Needed
### Wired Configuration
- ESP32 board [but NOT an ESP32-S2 or ESP32-S3]
- 5 Buttons
- Portable charger

### Hub
- ESP32 board [but NOT an ESP32-S2 or ESP32-S3]
- Button
- Portable charger


### Spoke(s)
- ESP32 board [but NOT an ESP32-S2 or ESP32-S3]
- Buttons
- Portable charger
  
## Arduino IDE Setup (ESP32 + BLE Keyboard)
1. Download and install **Arduino IDE**.
2. Open Arduino IDE and add ESP32 board support:
   - Go to **File → Preferences**
   - Under **Additional Boards Manager URLs**, paste:
     - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Click **OK**
   - Then go to **Tools → Board → Boards Manager**, search **ESP32**, and install **Espressif Systems ESP32**
3. Install the required libraries:
   - For BLE HID mode, install `BleKeyboard.h`:
     - Go to `https://github.com/T-vK/ESP32-BLE-Keyboard`
     - Click **Code → Download ZIP**
     - In Arduino IDE, go to **Sketch → Include Library → Add .ZIP Library**
     - Select the downloaded ZIP and confirm it says **“Library installed”**
4. Restart Arduino IDE (close and re-open) so everything loads correctly.
5. Select your board and port:
   - Go to **Tools → Board** and choose the correct ESP32 board
   - Go to **Tools → Port** and select the correct COM port
6. Upload the code:
   - Upload the **Spoke** code to the spoke board(s)
   - Upload the **Hub** code to the hub board
7. Test the system by pressing buttons and checking output in the **Serial Monitor**.

> **Note:** Some ESP32 board package versions change the ESP-NOW receive callback type. If you get compilation errors, check the **Troubleshooting** section below.


## Wiring
### Button wiring (basic)
- One button leg → GPIO pin
- Other button leg → GND  
Use `INPUT_PULLUP` in code so no external resistor is needed.

## Usage
1. Power the hub with portable charger
2. Power the spoke devices
3. Pair hub with phone/computer/tablet
4. Press a button on the spokes
5. Hub receives the input and sends the corresponding key command
6. Phone/computer/tablet reacts like a keyboard input

## Troubleshooting
### BLE keyboard not showing up
- Confirm `BleKeyboard.begin()` is called in `setup()`
- Check that your phone Bluetooth is on
- Try removing the device from Bluetooth settings and re-pairing

### Buttons triggering randomly
- Use `INPUT_PULLUP`
- Make sure the button goes to **GND**
- Add debouncing (already included in most versions of this code), or increase the debounce until issue is fixed
  
## Contributing
Feel free to open issues or pull requests!
