# **Sistema Automatizado de Controle de Cortinas**

Este projeto implementa um sistema automatizado para controle de cortinas utilizando Arduino. O sistema pode operar em dois modos: controle por **luminosidade** (sensor LDR) ou **horário** (simulação de tempo). Além disso, o sistema permite alternar entre os modos com um botão físico e configurar os horários de abertura e fechamento por meio do monitor serial.

---

## **Características do Projeto**
- **Controle por luminosidade:** Abre ou fecha a cortina com base na quantidade de luz detectada por um sensor LDR.
- **Controle por horário:** Define intervalos de tempo para abertura e fechamento da cortina.
- **Simulação de tempo:** Relógio virtual que avança em minutos a cada segundo real.
- **Alternância de modos:** Um botão físico alterna entre os modos de operação.
- **Configuração dinâmica:** Os horários de abertura e fechamento podem ser ajustados via entrada serial.

---

## **Componentes Necessários**
- 1 Arduino (Uno, Nano ou compatível)
- 1 Servo motor
- 1 LDR (resistor dependente de luz)
- 1 Resistor (10 kΩ recomendado, para o LDR)
- 1 Botão push-button
- Jumpers e cabos de conexão
- Protoboard ou circuito soldado

---

## **Esquema de Conexão**
1. **Servo Motor:**  
   - Sinal no pino digital **9**  
   - VCC (5V) e GND no Arduino.

2. **Sensor LDR:**  
   - Um lado conectado ao pino analógico **A0** e ao VCC.  
   - Outro lado ao GND, com resistor de **10 kΩ** conectado ao GND e ao pino **A0**.

3. **Botão Push-Button:**  
   - Um lado conectado ao pino digital **2** (com `INPUT_PULLUP` configurado).  
   - Outro lado ao GND.

---

## **Como Usar**
1. **Configuração Inicial:**
   - Suba o código no Arduino.
   - Monte o circuito conforme o esquema descrito.
   - Abra o monitor serial (configurado para **9600 baud**) para interagir com o sistema.

2. **Alternar Modos:**
   - Pressione o botão físico para alternar entre os modos **luminosidade** e **horário**.
   - O monitor serial informará o modo selecionado.

3. **Configuração de Horários:**
   - No monitor serial, insira os horários de abertura e fechamento no formato `hh hh` (por exemplo: `7 18`).
   - Certifique-se de que o horário de abertura seja anterior ao de fechamento.

4. **Operação:**
   - Em **modo luminosidade**, a cortina abre ou fecha automaticamente com base na luz detectada.
   - Em **modo horário**, a cortina segue os horários configurados.

---

## **Código**
O código principal está no arquivo `cortina_automatica.ino`. Ele utiliza as seguintes funções:
- **horaSimulada():** Simula a passagem de tempo.
- **modoLuminosidade():** Controla a cortina com base no sensor LDR.
- **modoHorario():** Controla a cortina com base nos horários configurados.
- **abrirCortina() / fecharCortina():** Movimentam o servo motor para abrir ou fechar a cortina.

---

## **Melhorias Futuras**
- Integração com relógios de tempo real (RTC) para sincronização com a hora real.
- Adicionar um display LCD ou OLED para exibir o modo atual e os horários configurados.
- Controle remoto via aplicativo ou Wi-Fi usando módulos como ESP8266/ESP32.

---

## **Licença**
Este projeto é livre para uso educacional e não comercial. Contribuições são bem-vindas!

---

💡 Desenvolvido para automação simples e eficiente de residências.
