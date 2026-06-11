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