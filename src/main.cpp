#include <Arduino.h>

#include <TimeLib.h>

unsigned long time;

int calcMin;
int calcHour;
int calcDay;

const int ledVerde = 12;
const int ledVermelho = 13;



// Ajusta o tempo do timer

void setTimer(int timeHour, int timeMin)
{

  calcHour = timeHour + hour();

  calcMin = timeMin + minute();

  calcDay = day();
}

// Verifica se o tempo atual é igual o tempo do timer

bool compareTime() {

  if (calcHour <= hour() && calcMin <= minute()) {

    return true;
  } else {
    
    return false;
  }
}

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  Serial.begin(9600);
  setTime(0, 0, 0, 0, 0, 0);

  setTimer( 0, 1);
}

void loop()
{

  Serial.println(compareTime());

  if (compareTime() == true) {

    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    
  } else {

    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    
  }
}







