#include <Servo.h>

const int MOTOR_PIN = 9;
const int LDR_PIN = A0;
const int BOTAO_PIN = 2;

const int LIMIAR_LUZ = 950;
bool amodoLuminosidade = true;

bool cortinaAberta = true;

int hora = 8; // Inicializa o relógio às 8 horas
int minuto = 0; // Minutos iniciam em 0
unsigned long ultimaAtualizacao = 0; // Para rastrear o tempo da última atualização
const unsigned long intervalo = 1000; // Intervalo de 1 segundo na vida real = 1 minuto no sistema

int horaAbrir = 9; // Padrão
int horaFechar = 10; // Padrão

Servo motor;

// Função para verificar se o botão foi pressionado
bool botaoPressionado() {
    static bool estadoAnterior = HIGH; // Estado inicial do botão (não pressionado)
    bool estadoAtual = digitalRead(BOTAO_PIN);

    if (estadoAnterior == HIGH && estadoAtual == LOW) { // Detecta transição de "não pressionado" para "pressionado"
        estadoAnterior = estadoAtual;
        return true;
    } else {
        estadoAnterior = estadoAtual;
        return false;
    }
}

// Simula o avanço do tempo
void horaSimulada() {
    unsigned long agora = millis(); // Obtém o tempo atual em milissegundos

    if (agora - ultimaAtualizacao >= intervalo) {
        ultimaAtualizacao = agora;
        minuto++;

        // Incrementa a hora se os minutos ultrapassarem 59
        if (minuto >= 60) {
            minuto = 0;
            hora++;
        }

        // Reseta o relógio se as horas ultrapassarem 23
        if (hora >= 24) {
            hora = 0;
        }
    }
}

// Controle baseado na luminosidade
void modoLuminosidade() {
    int leituraLDR = analogRead(LDR_PIN);
    if (leituraLDR > LIMIAR_LUZ) {
        abrirCortina();
    } else {
        fecharCortina();
    }
}

// Controle baseado no horário
void modoHorario() {
    if (hora >= horaAbrir && hora < horaFechar) {
        abrirCortina();
    } else {
        fecharCortina();
    }
}

// Função para abrir a cortina
void abrirCortina() {
  if (!cortinaAberta){
    Serial.println("Abrindo a cortina...");
    motor.write(0); // Ajuste para a posição de "aberto"
    cortinaAberta = true;
  }
}

// Função para fechar a cortina
void fecharCortina() {
  if (cortinaAberta){
    Serial.println("Fechando a cortina...");
    motor.write(90); // Ajuste para a posição de "fechado"
    cortinaAberta = false;
  }
}

void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial
    pinMode(LDR_PIN, INPUT);
    pinMode(BOTAO_PIN, INPUT_PULLUP);
    motor.attach(MOTOR_PIN); // Conecta o servo ao pino

    // Instruções para o usuário
    Serial.println("Sistema de controle de cortina iniciado.");
    Serial.println("Pressione o botão para alternar entre os modos: Horário ou Luminosidade.");
    Serial.println("Digite os horários de abertura e fechamento no formato 'hh' e 'hh' (ex: 7 18).");
}

void loop() {
    horaSimulada();

    // Alterna o modo quando o botão é pressionado
    if (botaoPressionado()) {
        amodoLuminosidade = !amodoLuminosidade;
        Serial.print("Modo alterado para: ");
      if (amodoLuminosidade){
            Serial.println("Controle por luminosidade.");
        } else {
            Serial.println("Controle por horário.");
        }
        delay(500); // Debounce para evitar múltiplas leituras do botão
    }

    // Verifica se há entrada serial para definir os horários
    if (Serial.available() > 0) {
        int comandoAbrir = Serial.parseInt();  // Lê horário de abertura
        int comandoFechar = Serial.parseInt(); // Lê horário de fechamento
        if (comandoAbrir >= 0 && comandoAbrir < 24 && comandoFechar > comandoAbrir && comandoFechar <= 24) {
            horaAbrir = comandoAbrir;
            horaFechar = comandoFechar;
            Serial.print("Horários atualizados: abrir às ");
            Serial.print(horaAbrir);
            Serial.print(":00, fechar às ");
            Serial.print(horaFechar);
            Serial.println(":00.");
        } else {
            Serial.println("Entrada inválida. Certifique-se de usar valores entre 0 e 24, e o horário de abertura deve ser antes do fechamento.");
        }
    }

    // Controle da cortina baseado no modo
    if (amodoLuminosidade) {
        modoLuminosidade();
    }else {
        modoHorario();
    }

    delay(100); // Aguarda para evitar leituras muito rápidas
}
