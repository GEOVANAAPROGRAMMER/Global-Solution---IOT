# **Global Solution -  Eficiência Energética com Automação**

### **Integrantes do Grupo**
- **Ana Beatriz Bento da Silva** - RM555336  
- **Geovana Ribeiro Domingos Silva** - RM99646  
- **Leonardo Camargo Lucena** - RM552537  
- **Nathan Nunes Calsonari** - RM552539  
- **Ruan Guedes de Campos** - RM551096  

---

## **Índice**
1. [Objetivo do Projeto](#objetivo-do-projeto)  
2. [Detalhamento da Arquitetura de IoT](#detalhamento-da-arquitetura-de-iot)  
3. [Protótipo Funcional](#protótipo-funcional)  
4. [Layout do Protótipo](#layout-do-protótipo)  
5. [Como Rodar Este Projeto?](#como-rodar-este-projeto)
6. [Utilizando o Node-RED](#utilizando-o-node-red)  
7. [Links Importantes](#links-importantes)  

---

## **Objetivo do Projeto**
O objetivo deste projeto é criar um sistema IoT usando o Arduino Uno, simulando dispositivos conectados e monitorando informações como movimento e temperatura em um ambiente inteligente.  

Por limitações técnicas, a comunicação com o Node-RED foi simulada via monitor serial, permitindo que os dados coletados pelos sensores fossem exibidos no console.  

As principais funcionalidades incluem:
- Detecção de movimento com um sensor PIR.  
- Monitoramento de temperatura usando um termistor.  
- Controle de dispositivos (simulado com LEDs).  

---

## **Detalhamento da Arquitetura de IoT**
### **Componentes Utilizados**
1. **Hardware (Simulado no Wokwi)**  
   - **Arduino Uno**: Microcontrolador responsável por processar as informações.  
   - **Sensor PIR**: Detecta movimento no ambiente.  
   - **Termistor**: Mede a temperatura ambiente.  
   - **LEDs**: Simulam dispositivos como lâmpadas e controle de ar-condicionado.  

2. **Software**  
   - Monitor Serial: Usado para exibir as informações coletadas e enviar comandos.  
   - Node-RED: Utilizado apenas para simulação de uma interface gráfica de monitoramento.  

### **Fluxo de Dados**
1. Os sensores PIR e de temperatura coletam informações do ambiente.  
2. As informações são processadas pelo Arduino Uno e exibidas no monitor serial.  
3. Simula-se a interação com dispositivos (ex.: ligar/desligar LEDs) com base nos dados dos sensores.  

---

## **Protótipo Funcional**
- **Simulação no Wokwi**:  
  O projeto é executado no simulador Wokwi, que permite emular o funcionamento dos sensores e LEDs.  

- **Funcionalidades Implementadas**:  
  - **Sensor PIR**: Detecta movimento e acende um LED para simular uma lâmpada.  
  - **Termistor**: Mede a temperatura ambiente e ajusta o nível simulado de um ar-condicionado (representado por LEDs).  
  - **Monitor Serial**: Exibe os dados coletados e os estados dos dispositivos em tempo real.  

---

## **Layout do Protótipo**
### **Circuito no Wokwi**
<img width="467" alt="image" src="https://github.com/user-attachments/assets/d47078d9-2dae-4e9c-850a-c60c5bee0ece">


### **Saída no Monitor Serial**
<img width="481" alt="image" src="https://github.com/user-attachments/assets/128e9831-5c6c-4e68-9938-b8cf4b8ae5bb">

---

## **Como Rodar Este Projeto?**
### **Pré-requisitos**
1. Conta no [Wokwi](https://wokwi.com/).  
2. Arduino IDE instalado para simulação local (opcional).  
3. Configuração do circuito com os componentes descritos.  

### **Passos para Executar**
1. **Configuração no Wokwi**  
   - Acesse o Wokwi e configure o circuito conforme o layout fornecido.  
   - Carregue o código do projeto no simulador.  

2. **Execução no Simulador**  
   - Inicie a simulação no Wokwi.  
   - Acompanhe os dados no monitor serial (disponível no Wokwi).  

3. **Interação com o Sistema**  
   - Ative o sensor PIR para simular movimento e veja o LED acender.  
   - Alterne a temperatura no termistor para simular o ajuste do "ar-condicionado".  

---

## **Utilizando o Node-RED**
1. **Instalação e Configuração do Node-RED**  
   - Baixe e instale o Node-RED a partir do [site oficial](https://nodered.org/).  
   - Inicie o Node-RED executando o comando `node-red` no terminal.  
   - Abra o painel do Node-RED no navegador acessando `http://localhost:1880`.  

2. **Importando o Fluxo**  
   - No painel do Node-RED, clique no botão de menu (canto superior direito) e selecione **Import > Clipboard**.  
   - Abra o arquivo `flows(1).json` com um editor de texto e copie o conteúdo.  
   - Cole o conteúdo no Node-RED e clique em **Import**.  

3. **Executando o Fluxo**  
   - Conecte os nós e clique no botão **Deploy** para iniciar o fluxo.  
   - **Nota Importante**: O fluxo é apenas uma simulação e não está conectado ao Wokwi ou ao Arduino Uno. 

## **Links Importantes**
- [Wokwi (Simulador IoT)](https://wokwi.com/projects/415201099640704001)  
- [Github](https://github.com/GEOVANAAPROGRAMMER/Global-Solution---IOT)  
- [Vídeo](https://youtu.be/wG3ZbnKdkhc)  
