# Hub y Radios *(Hub-and-Spoke Device)*

Este subdirectorio contiene el firmware para la versión hub y radios del dispositivo de CAA (Comunicación Aumentativa y Alternativa), que funciona como un teclado HID de Bluetooth de Bajo Consumo (BLE). En esta configuración, los controles se dividen en módulos: un hub recibe las pulsaciones de los **spokes** y envía comandos de navegación (arriba/abajo/izquierda/derecha/clic) al teléfono como si fuera un teclado.

*This subdirectory contains the firmware for the hub-and-spoke version of the AAC (Augmentative and Alternative Communication) device, which functions as a Bluetooth Low Energy (BLE) HID keyboard. In this configuration, the controls are split into modules: a hub receives button presses from spokes and sends navigation commands (up/down/left/right/click) to the phone like a keyboard.*

---

## Qué hace este subproyecto *(What This Subproject Does)*
- **Radios:** detecta pulsaciones de botones y envía señales al hub mediante códigos MAC.  
  *Spoke: detects button presses and sends signals to the hub using MAC codes.*
- **Hub:** recibe mensajes de los spokes y envía eventos de teclado al teléfono usando BLE HID.  
  *Hub: receives spoke messages and outputs keyboard events to the phone via BLE HID.*

---

## Archivos incluidos *(Included Files)*
- `MAC_code_retrieval.ino` — código para obtener/confirmar los códigos MAC necesarios para la comunicación entre módulos.  
  *Code used to retrieve/confirm MAC codes needed for communication between modules.*
- `final_hub_code.ino` — firmware final para el **hub** (salida BLE HID al teléfono).  
  *Final firmware for the **hub** (BLE HID output to the phone).*
- `final_spoke_code.ino` — firmware final para el/los **spoke(s)** (envían botones al hub).  
  *Final firmware for the **spoke(s)** (send button inputs to the hub).*

---

## Materiales necesarios *(Hardware Needed)*
- Placa ESP32 *(pero NO ESP32-S2 ni ESP32-S3)*  
  *ESP32 board *(but NOT an ESP32-S2 or ESP32-S3)*
- Botones (para cada módulo)  
  *Buttons (for each module)*
- Cargador portátil (power bank) para cada módulo  
  *Portable charger (power bank) for each module*

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
3. Sube `final_spoke_code.ino` a cada módulo **spoke**.  
   *Upload `final_spoke_code.ino` to each **spoke** module.*
4. Sube `final_hub_code.ino` al módulo **hub**.  
   *Upload `final_hub_code.ino` to the **hub** module.*
5. Prueba con el **Monitor serie** si es necesario.  
   *Test with the **Serial Monitor** if needed.*

---

## Uso *(Usage)*
1. Alimenta el hub y los spokes con sus cargadores portátiles.  
   *Power the hub and spokes with portable chargers.*
2. Empareja el hub con tu teléfono/computadora/tablet por BLE.  
   *Pair the hub with your phone/computer/tablet via BLE.*
3. Presiona botones en los spokes y verifica que el hub envíe comandos.  
   *Press buttons on the spokes and confirm the hub sends commands.*

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
- Asegúrate de que el botón vaya a **GND**.  
  *Make sure the button goes to **GND**.*
- Aumenta el tiempo de debounce si es necesario.  
  *Increase the debounce time if needed.*

> **Nota:** Algunas versiones del paquete ESP32 cambian el tipo de callback de ESP-NOW. Si tienes errores de compilación, revisa la sección de troubleshooting del repositorio principal.  
> *Note: Some ESP32 board package versions change the ESP-NOW receive callback type. If you get compilation errors, check the troubleshooting section in the main repo.*

