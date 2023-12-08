#include <Servo.h>
#include <math.h>

// POTENCIOMETRO
int pin1 = A0;
int pin2 = A1;

int pos1;
int pos2;

// ATRIBUI OS PINOS
int servo1Pin = 9;
int servo2Pin = 10;

// DECLARA OS SERVOS
Servo servo1;
Servo servo2;

// LIMITES THETA 1
int minT1 = 0;
int maxT1 = 90;

// LIMITES THETA 2
int minT2 = 0;
int maxT2 = 180;

// TAMANHO DOS EIXOS
int d1 = 10;
int d2 = 20;
int d3 = 10;

// Flag pra indicar se o usuario ainda esta ajustando os angulos
bool ajustando = true;

void setup() {
  
  // CONECTA OS SERVOS
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // INICIALIZA EM SEU ÂNGULO MÍNIMO
  servo1.write(minT1);
  servo2.write(minT2);

  Serial.begin(9600);
}

void loop() {
  int theta1, theta2;
  static int theta1Ant, theta2Ant;
  
  static bool printado = false;

  // Verifica se tem input do Serial Monitor
  if (!printado) {
    Serial.println("Informe 0 quando terminar de ajustar: ");
    printado = true; // Flag pra true pra não printar novamente nesse loop
  }
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '0') {
      ajustando = false;  // Parar de ajustar os angulos
      printado = false;   // Printado para false para printar novamente no próximo loop
    }
  }
  
  // LE VALORES DO POTENCIOMETRO E MAPEIA PARA OS LIMITES DOS SERVOS
  if (ajustando) {
    theta1 = analogRead(pin1);
    theta1 = map(theta1, 0, 1023, minT1, maxT1);
    theta1 = round(theta1 / 5.0) * 5; // AJUSTA PARA MULTIPLOS DE 5
    servo1.write(theta1);
    if (theta1 != theta1Ant) {
      servo1.write(theta1);
      Serial.print("Theta1: ");
      Serial.println(theta1);
      theta1Ant = theta1;
    }

    theta2 = analogRead(pin2);
    theta2 = map(theta2, 0, 1023, minT2, maxT2);
    theta2 = round(theta2 / 5.0) * 5; // AJUSTA PARA MULTIPLOS DE 5
    servo2.write(theta2);
    if (theta2 != theta2Ant) {
      servo2.write(theta2);
      Serial.print("Theta2: ");
      Serial.println(theta2);
      theta2Ant = theta2;
    }
  } else {
    
    // CALCULO DA MATRIZ P
    double P[3][1] = {
      {d1 + (d2 * cos(theta1 * M_PI / 180.0)) + (d3 * cos((theta1 + theta2) * M_PI / 180.0))},
      {(d2 * sin(theta1 * M_PI / 180.0)) + (d3 * sin((theta1 + theta2) * M_PI / 180.0))},
      {1}
    };

    // PRINT DA MATRIZ P
    Serial.println("Matriz P:");
    for (int i = 0; i < 3; ++i) {
      Serial.println(P[i][0], 4);
    }
    
    ajustando = true;
  }
}
