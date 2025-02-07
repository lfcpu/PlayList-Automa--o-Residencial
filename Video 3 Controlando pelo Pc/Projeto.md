# Documentação do Sistema de Controle de Relés

## Visão Geral do Sistema
Sistema de controle remoto de relés utilizando ESP8266, Node.js e interface web.

## Diagrama Resumido
```mermaid
sequenceDiagram
    participant U as Usuário
    participant W as Web
    participant N as Node.js
    participant E as ESP8266
    participant R as Relés

    rect rgb(240, 220, 220)
        U->>W: Controla relé
        W->>N: Envia comando
        N->>E: Repassa comando
        E->>R: Executa ação
    end

    rect rgb(220, 220, 240)
        loop Monitoramento
            W->>E: Verifica status
            E-->>W: Retorna estado
        end
    end
```

## Diagrama Detalhado do Sistema
```mermaid
sequenceDiagram
    participant U as Usuário
    participant W as Interface Web
    participant N as Node.js
    participant E as ESP8266
    participant R as Relés

    Note over U,R: Processo de Controle dos Relés
    
    rect rgb(200, 240, 200)
        Note over E: Inicialização do Sistema
        E->>E: Conecta ao WiFi
        E->>E: Inicia Servidor Web
        E->>E: Configura Pinos dos Relés
    end

    rect rgb(240, 220, 220)
        Note over U,R: Ação de Controle
        U->>W: 1. Clica no botão
        W->>W: 2. Executa controlRelay()
        W->>N: 3. GET /control/relay/action
        N->>N: 4. Processa requisição
        N->>E: 5. GET /relay/action
        E->>E: 6. Processa comando
        E->>R: 7. Ativa/Desativa relé
        E-->>N: 8. Retorna status
        N-->>W: 9. Confirma ação
        W-->>U: 10. Atualiza interface
    end

    rect rgb(220, 220, 240)
        Note over U,R: Ciclo de Monitoramento
        loop Cada 2 segundos
            W->>N: Solicita status
            N->>E: Consulta estado
            E->>R: Verifica relés
            R-->>E: Estado atual
            E-->>N: Retorna estado
            N-->>W: Atualiza status
            W-->>U: Mostra estado atual
        end
    end
```

## Explicação do Fluxo

### 1. Inicialização (Verde):
- ESP8266 inicia e conecta à rede WiFi
- Configura os pinos dos relés
- Inicia o servidor web interno

### 2. Controle dos Relés (Vermelho):
1. Usuário clica no botão na interface web
2. JavaScript executa função de controle
3. Requisição enviada ao servidor Node.js
4. Node.js processa e encaminha para ESP8266
5. ESP8266 recebe e executa o comando
6. Relé é ativado/desativado
7. Confirmação retorna pela mesma rota
8. Interface atualiza para mostrar novo estado

### 3. Monitoramento Contínuo (Azul):
- Interface web verifica status a cada 2 segundos
- Requisição passa pelo Node.js até o ESP8266
- ESP8266 retorna estado atual dos relés
- Interface atualiza para mostrar estado real

## Componentes do Sistema

### Interface Web
- HTML/JavaScript para controle
- Botões para cada relé
- Atualização automática de status

### Servidor Node.js
- Intermediário entre interface e ESP8266
- Processa requisições
- Gerencia comunicação

### ESP8266
- Conectado aos relés físicos
- Servidor web embarcado
- Executa comandos de controle

### Relés
- Componentes físicos
- Controlados por sinais do ESP8266
- Estados: Ligado/Desligado