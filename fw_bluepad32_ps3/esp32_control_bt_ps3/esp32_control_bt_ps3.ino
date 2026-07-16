/***************************************************************************
 *  EJEMPLO DE USO DE BLUEPAD32
 *
 *  Descripción:
 *  ------------
 *  Este programa permite conectar un control Bluetooth compatible mediante
 *  la biblioteca Bluepad32 y mostrar en el Monitor Serie el estado de:
 *
 *    - Botones principales
 *    - Botones auxiliares (Misc)
 *    - D-Pad
 *    - Joystick izquierdo
 *    - Joystick derecho
 *    - Gatillos analógicos (L2 y R2)
 *
 *  Hardware:
 *      - ESP32
 *      - Control Bluetooth (PS3, PS4, Xbox, Switch, etc.)
 *
 ***************************************************************************/

#include <Bluepad32.h>

/*---------------------------------------------------------------------------
    Variable que almacenará el puntero al control conectado.

    ControllerPtr es una clase de Bluepad32 que contiene toda la información
    del control Bluetooth.
---------------------------------------------------------------------------*/
ControllerPtr gamepad = nullptr;


/*---------------------------------------------------------------------------
    Callback ejecutado automáticamente cuando un control se conecta.
---------------------------------------------------------------------------*/
void onConnectedController(ControllerPtr ctl) {

    // Guarda el puntero al control conectado
    gamepad = ctl;

    Serial.println("\n================================");
    Serial.println("Control conectado");

    // Muestra el nombre del modelo detectado
    Serial.printf("Modelo : %s\n", ctl->getModelName().c_str());

    Serial.println("================================");
}


/*---------------------------------------------------------------------------
    Callback ejecutado cuando el control se desconecta.
---------------------------------------------------------------------------*/
void onDisconnectedController(ControllerPtr ctl) {

    // Si el control desconectado es el mismo que estaba almacenado,
    // se elimina la referencia.
    if (gamepad == ctl)
        gamepad = nullptr;

    Serial.println("Control desconectado");
}


/*---------------------------------------------------------------------------
    SETUP
---------------------------------------------------------------------------*/
void setup() {

    // Inicializa el puerto serie
    Serial.begin(115200);

    // Inicializa Bluepad32 indicando las funciones callback
    // para conexión y desconexión.
    BP32.setup(&onConnectedController,
               &onDisconnectedController);

    /*
        Borra todas las claves Bluetooth almacenadas.

        Esto obliga a realizar un nuevo emparejamiento cada vez
        que se reinicia el ESP32.

        Una vez que el control ya esté emparejado correctamente,
        esta línea puede comentarse para evitar volver a enlazarlo.
    */
    BP32.forgetBluetoothKeys();

    /*
        Deshabilita el dispositivo virtual BLE.

        El programa utilizará únicamente Bluetooth Classic HID,
        que es el utilizado por la mayoría de controles.
    */
    BP32.enableVirtualDevice(false);

    Serial.println("Esperando control...");
}


/*---------------------------------------------------------------------------
    LOOP PRINCIPAL
---------------------------------------------------------------------------*/
void loop() {

    /*
        Actualiza el estado interno de Bluepad32.

        Esta función procesa los paquetes Bluetooth recibidos y actualiza
        la información del control.
    */
    BP32.update();

    /*
        Se verifica:

            1) Que exista un control.
            2) Que continúe conectado.
            3) Que existan datos nuevos.

        hasData() evita procesar información repetida.
    */
    if (gamepad &&
        gamepad->isConnected() &&
        gamepad->hasData()) {

        Serial.println("--------------------------------");

        //------------------------------------------------------------------
        // BOTONES PRINCIPALES
        //------------------------------------------------------------------

        /*
            Devuelve un entero de 16 bits.

            Cada bit representa un botón diferente.

            Ejemplo:

                0x0001
                0x0020
                0x0100
        */
        Serial.printf("Buttons : 0x%04X\n",
                      gamepad->buttons());


        //------------------------------------------------------------------
        // BOTONES AUXILIARES
        //------------------------------------------------------------------

        /*
            Devuelve botones especiales como:

                Select
                Start
                Home / PS
                Capture

            dependiendo del tipo de control.
        */
        Serial.printf("Misc    : 0x%02X\n",
                      gamepad->miscButtons());


        //------------------------------------------------------------------
        // D-PAD
        //------------------------------------------------------------------

        /*
            Devuelve un byte cuyos bits indican:

                Arriba
                Abajo
                Izquierda
                Derecha
        */
        Serial.printf("DPad    : 0x%02X\n",
                      gamepad->dpad());


        //------------------------------------------------------------------
        // JOYSTICK IZQUIERDO
        //------------------------------------------------------------------

        /*
            axisX()

                Movimiento horizontal.

            axisY()

                Movimiento vertical.

            Rango aproximado:

                -511  ...  512
        */
        Serial.printf("LX=%4d  LY=%4d\n",
                      gamepad->axisX(),
                      gamepad->axisY());


        //------------------------------------------------------------------
        // JOYSTICK DERECHO
        //------------------------------------------------------------------

        Serial.printf("RX=%4d  RY=%4d\n",
                      gamepad->axisRX(),
                      gamepad->axisRY());


        //------------------------------------------------------------------
        // GATILLOS ANALÓGICOS
        //------------------------------------------------------------------

        /*
            brake()

                Gatillo L2.

            throttle()

                Gatillo R2.

            Rango:

                0 ... 1023
        */
        Serial.printf("L2=%4d  R2=%4d\n",
                      gamepad->brake(),
                      gamepad->throttle());

        /*
            Pequeña pausa para evitar saturar el Monitor Serie.
        */
        delay(100);
    }
}