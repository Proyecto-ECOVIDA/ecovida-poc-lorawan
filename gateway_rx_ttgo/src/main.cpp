#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// Credenciales de tu red Wi-Fi local
const char* ssid = "FABLAB-UdeC";
const char* password = "3Dprint2025*";

// Configuración de red hacia tu servidor Ubuntu (vía Tailscale)
const char* serverIP = "100.106.78.8";
const int serverPort = 1700;

WiFiUDP udp;

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando Micro-Gateway ECOVIDA...");

    // Iniciamos la conexión Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\n¡Wi-Fi conectado con éxito!");
    Serial.print("IP local asignada al Gateway: ");
    Serial.println(WiFi.localIP());

    // Abrimos el puerto UDP local para prepararnos a enviar paquetes
    udp.begin(serverPort);
    Serial.println("Canal UDP listo para retransmitir hacia el servidor.");
}

void loop() {
    // Aquí programaremos la captura de radio LoRa en el siguiente paso.
}