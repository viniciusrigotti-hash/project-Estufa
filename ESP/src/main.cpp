////////////////////////////////////////////////////////////////////////
// Bibliotecas
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <TFT_eSPI.h>
#include "imagem.h"

////////////////////////////////////////////////////////////////////////
// Credenciais do Wi-Fi 
#define WIFI_SSID "Gabriel"
#define WIFI_PASSWORD "Gabriel19"

////////////////////////////////////////////////////////////////////////
// Credenciais do FB
#define API_KEY "AIzaSyAUKXBwWRhgZOwI3NTibBzHh3duuDRNSyE"
#define DATABASE_URL "https://projeto-sensor---dados-default-rtdb.firebaseio.com"
#define USER_EMAIL "ghnv@gmail.com"
#define USER_PASSWORD "oi1234"
// Configuração FB
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

////////////////////////////////////////////////////////////////////////
// LED
const int led = 2;
// Tela
TFT_eSPI tft = TFT_eSPI();

////////////////////////////////////////////////////////////////////////
// Inicialização
void setup()
{
    ////////////////////////////////////////////////////////////////////////
    // Começo
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    Serial.begin(115200);

    ////////////////////////////////////////////////////////////////////////
    // Tela
    tft.init();
    tft.setRotation(1);
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, 320, 240, (uint16_t*)cachorro240x320_map);

    ////////////////////////////////////////////////////////////////////////
    // Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Conectando ao Wi-Fi");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }

    Serial.println();
    Serial.println("Wi-Fi conectado!");

    ////////////////////////////////////////////////////////////////////////
    // Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
}

////////////////////////////////////////////////////////////////////////
// Loop
void loop()
{
    if (Firebase.ready())
    {
        Serial.println("Firebase está pronto!");
    }
    else
    {
        Serial.println("Firebase ainda não está pronto!");
    }
}