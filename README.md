# Mago de Voz *(Wizard of Voz)*

Este repositorio contiene el firmware para dos dispositivos de CAA (Comunicación Aumentativa y Alternativa) que funcionan como teclados HID de Bluetooth de Bajo Consumo (BLE). Ambos diseños usan botones externos grandes para enviar comandos de navegación de arriba/abajo/izquierda/derecha/clic. El proyecto admite dos configuraciones: primero, una versión con cable, donde los cinco botones se conectan a una sola carcasa del dispositivo, y una versión de hub y radios, donde los controles se dividen en tres módulos: un hub de un solo botón (clic) y dos radios de dos botones (arriba/abajo e izquierda/derecha/clic).

*This repository contains the firmware for two AAC (Augmentative and Alternative Communication) devices that function as Bluetooth Low Energy (BLE) HID keyboards. Both designs use large external buttons to send up/down/left/right/click navigation commands. The project supports two configurations: a wired version, where all five buttons connect to a single device enclosure, and a hub-and-spoke version, where the controls are split across three modules—one single-button hub (click) and two two-button spokes (up/down and left/right/click).*

---

## What This Does *(Qué hace este proyecto)*
- **Spoke(s):** módulos pequeños con botones que detectan pulsaciones y envían señales al hub mediante códigos MAC.  
  *Small button modules that detect button presses and send signals to the hub using MAC codes.*
- **Hub:** recibe mensajes de los spokes y envía eventos de teclado al teléfono usando BLE HID.  
  *Receives button messages from spokes and outputs keyboard events to the phone via BLE HID.*

---

## Features *(Características)*
- Controles de navegación: arriba/abajo/izquierda/derecha/enter.  
  *Up/Down/Left/Right/Enter navigation controls.*
- Comunicación inalámbrica entre spokes y hub (solo en la configuración hub-and-spoke).  
  *Wireless communication between spokes and hub (hub-and-spoke configuration only).*
- Lógica simple de “debouncing” para botones.  
  *Simple button debouncing logic.*
- Diseñado para accesibilidad y control confiable del teléfono.  
  *Built for accessibility and reliable phone control.*

---

## Hardware Needed *(Materiales necesarios)*

### Wired Configuration *(Configuración con cable)*
- Placa ESP32 *(pero NO ESP32-S2 ni ESP32-S3)*  
  *ESP32 board *(but NOT an ESP32-S2 or ESP32-S3)*
- 5 botones  
  *5 buttons*
- Cargador portátil (power bank)  
  *Portable charger (power bank)*

### Hub *(Hub)*
- Placa ESP32 *(pero NO ESP32-S2 ni ESP32-S3)*  
  *ESP32 board *(but NOT an ESP32-S2 or ESP32-S3)*
- 1 botón  
  *1 button*
- Cargador portátil (power bank)  
  *Portable charger (power bank)*

### Spoke(s) *(Spoke(s))*
- Placa ESP32 *(pero NO ESP32-S2 ni ESP32-S3)*  
  *ESP32 board *(but NOT an ESP32-S2 or ESP32-S3)*
- Botones  
  *Buttons*
- Cargador portátil (power bank)  
  *Portable charger (power bank)*

---

## Arduino IDE Setup (ESP32 + BLE Keyboard) *(Configuración de Arduino IDE)*

1. Descarga e instala **Arduino IDE**.  
   *Download and install **Arduino IDE**.*
2. Abre Arduino IDE y agrega soporte para placas ESP32:  
   *Open Arduino IDE and add ESP32 board support:*
   - Ve a **File → Preferences**  
     *Go to **File → Preferences***
   - En **Additional Boards Manager URLs**, pega:  
     *Under **Additional Boards Manager URLs**, paste:*
     - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Haz clic en **OK**  
     *Click **OK***
   - Luego ve a **Tools → Board → Boards Manager**, busca **ESP32**, e instala **Espressif Systems ESP32**  
     *Then go to **Tools → Board → Boards Manager**, search **ESP32**, and install **Espressif Systems ESP32***
3. Instala las librerías necesarias:  
   *Install the required libraries:*
   - Para modo BLE HID, instala `BleKeyboard.h`:  
     *For BLE HID mode, install `BleKeyboard.h`:*
     - Ve a `https://github.com/T-vK/ESP32-BLE-Keyboard`  
       *Go to `https://github.com/T-vK/ESP32-BLE-Keyboard`*
     - Haz clic en **Code → Download ZIP**  
       *Click **Code → Download ZIP***
     - En Arduino IDE: **Sketch → Include Library → Add .ZIP Library**  
       *In Arduino IDE: **Sketch → Include Library → Add .ZIP Library***
     - Selecciona el ZIP y confirma que diga **“Library installed”**  
       *Select the ZIP and confirm it says **“Library installed”***
4. Reinicia Arduino IDE (ciérralo y vuelve a abrirlo) para que todo cargue correctamente.  
   *Restart Arduino IDE (close and re-open) so everything loads correctly.*
5. Selecciona tu placa y puerto:  
   *Select your board and port:*
   - Ve a **Tools → Board** y elige la placa ESP32 correcta  
     *Go to **Tools → Board** and choose the correct ESP32 board*
   - Ve a **Tools → Port** y selecciona el COM correcto  
     *Go to **Tools → Port** and select the correct COM port*
6. Sube el código:  
   *Upload the code:*
   - Sube el código de **Spoke** a cada spoke  
     *Upload the **Spoke** code to the spoke board(s)*
   - Sube el código de **Hub** al hub  
     *Upload the **Hub** code to the hub board*
7. Prueba el sistema presionando botones y revisando la salida en el **Serial Monitor**.  
   *Test the system by pressing buttons and checking output in the **Serial Monitor**.*

> **Nota:** Algunas versiones del paquete ESP32 cambian el tipo de callback de ESP-NOW. Si tienes errores de compilación, revisa la sección **Troubleshooting**.  
> *Note: Some ESP32 board package versions change the ESP-NOW receive callback type. If you get compilation errors, check the **Troubleshooting** section below.*

---

## GitHub Layout *(Estructura del repositorio)*

Coloca tus archivos en estas carpetas según la versión del dispositivo.  
*Place your files in these folders depending on the device version.*

