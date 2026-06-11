# Test Ethernet W5500 con ESP32

Este proyecto permite probar rápidamente un módulo Ethernet **W5500** conectado a un **ESP32** usando el framework de Arduino.

El programa solicita una dirección IP automáticamente mediante **DHCP**, crea un servidor web local y muestra una página con el mensaje **“Hola PLEXY”**. También incluye un botón **“Seguir comprando”** que redirige a:

```text
https://www.plexylab.com
```

Este ejemplo está pensado para que una persona que recién empieza pueda conectar el módulo, cargar el código y verificar si el W5500 funciona correctamente.

---

## Advertencia sobre niveles de voltaje

**ADVERTENCIA:** Aunque el chip W5500 trabaja a 3.3V y declara tolerancia a señales de entrada de 5V, en este proyecto se usa con un ESP32, cuyos pines GPIO no son tolerantes a 5V. Por seguridad, todas las señales de control y comunicación SPI entre el ESP32 y el módulo W5500 deben trabajar a **3.3V**.

De igual manera, como en este proyecto se usa con un ESP32, si el módulo W5500 incluye regulador de voltaje, puede aceptar alimentación de 5V únicamente en el pin de entrada de alimentación del módulo, siempre que el fabricante lo especifique. Esto no significa que los pines conectados al ESP32 deban trabajar a 5V.

**No aplicar** señales de 5V a los GPIO del ESP32.

---

## Funcionamiento general

Al iniciar, el ESP32 configura el bus SPI y se comunica con el módulo Ethernet W5500.

Luego solicita una dirección IP al router mediante DHCP. Si todo está correctamente conectado, el monitor serial mostrará la dirección IP asignada.

Al abrir esa IP desde un navegador web, se mostrará una página simple de prueba con el mensaje **Hola PLEXY**.

---

## Librerías necesarias

Instalar desde el gestor de librerías de Arduino IDE:

```text
Ethernet by Arduino
```

La librería `SPI.h` ya viene incluida con el soporte de ESP32 para Arduino.

También se debe tener instalado el paquete de placas:

```text
ESP32 by Espressif Systems
```

---

## Configuración típica en Arduino IDE

| Parámetro | Valor recomendado |
|---|---|
| Board | ESP32 Dev Module |
| Upload Speed | 921600 o 115200 |
| CPU Frequency | 240 MHz |
| Flash Frequency | 40 MHz |
| Flash Mode | DIO |
| Monitor Speed | 115200 |

Si tienes problemas al cargar el programa, usa `Upload Speed: 115200`.

---

## Pinout de conexión ESP32 + W5500

| Módulo W5500 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SCK / SCLK | GPIO18 |
| MISO / SO | GPIO19 |
| MOSI / SI | GPIO23 |
| CS / SCS | GPIO5 |
| RST | 3.3V o sin conectar |
| INT | No usado |

---

## Pines usados en el código

```cpp
#define W5500_CS    5
#define W5500_SCK   18
#define W5500_MISO  19
#define W5500_MOSI  23
```

Estos pines corresponden al bus SPI VSPI típico del ESP32.

---

## Recomendaciones de conexión

- Conectar el W5500 al ESP32 antes de alimentar la placa.
- Usar cables cortos para las señales SPI.
- Verificar que GND del ESP32 y GND del W5500 estén conectados.
- Conectar el cable Ethernet al router o switch antes de reiniciar el ESP32.
- Usar una fuente USB estable para alimentar el ESP32.
- El W5500 trabaja con lógica de 3.3V. No aplicar señales SPI de 5V al ESP32.

Algunos módulos W5500 tienen regulador interno y aceptan alimentación de 5V, pero si el módulo permite alimentación directa a 3.3V, es recomendable usar 3.3V.

---

## Cómo probar el módulo

1. Conecta el módulo W5500 al ESP32 según la tabla de pinout.
2. Conecta un cable Ethernet desde el W5500 hacia el router o switch.
3. Abre Arduino IDE.
4. Selecciona la placa `ESP32 Dev Module`.
5. Instala la librería `Ethernet by Arduino`.
6. Carga el código en el ESP32.
7. Abre el monitor serial a `115200 baudios`.
8. Reinicia el ESP32.
9. Espera a que aparezca una dirección IP.

Ejemplo de salida esperada:

```text
|Hola PLEXY| Test Ethernet W5500 - ESP32
|Hola PLEXY| Solicitando IP por DHCP...
|Hola PLEXY| Servidor web iniciado.
|Hola PLEXY| Dirección IP: 192.168.1.45
|Hola PLEXY| Abre esta IP en el navegador para probar el módulo.
```

10. Abre un navegador web en una computadora o celular conectado a la misma red.
11. Ingresa la IP mostrada en el monitor serial.

Ejemplo:

```text
http://192.168.1.45
```

Si todo está correcto, se mostrará una página web con el mensaje:

```text
Hola PLEXY
```

Y un botón:

```text
Seguir comprando
```

---

## Problemas comunes

### No aparece dirección IP

Verifica lo siguiente:

- El cable Ethernet está conectado.
- El router tiene DHCP activado.
- El módulo W5500 está correctamente alimentado.
- Los pines SPI están conectados correctamente.
- El pin CS del módulo coincide con el definido en el código.

---

### El monitor serial muestra que no se detecta el W5500

Revisar:

- Conexión de `SCK`, `MISO`, `MOSI` y `CS`.
- Alimentación del módulo.
- Que el pin `CS` usado sea `GPIO5`.
- Que el módulo sea realmente W5500.

---

### La IP aparece, pero no abre la página

Verifica:

- Que el celular o computadora esté conectado a la misma red.
- Que estés escribiendo la IP correcta.
- Que no estés usando `https://`; se debe usar `http://`.
- Que el firewall o red del router no bloquee dispositivos locales.

Ejemplo correcto:

```text
http://192.168.1.45
```

---

## Resultado esperado

Este proyecto permite confirmar que:

- El ESP32 está funcionando.
- El módulo W5500 responde por SPI.
- El router asigna IP por DHCP.
- El servidor web del ESP32 funciona correctamente.
- El cliente puede acceder a una página local de prueba.

Si la página **Hola PLEXY** aparece en el navegador, el módulo Ethernet W5500 está funcionando correctamente.
