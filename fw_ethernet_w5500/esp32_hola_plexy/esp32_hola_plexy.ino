/*
  Test Ethernet W5500 con ESP32

  Este programa sirve para verificar que un módulo Ethernet W5500
  funciona correctamente conectado a un ESP32.

  El ESP32 solicita una IP automáticamente por DHCP y crea un servidor web.
  Al abrir la IP asignada desde un navegador, se muestra una página con
  el mensaje "Hola PLEXY" y un botón para visitar www.plexylab.com.

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

#include <SPI.h>
#include <Ethernet.h>

// Pines SPI usados para comunicar el ESP32 con el módulo W5500
#define W5500_CS    5
#define W5500_SCK   18
#define W5500_MISO  19
#define W5500_MOSI  23

// Puerto donde funcionará el servidor web
#define WEB_SERVER_PORT 80

// Creamos el servidor web usando el puerto definido
EthernetServer server(WEB_SERVER_PORT);

// Aquí guardaremos la dirección MAC que usará el ESP32 en la red
byte mac[6];

// Genera una dirección MAC usando el identificador único del ESP32
void generarMacDesdeESP32() {
  uint64_t chipId = ESP.getEfuseMac();

  // 0x02 indica que esta MAC es local y generada por software
  mac[0] = 0x02;
  mac[1] = (chipId >> 40) & 0xFF;
  mac[2] = (chipId >> 32) & 0xFF;
  mac[3] = (chipId >> 24) & 0xFF;
  mac[4] = (chipId >> 16) & 0xFF;
  mac[5] = (chipId >> 8)  & 0xFF;
}

// Envía al navegador la página web de prueba
void enviarPaginaWeb(EthernetClient &client) {
  // Cabecera HTTP necesaria para que el navegador interprete la respuesta
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Connection: close");
  client.println();

  // Página HTML que verá el cliente al ingresar a la IP del ESP32
  client.println(R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Hola PLEXY</title>

  <style>
    body {
      margin: 0;
      font-family: Arial, sans-serif;
      background: #f4f6f8;
      color: #222;
      height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      text-align: center;
    }

    .card {
      background: white;
      padding: 35px;
      border-radius: 16px;
      box-shadow: 0 4px 18px rgba(0, 0, 0, 0.12);
      max-width: 360px;
      width: 90%;
    }

    h1 {
      font-size: 34px;
      margin-bottom: 10px;
    }

    p {
      font-size: 16px;
      margin-bottom: 25px;
      color: #555;
    }

    a {
      display: inline-block;
      background: #e5172c;
      color: white;
      text-decoration: none;
      padding: 14px 22px;
      border-radius: 8px;
      font-weight: bold;
      transition: 0.2s;
    }

    a:hover {
      background: #b81222;
    }
  </style>
</head>

<body>
  <div class="card" style="margin-left: 1rem; margin-right: 1rem;">
    <h1>Hola PLEXY</h1>
    <p>Tu módulo Ethernet W5500 está funcionando correctamente.</p>
    <a href="https://www.plexylab.com">Seguir comprando</a>
  </div>
</body>
</html>
)rawliteral");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("|Hola PLEXY| Test Ethernet W5500 - ESP32");

  // Generamos una MAC para que el ESP32 pueda identificarse en la red
  generarMacDesdeESP32();

  // Mostramos la MAC generada en el monitor serial
  Serial.print("|Hola PLEXY| MAC generada: ");
  for (int i = 0; i < 6; i++) {
    if (mac[i] < 0x10) Serial.print("0");
    Serial.print(mac[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  // Inicializamos el bus SPI con los pines conectados al W5500
  SPI.begin(W5500_SCK, W5500_MISO, W5500_MOSI, W5500_CS);

  // Indicamos a la librería Ethernet cuál pin se usa como CS
  Ethernet.init(W5500_CS);

  Serial.println("|Hola PLEXY| Solicitando IP por DHCP...");

  // Solicitamos una IP automáticamente al router
  if (Ethernet.begin(mac) == 0) {
    Serial.println("|Hola PLEXY| Error: No se pudo obtener IP por DHCP.");
    Serial.println("|Hola PLEXY| Verifica cable Ethernet, router, alimentación y conexión SPI.");

    // Detenemos el programa porque sin IP no podemos crear el servidor web
    while (true) {
      delay(1000);
    }
  }

  delay(1000);

  // Verificamos si la librería detecta el módulo Ethernet
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("|Hola PLEXY| Error: No se detecta el módulo W5500.");

    while (true) {
      delay(1000);
    }
  }

  // Avisamos si el cable Ethernet no está conectado
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("|Hola PLEXY| Advertencia: Cable Ethernet desconectado.");
  }

  // Iniciamos el servidor web
  server.begin();

  Serial.println("|Hola PLEXY| Servidor web iniciado.");
  Serial.print("|Hola PLEXY| Dirección IP: ");
  Serial.println(Ethernet.localIP());

  Serial.println("|Hola PLEXY| Abre esta IP en el navegador para probar el módulo.");
}

void loop() {
  // Mantiene activa la IP asignada por DHCP
  Ethernet.maintain();

  // Revisamos si algún navegador se conectó al servidor
  EthernetClient client = server.available();

  if (client) {
    Serial.println("|Hola PLEXY| Cliente conectado.");

    bool lineaEnBlanco = true;
    unsigned long tiempoInicio = millis();

    // Leemos la petición del navegador por un tiempo limitado
    while (client.connected() && millis() - tiempoInicio < 1500) {
      if (client.available()) {
        char c = client.read();

        // Una línea en blanco indica el final de la petición HTTP
        if (c == '\n' && lineaEnBlanco) {
          enviarPaginaWeb(client);
          break;
        }

        // Detectamos si la línea actual está vacía
        if (c == '\n') {
          lineaEnBlanco = true;
        } else if (c != '\r') {
          lineaEnBlanco = false;
        }

        tiempoInicio = millis();
      }
    }

    delay(1);

    // Cerramos la conexión con el navegador
    client.stop();

    Serial.println("|Hola PLEXY| Cliente desconectado.");
  }
}