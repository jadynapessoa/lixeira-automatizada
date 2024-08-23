#include <Servo.h>  // Biblioteca para controlar o servo motor

// Definindo pinos
const int trigPin = 5;  // Pino do trigger do sensor ultrassônico
const int echoPin = 6;  // Pino do echo do sensor ultrassônico
const int servoPin = 7; // Pino do servo motor

Servo servo;  // Cria um objeto Servo para controlar o servo motor

void setup() {
    Serial.begin(9600);      // Inicializa a comunicação serial
    servo.attach(servoPin);  // Conecta o servo motor ao pino especificado
    pinMode(trigPin, OUTPUT); // Define o pino do trigger como saída
    pinMode(echoPin, INPUT);  // Define o pino do echo como entrada
    servo.write(0);          // Inicializa o servo motor com a tampa fechada
    delay(100);
}

void measureDistance() {
    // Emite um pulso no pino do trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Lê o tempo do pulso retornado pelo pino do echo
    long duration = pulseIn(echoPin, HIGH);

    // Calcula a distância em centímetros
    long distance = (duration / 2) / 29.1;
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 50) {  // Se a distância for menor que 50 cm
        servo.write(90); // Abre a tampa (ajuste o ângulo conforme necessário)
        delay(3000);     // Mantém a tampa aberta por 3 segundos
        servo.write(0);  // Fecha a tampa
        delay(1000);     // Aguarda 1 segundo antes de permitir a próxima abertura
    }
}

void loop() {
    measureDistance();  // Mede a distância e controla o servo motor
    delay(500);         // Aguarda 500 ms antes da próxima medição
}
