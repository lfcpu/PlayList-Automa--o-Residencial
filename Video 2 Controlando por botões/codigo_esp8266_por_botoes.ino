// Definição dos pinos no ESP8266 para os relés e botões
#define RELAY1_PIN D1 // Relé 1 conectado ao pino D1 do ESP8266
#define RELAY2_PIN D2 // Relé 2 conectado ao pino D2 do ESP8266
#define BUTTON1_PIN D5 // Botão 1 conectado ao pino D5 do ESP8266
#define BUTTON2_PIN D6 // Botão 2 conectado ao pino D6 do ESP8266

// Variáveis para armazenar o estado atual dos relés
bool relay1State = false; // Relé 1 começa desligado
bool relay2State = false; // Relé 2 começa desligado

void setup() {
  // Configuração dos pinos dos relés como saída (OUTPUT)
  // OUTPUT indica que enviaremos sinal para esses pinos para controlar os relés
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Configuração dos pinos dos botões como entrada (INPUT)
  // INPUT_PULLUP ativa um resistor interno que mantém o estado inicial do pino como HIGH
  pinMode(BUTTON1_PIN, INPUT_PULLUP); // Botão 1 configurado como entrada com pull-up interno
  pinMode(BUTTON2_PIN, INPUT_PULLUP); // Botão 2 configurado como entrada com pull-up interno
  
  // Garantimos que os relés começam desligados
  digitalWrite(RELAY1_PIN, LOW); // Relé 1 inicializado em OFF (desligado)
  digitalWrite(RELAY2_PIN, LOW); // Relé 2 inicializado em OFF (desligado)

  // Inicializamos o monitor serial para depuração e acompanhamento
  Serial.begin(115200); // Comunicação serial a 115200 bps
  Serial.println("Sistema iniciado! Relés desligados.");
}

void loop() {
  // Verifica o estado do Botão 1 (ligado ao Relé 1)
  // O pino BUTTON1_PIN será LOW quando o botão for pressionado
  if (digitalRead(BUTTON1_PIN) == LOW) { 
    delay(200); // Adicionamos um pequeno atraso (200ms) para evitar múltiplas leituras do botão (debounce)
    
    // Alterna o estado do Relé 1: se estava desligado, liga; se estava ligado, desliga
    relay1State = !relay1State; // Inverte o estado atual do Relé 1 (toggle)
    
    // Atualiza o estado físico do Relé 1
    // HIGH = Liga o relé; LOW = Desliga o relé
    digitalWrite(RELAY1_PIN, relay1State ? HIGH : LOW);
    
    // Exibe no monitor serial o novo estado do Relé 1
    Serial.println(relay1State ? "Relé 1 LIGADO" : "Relé 1 DESLIGADO");
  }

  // Verifica o estado do Botão 2 (ligado ao Relé 2)
  // O pino BUTTON2_PIN será LOW quando o botão for pressionado
  if (digitalRead(BUTTON2_PIN) == LOW) { 
    delay(200); // Adicionamos um pequeno atraso (200ms) para evitar múltiplas leituras do botão (debounce)
    
    // Alterna o estado do Relé 2: se estava desligado, liga; se estava ligado, desliga
    relay2State = !relay2State; // Inverte o estado atual do Relé 2 (toggle)
    
    // Atualiza o estado físico do Relé 2
    // HIGH = Liga o relé; LOW = Desliga o relé
    digitalWrite(RELAY2_PIN, relay2State ? HIGH : LOW);
    
    // Exibe no monitor serial o novo estado do Relé 2
    Serial.println(relay2State ? "Relé 2 LIGADO" : "Relé 2 DESLIGADO");
  }
}
