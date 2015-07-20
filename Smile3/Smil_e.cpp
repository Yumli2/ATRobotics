#include "Smile.h"

//PID
//=====================================================================================================================
PID::PID(double _kP, double _kI, double _kD) { //Recebe os parametros das constantes
  kP = _kP;
  kI = _kI;
  kD = _kD;
}

void PID::addNewSample(double _sample) { //Recebe as amostras lidas de algo Exemplo.: distancia, temperatura...
  sample = _sample;
}

void PID::setSetPoint(double _setPoint) { //Defini qual o offset/inicio
  setPoint = _setPoint;
}

double PID::process() { //retorna o valor calculado do PID
  // Implementação P I D
  error = setPoint < 0 ? sample + setPoint : setPoint - sample;
  float deltaTime = (millis() - lastProcess) / 1000.0;
  lastProcess = millis();

  //P
  P = error * kP;

  //I
  I += (error * kI) * deltaTime;

  //D
  D = (lastSample - sample) * kD / deltaTime;
  lastSample = sample;

  // Soma tudo
  //pid = P + I + D;

  return P + I + D;
}
//LED rgb
//=====================================================================================================================
LED::LED(short int _reD, short int _bluE, short int _greeN) {
  PinRed = _reD;
  PinBlue = _bluE;
  PinGreen = _greeN;
  pinMode(PinRed, OUTPUT); pinMode(PinBlue, OUTPUT); pinMode(PinGreen, OUTPUT);
}
void LED::statusRed(short int _statusR) {
  short int statusR = _statusR;
  statusR != 0 ? digitalWrite(PinRed, 1) : digitalWrite(PinRed, 0);
}
void LED::statusBlue(short int _statusB) {
  short int statusB = _statusB;
  statusB != 0 ? digitalWrite(PinBlue, 1) : digitalWrite(PinBlue, 0);
}
void LED::statusGreen(short int _statusG) {
  short int statusG = _statusG;
  statusG != 0 ? digitalWrite(PinGreen, 1) : digitalWrite(PinGreen, 0);
}

//Ultrasson
//=====================================================================================================================
ULTRA::ULTRA(int _echoPin, int _trigPin) {
  echoPin = _echoPin;
  trigPin = _trigPin;
  pinMode(echoPin, INPUT); pinMode(trigPin, OUTPUT);
}
int ULTRA::distancia() {
  //seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0
  digitalWrite(trigPin, LOW);
  // delay de 2 microssegundos
  delayMicroseconds(2);
  //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1
  digitalWrite(trigPin, HIGH);
  //delay de 10 microssegundos
  delayMicroseconds(10);
  //seta o pino 12 com pulso baixo novamente
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  disT = duracao / 58.82;

  return disT;

}


