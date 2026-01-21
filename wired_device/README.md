# Dispositivo con cable *(Wired Device)*

Este subdirectorio contiene el firmware para la versión con cable del dispositivo de CAA (Comunicación Aumentativa y Alternativa), que funciona como un teclado HID de Bluetooth de Bajo Consumo (BLE). En esta configuración, los cinco botones (arriba/abajo/izquierda/derecha/clic) están conectados a una sola carcasa y a una sola placa ESP32.

*This subdirectory contains the firmware for the wired version of the AAC (Augmentative and Alternative Communication) device, which functions as a Bluetooth Low Energy (BLE) HID keyboard. In this configuration, all five buttons (up/down/left/right/click) connect to a single enclosure and a single ESP32 board.*

---

## Qué hace este subproyecto *(What This Subproject Does)*
- Lee las entradas de los cinco botones en una sola placa.  
  *Reads input from all five buttons on one board.*
- Envía comandos de navegación al teléfono como teclado BLE HID.  
  *Sends navigation commands to the phone as a BLE HID keyboard.*

---

## Archivos incluidos *(Included Files)*
- `final_wired_code.ino` — firmware final para la versión con cable.  
  *Final firmware for the wired version.*

---

## Materiales necesarios *(Hardware Needed)*
- Placa ESP32 *(pero NO ESP32-S2 ni ESP32-S3)*  
  *ESP32 board *(but NOT an ESP32-S2 or ESP32-S3)*
- 5 botones  
  *5 buttons*
- Cargador portátil (power bank)  
  *Portable charger (power bank)*

---

## Configuración de Arduino IDE *(Arduino IDE Setup)*

1. Descarga e instala **Arduino IDE**. (https://www.arduino.cc/en/software/)  
   *Download and install **Arduino IDE**.*
2. Agrega soporte para ESP32:  
   *Add ESP32 board support:*
   - Ve a **Archivo → Preferencias**  
     *Go to **File → Preferences***
   - En **URLs adicionales del Gestor de placas**, pega:  
     *Under **Additional Boards Manager URLs**, paste:*
     - `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Haz clic en **OK**  
     *Click **OK***
   - Luego ve a **Herramientas → Placa → Gestor de placas**, busca **ESP32**, e instala **Espressif Systems ESP32**  
     *Then go to **Tools → Board → Boards Manager**, search **ESP32**, and install **Espressif Systems ESP32***
3. Instala la librería BLE HID:  
   *Install the BLE HID library:*
   - Ve a `https://github.com/T-vK/ESP32-BLE-Keyboard`  
     *Go to `https://github.com/T-vK/ESP32-BLE-Keyboard`*
   - Haz clic en **Código → Descargar ZIP**  
     *Click **Code → Download ZIP***
   - En Arduino IDE: **Programa → Incluir biblioteca → Añadir biblioteca .ZIP**  
     *In Arduino IDE: **Sketch → Include Library → Add .ZIP Library***
   - Confirma que diga **“Biblioteca instalada”**  
     *Confirm it says **“Library installed”***
4. Reinicia Arduino IDE para que todo cargue correctamente.  
   *Restart Arduino IDE so everything loads correctly.*

---

## Cómo subir el código *(How to Upload the Code)*
1. Ve a **Herramientas → Placa** y selecciona tu ESP32.  
   *Go to **Tools → Board** and select your ESP32.*
2. Ve a **Herramientas → Puerto** y selecciona el puerto correcto.  
   *Go to **Tools → Port** and select the correct port.*
3. Sube `final_wired_code.ino` a tu placa ESP32.  
   *Upload `final_wired_code.ino` to your ESP32 board.*
4. Prueba con el **Monitor serie** si es necesario.  
   *Test with the **Serial Monitor** if needed.*

---

## Uso *(Usage)*
1. Alimenta el dispositivo con un cargador portátil.  
   *Power the device with a portable charger.*
2. Empareja el dispositivo con tu teléfono/computadora/tablet por BLE.  
   *Pair the device with your phone/computer/tablet via BLE.*
3. Presiona los botones para navegar (arriba/abajo/izquierda/derecha/clic).  
   *Press buttons to navigate (up/down/left/right/click).*

---

## Solución de problemas *(Troubleshooting)*

### No aparece el teclado BLE *(BLE keyboard not showing up)*
- Confirma que `BleKeyboard.begin()` se llame en `setup()`.  
  *Confirm `BleKeyboard.begin()` is called in `setup()`.*
- Verifica que el Bluetooth del teléfono esté encendido.  
  *Check that your phone Bluetooth is on.*
- Borra el dispositivo en Bluetooth y vuelve a emparejarlo.  
  *Remove the device from Bluetooth settings and re-pair it.*

### Botones se activan solos *(Buttons triggering randomly)*
- Usa `INPUT_PULLUP`.  
  *Use `INPUT_PULLUP`.*
- Asegúrate de que cada botón vaya a **GND**.  
  *Make sure each button goes to **GND**.*
- Aumenta el tiempo de debounce si es necesario.  
  *Increase the debounce time if needed.*

