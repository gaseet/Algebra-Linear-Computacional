#include <Servo.h>
#include <math.h>

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

void setup() {
  
  // CONECTA OS SERVOS
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  
  // INICIALIZA EM SEU ANGULO MINIMO
  servo1.write(minT1);
  servo2.write(minT2);
  
  Serial.begin(9600);
  
}

void loop() {
  
  // ANGULOS MANUALMENTE
  //int theta1 = 0;
  //int theta2 = 0;
  
  // ANGULOS INPUT (SE INPUT NAO FOR INT, ASSUME VALOR 0)
  Serial.println("Informe theta1:");
  while (!Serial.available()) {
    // Aguarda input
  }
  int theta1 = Serial.parseInt();
  
  Serial.println("Informe theta2:");
  while (!Serial.available()) {
    // Aguarda input
  }
  int theta2 = Serial.parseInt();
  
  if (theta1 >= minT1 && theta1 <= maxT1 && theta2 >= minT2 && theta2 <= maxT2) {
    // TAMANHOS DOS EIXOS
    int d1 = 10;
    int d2 = 20;
    int d3 = 10;

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
    
    // ATRIBUI OS ANGULOS
    servo1.write(theta1);
    servo2.write(theta2);
    
  } else if ((theta1 < minT1 || theta1 > maxT1) && (theta2 < minT2 || theta2 > maxT2)) {
    Serial.println("Theta1 e Theta2 estao fora do alcance do motor.");
    
  } else if (theta1 < minT1 || theta1 > maxT1) {
    Serial.println("Theta1 esta fora do alcance do motor.");
  
  } else if (theta2 < minT2 || theta2 > maxT2) {
    Serial.println("Theta2 esta fora do alcance do motor.");

  }
  
  //delay(5000)
  
}
