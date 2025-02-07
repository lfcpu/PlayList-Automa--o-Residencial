#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configurações do WiFi
const char* ssid = "SUA_REDE_WIFI";     // Nome da sua rede WiFi
const char* password = "SUA_SENHA_WIFI"; // Senha da sua rede WiFi

// Definição dos pinos dos relés
#define RELAY1_PIN D1
#define RELAY2_PIN D2

// Variáveis para armazenar o estado dos relés
bool relay1State = false;
bool relay2State = false;

// Criar servidor web na porta 80
ESP8266WebServer server(80);

void setup() {
  // Inicializa o monitor serial
  Serial.begin(115200);
  
  // Configura os pinos dos relés como saída
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Garante que os relés começam desligados
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  
  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  
  // Aguarda a conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Conectado ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  
  // Configura as rotas do servidor
  server.on("/relay1/on", HTTP_GET, turnOnRelay1);
  server.on("/relay1/off", HTTP_GET, turnOffRelay1);
  server.on("/relay2/on", HTTP_GET, turnOnRelay2);
  server.on("/relay2/off", HTTP_GET, turnOffRelay2);
  server.on("/status", HTTP_GET, getStatus);
  
  // Inicia o servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

// Funções para controlar os relés
void turnOnRelay1() {
  digitalWrite(RELAY1_PIN, HIGH);
  relay1State = true;
  server.send(200, "application/json", "{\"relay1\": true}");
  Serial.println("Relé 1 LIGADO");
}

void turnOffRelay1() {
  digitalWrite(RELAY1_PIN, LOW);
  relay1State = false;
  server.send(200, "application/json", "{\"relay1\": false}");
  Serial.println("Relé 1 DESLIGADO");
}

void turnOnRelay2() {
  digitalWrite(RELAY2_PIN, HIGH);
  relay2State = true;
  server.send(200, "application/json", "{\"relay2\": true}");
  Serial.println("Relé 2 LIGADO");
}

void turnOffRelay2() {
  digitalWrite(RELAY2_PIN, LOW);
  relay2State = false;
  server.send(200, "application/json", "{\"relay2\": false}");
  Serial.println("Relé 2 DESLIGADO");
}

void getStatus() {
  String json = "{\"relay1\":" + String(relay1State ? "true" : "false") + 
                ",\"relay2\":" + String(relay2State ? "true" : "false") + "}";
  server.send(200, "application/json", json);
}