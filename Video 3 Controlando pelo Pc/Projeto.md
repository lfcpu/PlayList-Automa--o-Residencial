# Documentação do Sistema de Controle de Relés

## Visão Geral do Sistema
Sistema de controle remoto de relés utilizando ESP8266, Node.js e interface web.

## Diagrama Resumido
```mermaid
%%{init: {'theme': 'base', 'themeVariables': { 'primaryTextColor': '#000'}}}%%
sequenceDiagram
    participant U as Usuário
    participant W as Web
    participant N as Node.js
    participant E as ESP8266
    participant R as Relés

    rect rgba(255, 220, 220, 0.5)
        U->>W: Controla relé
        W->>N: Envia comando
        N->>E: Repassa comando
        E->>R: Executa ação
    end

    rect rgba(220, 220, 255, 0.5)
        loop Monitoramento
            W->>E: Verifica status
            E-->>W: Retorna estado
        end
    end
```

## Diagrama Detalhado do Sistema
```mermaid
%%{init: {'theme': 'base', 'themeVariables': { 'primaryTextColor': '#000'}}}%%
sequenceDiagram
    participant U as Usuário
    participant W as Interface Web
    participant N as Node.js
    participant E as ESP8266
    participant R as Relés

    Note over U,R: Processo de Controle dos Relés

    rect rgba(220, 255, 220, 0.5)
        Note over E: Inicialização do Sistema
        E->>E: 1. Conecta ao WiFi
        E->>E: 2. Inicia Servidor Web
        E->>E: 3. Configura Pinos dos Relés
    end

    rect rgba(255, 220, 220, 0.5)
        Note over U,R: Ação de Controle
        U->>W: 1. Clica no botão na interface
        W->>W: 2. Executa controlRelay()
        W->>N: 3. Envia comando ao servidor
        N->>N: 4. Processa requisição
        N->>E: 5. Envia comando ao ESP8266
        E->>E: 6. Processa comando
        E->>R: 7. Ativa/Desativa relé
        E-->>N: 8. Confirma execução
        N-->>W: 9. Retorna resposta
        W-->>U: 10. Atualiza interface
    end

    rect rgba(220, 220, 255, 0.5)
        Note over U,R: Sistema de Monitoramento
        loop Cada 2 segundos
            W->>N: Requisita estado atual
            N->>E: Consulta ESP8266
            E->>R: Verifica relés
            R-->>E: Retorna estado
            E-->>N: Envia estado atual
            N-->>W: Repassa informação
            W-->>U: Atualiza display
        end
    end
```

## Explicação do Fluxo

### 1. Inicialização (Verde):
- ESP8266 inicia e conecta à rede WiFi configurada
- Configura pinos digitais para controle dos relés
- Inicia servidor web interno para receber comandos

### 2. Controle dos Relés (Vermelho):
1. Usuário interage com botão na interface web
2. JavaScript processa a ação do usuário
3. Envia comando HTTP para servidor Node.js
4. Servidor Node.js valida e processa a requisição
5. Comando é enviado ao ESP8266
6. ESP8266 processa o comando recebido
7. Sinal digital é enviado ao relé
8. Confirmação retorna por toda a cadeia
9. Interface atualiza para mostrar novo estado

### 3. Monitoramento Contínuo (Azul):
- Interface web mantém verificação periódica
- Requisições de status a cada 2 segundos
- ESP8266 verifica estado físico dos relés
- Estado atual é enviado de volta
- Interface atualiza informações em tempo real

## Componentes do Sistema

### Interface Web
- Frontend em HTML/JavaScript
- Controles intuitivos para cada relé
- Sistema de atualização automática
- Feedback visual do estado dos relés

### Servidor Node.js
- API REST para controle
- Gerenciamento de comunicação
- Tratamento de erros
- Validação de comandos

### ESP8266
- Microcontrolador com WiFi
- Controle direto dos relés
- Servidor web embarcado
- Processamento de comandos em tempo real

### Relés
- Componentes físicos de chaveamento
- Controle via sinais digitais
- Estados binários (Ligado/Desligado)
- Feedback de estado atual