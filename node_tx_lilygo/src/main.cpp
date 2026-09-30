#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Wire.h> // Librería para comunicación I2C con el chip de energía
#include "XPowersLib.h"
#include "credentials.h"

// Gestor de energía avanzado de la placa T-Beam
XPowersAXP2101 PMU;

// Mapa de pines físico corregido para la arquitectura T-Beam
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 23, // OJO: En la T-Beam el reset de la antena está en el cable 23
    .dio = {26, 33, 32},
};

osjob_t sendjob; 
void do_send(osjob_t* j);

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_JOINING:
            Serial.println(F("EV_JOINING: Buscando la red de ECOVIDA..."));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED: ¡Conexión segura establecida con el servidor!"));
            LMIC_setLinkCheckMode(0);
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED: El servidor rechazó las llaves."));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE: Transmisión completada y ciclos de escucha terminados."));
            break;
        // NUEVO: Traducimos el evento 17
        case EV_TXSTART:
            Serial.println(F("EV_TXSTART: Transmisión de radio iniciada físicamente."));
            break;
        default:
            Serial.print(F("Evento LMIC: "));
            Serial.println((unsigned) ev);
            break;
    }
}

void do_send(osjob_t* j){
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND: Hay un paquete esperando en la radio, no se puede enviar aún."));
    } else {
        static uint8_t payload_prueba[] = "1";
        LMIC_setTxData2(1, payload_prueba, sizeof(payload_prueba)-1, 0);
        Serial.println(F("Petición de paquete encolada para transmisión."));
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("Inicializando Cerebro Físico ECOVIDA - Secuencia OTAA"));

    // 1. Despertar el chip de gestión de energía (AXP2101) por I2C
    Wire.begin(21, 22);
    if (!PMU.init(Wire, AXP2101_SLAVE_ADDRESS)) {
        Serial.println(F("Error: No se encontró el PMU AXP2101. Revisa el modelo de placa."));
    } else {
        Serial.println(F("AXP2101 Iniciado. Suministrando 3.3V a la antena LoRa..."));
        // El canal ALDO2 alimenta el chip de radio en las T-Beam v1.2
        PMU.setALDO2Voltage(3300); 
        PMU.enableALDO2();
    }

    // 2. Inicializar el bus de datos
    SPI.begin();

    // 3. Iniciar la librería de radio
    os_init();
    LMIC_reset();
    do_send(&sendjob);
}

void loop() {
    os_runloop_once();
}