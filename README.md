# 🌡️ Projeto ESP32 com MQTT e ThingSpeak - Global Solution 2025

Este projeto tem como objetivo demonstrar a leitura de temperatura com sensor DHT22 em uma placa ESP32, envio de dados via protocolo MQTT para o **ThingSpeak**, e acionamento de LEDs com base em limites críticos de temperatura. Desenvolvido como parte da disciplina **Global Solution 2025**, este projeto foi implementado e testado na simulação online **Wokwi**.

## 🛠️ Componentes Utilizados

| Componente       | Quantidade | Descrição                           |
|------------------|------------|-------------------------------------|
| ESP32 DevKit V1  | 1          | Microcontrolador com Wi-Fi integrado |
| Sensor DHT22     | 1          | Sensor de temperatura e umidade     |
| LED Verde        | 1          | Indica temperatura segura           |
| LED Vermelho     | 1          | Indica temperatura perigosa         |
| Wokwi Simulator  | -          | Plataforma online de simulação      |

## 🔌 Esquema de Ligações

O esquema abaixo representa as conexões no Wokwi:

- **DHT22**: 
  - VCC → 3.3V  
  - DATA → GPIO 15  
  - GND → GND  
- **LED Verde** → GPIO 2
- **LED Vermelho** → GPIO 4


## 🚀 Funcionalidades

- Conexão Wi-Fi com rede `Wokwi-GUEST`
- Leitura de temperatura do sensor DHT22
- Envio da temperatura via MQTT para o ThingSpeak (canal privado)
- Acionamento de LED vermelho para temperaturas acima de **35°C**
- Acionamento de LED verde para temperaturas seguras

## 📡 Comunicação MQTT

Os dados são enviados para o broker MQTT do **ThingSpeak**:

- **Broker**: `mqtt3.thingspeak.com`  
- **Porta**: `1883`  
- **Canal**: `2982369`  
- **Tópico de publicação**: `channels/2982369/publish`  
- **Payload**:  
  ```text
  field1=<valor da temperatura>
