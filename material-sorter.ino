#include <Servo.h>

//CODIGO FINAL
//unicas coisas para prestar a atenção potenciometro e analise dos picos
// ultimo recurso deixar o sensor em 50 e identificar só as pancadas do vidro, e identificar o plastico por exclusão
// Definir pinos e constantes
#define pinServo 9


Servo servo1;
int grau = 0;

const int sensorPin = 7; // Pino Sensor de indução metal
const int SOUND_SENSOR_PIN = 8;    // Pino digital conectado ao sensor KY-037
const int INTERVALO_TEMPO = 1000;  // Intervalo de tempo para contar os quiques (em milissegundos)
unsigned long tempoAnterior = 0;   // Armazena o tempo da última leitura
int contadorQuiques = 0;           // Contador de quiques (impactos)

const int SAMPLE_TIME = 10;        // Tempo entre amostras
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;
int picoThreshold = 100;           // Limiar para considerar um pico

bool picoAtivo = false;            // Indica se um pico está ativo
bool metalIdentifier = false; //se o metal foi identificado

void setup() {
  Serial.begin(9600);              // Inicializa a comunicação serial
  pinMode(SOUND_SENSOR_PIN, INPUT);
  servo1.attach(pinServo);
  pinMode(13, OUTPUT);
  pinMode(13, LOW);
  pinMode(12, OUTPUT);
  pinMode(12, LOW);
  pinMode(14, OUTPUT);
  pinMode(14, LOW);
  pinMode(sensorPin, INPUT); // pino do metal
  //7 sensor de inducao metal, 8 sensor de som, 9 servo cancela, 13 led1, 12 led2, 14 led3
}

void loop() {
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;  // Tempo decorrido desde a última amostra

  // Detecta se há um som (LOW indica que o som foi detectado)
  if (digitalRead(SOUND_SENSOR_PIN) == LOW && digitalRead(sensorPin) == true) {
    metalIdentifier = true;
  } else if (digitalRead(SOUND_SENSOR_PIN) == LOW && digitalRead(sensorPin) == false) {
    sampleBufferValue++;
  }

  // Se o tempo de amostragem passou, avalia o valor do buffer
  if (millisElapsed > SAMPLE_TIME) {
    // Detectar um pico quando o valor buffer for maior que o limiar
    if (sampleBufferValue > picoThreshold && !picoAtivo) {
      picoAtivo = true;            // Ativar o pico
      contadorQuiques++;           // Contar o quique
      Serial.println("Pico detectado!");
    }

    // Se o buffer retornar a 0, desativa o pico
    if (sampleBufferValue == 0 && picoAtivo) {
      picoAtivo = false;           // Desativar o pico quando o som termina
      Serial.println("Fim do pico.");
    }

    // Resetar o buffer de amostra para o próximo ciclo
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }

  // Verifica se o intervalo de tempo se passou para analisar os quiques
  if (millisCurrent - tempoAnterior > INTERVALO_TEMPO && !picoAtivo) {
    // Decisão baseada no número de quiques
    if (contadorQuiques >= 2) {
      Serial.println("Material detectado: Plastico");
      delay(5000); //5 seg de espera
      digitalWrite(13, HIGH);
      delay(5000);//para o 2 servo girar
      //gireServo2ParaPosiçãoDoLixoCorreto();
      servo1.write(180);
      delay(5000); //5 seg de espera
    } else if (contadorQuiques == 1) {
      Serial.println("Material detectado: Vidro");
      delay(5000); //5 seg de espera
      digitalWrite(12, HIGH);
      delay(5000);
      //gireServo2ParaPosiçãoDoLixoCorreto();
      servo1.write(180);
      delay(5000); //5 seg de espera
    } else if (metalIdentifier == true) {
      Serial.println("Material detectado: Metalico");
      delay(5000); //5 seg de espera
      digitalWrite(14, HIGH);
      delay(5000);
      //gireServo2ParaPosiçãoDoLixoCorreto();
      servo1.write(180);
      delay(5000); //5 seg de espera
    } else {
      Serial.println("Nenhum som detectado dentro do intervalo.");
    }
    //13 led 1
    if (digitalRead(13) == HIGH ) { //dependendo do led acesso voce usa para girar o servo2 para lixaira certa;
      servo2.write(0);//espera um tempo ate a garrafa cair no lixo e depois volta
    }
    //12 led2
    if (digitalRead(12) == HIGH ) { //dependendo do led acesso voce usa para girar o servo2 para lixaira certa;
      servo2.write(90);//espera um tempo ate a garrafa cair no lixo e depois volta
    }
    //14 led3
    if (digitalRead(14) == HIGH ) { //dependendo do led acesso voce usa para girar o servo2 para lixaira certa;
      servo2.write(180);//espera um tempo ate a garrafa cair no lixo e depois volta
    }

    // Reseta as variáveis para a próxima medição
    servo1.write(180);//deve abrir e deve voltar pro zero
    contadorQuiques = 0;
    tempoAnterior = millisCurrent;
  }
}


























//CODIGO FINAL
//unicas coisas para prestar a atenção potenciometro e analise dos picos
// ultimo recurso deixar o sensor em 50 e identificar só as pancadas do vidro, e identificar o plastico por exclusão
// Definir pinos e constantes
/*const int SOUND_SENSOR_PIN = 8;    // Pino digital conectado ao sensor KY-037
const int INTERVALO_TEMPO = 1000;  // Intervalo de tempo para contar os quiques (em milissegundos)
unsigned long tempoAnterior = 0;   // Armazena o tempo da última leitura
int contadorQuiques = 0;           // Contador de quiques (impactos)

const int SAMPLE_TIME = 10;        // Tempo entre amostras
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;
int sampleBufferValue = 0;
int picoThreshold = 100;           // Limiar para considerar um pico

bool picoAtivo = false;            // Indica se um pico está ativo

void setup() {
  Serial.begin(9600);              // Inicializa a comunicação serial
  pinMode(SOUND_SENSOR_PIN, INPUT);
}

void loop() {
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;  // Tempo decorrido desde a última amostra

  // Detecta se há um som (LOW indica que o som foi detectado)
  if (digitalRead(SOUND_SENSOR_PIN) == LOW) {
    sampleBufferValue++;
  }

  // Se o tempo de amostragem passou, avalia o valor do buffer
  if (millisElapsed > SAMPLE_TIME) {
    // Detectar um pico quando o valor buffer for maior que o limiar
    if (sampleBufferValue > picoThreshold && !picoAtivo) {
      picoAtivo = true;            // Ativar o pico
      contadorQuiques++;           // Contar o quique
      Serial.println("Pico detectado!");
    }

    // Se o buffer retornar a 0, desativa o pico
    if (sampleBufferValue == 0 && picoAtivo) {
      picoAtivo = false;           // Desativar o pico quando o som termina
      Serial.println("Fim do pico.");
    }

    // Resetar o buffer de amostra para o próximo ciclo
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }

  // Verifica se o intervalo de tempo se passou para analisar os quiques
  if (millisCurrent - tempoAnterior > INTERVALO_TEMPO && !picoAtivo) {
    // Decisão baseada no número de quiques
    if (contadorQuiques >= 2) {
      Serial.println("Material detectado: Plastico");
      delay(10000); //10 seg de espera
    } else if (contadorQuiques == 1) {
      Serial.println("Material detectado: Vidro");
      delay(10000); //10 seg de espera
    } else {
      Serial.println("Nenhum som detectado dentro do intervalo.");
    }

    // Reseta as variáveis para a próxima medição
    contadorQuiques = 0;
    tempoAnterior = millisCurrent;
  }
}*/