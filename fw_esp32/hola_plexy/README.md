# Test básico de LED en GPIO2 con ESP32

Este proyecto permite verificar rápidamente que un **ESP32** está funcionando correctamente usando un LED conectado al **GPIO2**.

El programa enciende y apaga el LED cada **500 ms** y también muestra mensajes en el **monitor serial** para confirmar que el código se está ejecutando.

---

## ¿Qué hace este código?

El ESP32 configura el pin **GPIO2** como salida digital.

Luego, dentro del `loop()`, el programa realiza estas acciones continuamente:

1. Enciende el LED.
2. Muestra el mensaje `LED ON` en el monitor serial.
3. Espera 500 ms.
4. Apaga el LED.
5. Muestra el mensaje `LED OFF` en el monitor serial.
6. Espera 500 ms y repite el ciclo.

Este ejemplo es útil para comprobar:

- Que el ESP32 enciende correctamente.
- Que el código se cargó sin problemas.
- Que el monitor serial está funcionando.
- Que el GPIO2 puede controlar una salida digital.

---

## Código del proyecto

Copia este código en Arduino IDE:

```cpp
/*
  Test básico de LED en ESP32 usando GPIO2

  Este programa enciende y apaga el LED conectado al GPIO2 cada 500 ms.
  También envía mensajes por el monitor serial para verificar que el ESP32
  está ejecutando correctamente el código.

  Autor: PLEXYLAB
*/

/*
  Configuración típica en Arduino IDE:

  Board: ESP32 Dev Module
  Upload Speed: 921600 o 115200
  CPU Frequency: 240 MHz
  Flash Frequency: 40 MHz
  Flash Mode: DIO
  Monitor Speed: 115200
*/

/*
  Este código sirve para verificar rápidamente que el ESP32 está funcionando.
  Primero se configura el GPIO2 como salida. Luego, dentro del loop(), el pin
  cambia entre HIGH y LOW cada 500 ms, haciendo que el LED se encienda y se
  apague continuamente. Los mensajes por Serial.println() permiten confirmar
  el estado del LED desde el monitor serial.
*/

#define LED_PIN 2  // Definimos el GPIO2 como pin para controlar el LED

void setup() {
  // Iniciamos la comunicación serial a 115200 baudios
  // Esto nos permite ver mensajes desde el ESP32 en el monitor serial
  // Se debe configurar la misma velocidad en el monitor serial del IDE
  Serial.begin(115200);

  // Pequeña pausa para dar tiempo a que el monitor serial se inicie
  delay(1000);

  // Mensaje inicial para confirmar que el programa arrancó correctamente
  Serial.println("|Hola PLEXY| Test LED GPIO2 - ESP32");

  // Configuramos el GPIO2 como salida, porque vamos a controlar un LED
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Encendemos el LED colocando el GPIO2 en nivel alto
  digitalWrite(LED_PIN, HIGH);
  Serial.println("|Hola PLEXY| LED ON");

  // Esperamos 500 milisegundos
  delay(500);

  // Apagamos el LED colocando el GPIO2 en nivel bajo
  digitalWrite(LED_PIN, LOW);
  Serial.println("|Hola PLEXY| LED OFF");

  // Esperamos 500 milisegundos antes de repetir el ciclo
  delay(500);
}
```

---

## Materiales necesarios

- 1 placa ESP32.
- 1 cable USB para programar el ESP32.
- Arduino IDE instalado.
- Soporte de placas ESP32 instalado en Arduino IDE.

Opcional, si tu placa no tiene LED integrado en GPIO2:

- 1 LED.
- 1 resistencia entre 220 Ω y 1 kΩ.
- Cables jumper.

---

## Conexión del LED externo

Muchas placas ESP32 DevKit ya tienen un LED integrado conectado al **GPIO2**. En ese caso, no necesitas conectar un LED externo.

Si tu placa no tiene LED integrado, puedes conectar uno de esta manera:

| Componente | Conexión |
|---|---|
| GPIO2 del ESP32 | Resistencia de 220 Ω a 1 kΩ |
| Resistencia | Ánodo del LED |
| Cátodo del LED | GND del ESP32 |

Referencia rápida:

```text
GPIO2 ── Resistencia ── Ánodo LED
Cátodo LED ── GND
```

---

## Configuración típica en Arduino IDE

Usa la siguiente configuración recomendada:

| Parámetro | Valor recomendado |
|---|---|
| Board | ESP32 Dev Module |
| Upload Speed | 921600 o 115200 |
| CPU Frequency | 240 MHz |
| Flash Frequency | 40 MHz |
| Flash Mode | DIO |
| Monitor Speed | 115200 |

Si tienes problemas al cargar el programa, cambia `Upload Speed` a **115200**.

---

## Cómo cargar el código

1. Abre Arduino IDE.
2. Crea un nuevo sketch.
3. Copia el código del proyecto.
4. Conecta el ESP32 al computador mediante USB.
5. Selecciona la placa `ESP32 Dev Module`.
6. Selecciona el puerto COM correspondiente.
7. Presiona el botón **Upload**.
8. Espera a que termine la carga del programa.

En algunas placas ESP32 puede ser necesario mantener presionado el botón **BOOT** mientras inicia la carga.

---

## Cómo probar que funciona

Después de cargar el código:

1. Abre el monitor serial.
2. Configura la velocidad en **115200 baudios**.
3. Presiona el botón **EN** o **RESET** del ESP32.
4. Observa el LED conectado al GPIO2.
5. El LED debe encenderse y apagarse cada 500 ms.

En el monitor serial deberías ver mensajes similares a estos:

```text
|Hola PLEXY| Test LED GPIO2 - ESP32
|Hola PLEXY| LED ON
|Hola PLEXY| LED OFF
|Hola PLEXY| LED ON
|Hola PLEXY| LED OFF
```

---

## Problemas comunes

### El código no se carga

Revisa lo siguiente:

- Que la placa seleccionada sea `ESP32 Dev Module`.
- Que el puerto COM sea el correcto.
- Que el cable USB permita datos y no solo carga.
- Que el driver USB de la placa esté instalado.
- Prueba usar `Upload Speed: 115200`.

---

### No aparece nada en el monitor serial

Verifica:

- Que el monitor serial esté configurado a `115200 baudios`.
- Que el ESP32 esté conectado correctamente.
- Que el puerto seleccionado sea el correcto.
- Presiona el botón `EN` o `RESET` del ESP32.

---

### El LED no parpadea

Revisa:

- Que tu placa tenga LED integrado en GPIO2.
- Si usas LED externo, revisa la polaridad del LED.
- Verifica que la resistencia esté conectada en serie.
- Confirma que el código usa `#define LED_PIN 2`.

---

## Nota importante sobre GPIO2

El **GPIO2** puede estar relacionado con el arranque del ESP32 en algunas placas. Para esta prueba básica con LED no debería haber problema, pero evita conectar cargas pesadas o circuitos que fuercen este pin a GND durante el encendido.

Para pruebas simples, usa siempre una resistencia en serie con el LED.

---

## Resultado esperado

Si todo está correcto:

- El ESP32 ejecutará el programa.
- El LED parpadeará cada 500 ms.
- El monitor serial mostrará los mensajes `LED ON` y `LED OFF`.

Con esto puedes confirmar que tu ESP32 está funcionando correctamente.
