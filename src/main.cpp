#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <Keypad.h>

unsigned long time;

unsigned long calcMin;
unsigned long calcHour;
int timeHour;
int timeMin;
unsigned long calcTemp;


const int ledVerde = 12;
const int ledVermelho = 13;

Adafruit_SSD1306 display = Adafruit_SSD1306();

byte LinePin[] = {10, 9, 8};

byte ColumnPin[] = {11};

char keys[3][1] = {
    {'i'},
    {'d'},
    {'s'}};

char valueKey;

Keypad keyBord = Keypad{makeKeymap(keys), LinePin, ColumnPin, 3, 1};

// Ajusta o tempo do timer

void setTimer(int value)
{

  if (value == 1)
  {

    if (timeMin < 60)
    {

      timeMin += 1;
    }
    else if (timeMin >= 60)
    {

      timeMin = 0;
      timeHour += 1;
    }
  }
  else if (value == 2)
  {

    if (timeMin > 0)
    {

      timeMin -= 1;
    }
    else if (timeHour == 0 && timeMin == 0)
    {

      timeHour = 0;
      timeMin = 0;
    }
    else if (timeMin == 0)
    {

      timeMin = 60;
      timeHour -= 1;
    }
  }
  else if (value == 3)
  { 

    calcHour = timeHour * 3600000;

    calcMin = timeMin * 60000;

    calcTemp = (calcHour + calcMin) + time;

    timeHour = 0;
    timeMin = 0;

  }
}

// Verifica se o tempo atual é igual o tempo do timer

bool compareTime()
{

  if (calcTemp <= time)
  {

    return true;
  }
  else
  {

    return false;
  }
}


// Atribui uma ação para cada botão

void actionKey()
{

  if (valueKey == 'i')
  {
    setTimer(1);
  }

  if (valueKey == 'd')
  {

    setTimer(2);
  }

  if (valueKey == 's')
  {

    setTimer(3);
  }
}

void setup()
{

  timeHour = 0;
  timeMin = 0;

  String HourConv = String(timeHour);
  String minConv = String(timeMin);
  //Inincializa o Wire
  Wire.begin();
  //Inicializa o display com endereço I2C 0x3c
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE); //Define a Cor do Texto
  display.setTextSize(1);      //Define o tamanho do Texto
  display.clearDisplay();      //Limpa o display

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);


  display.setCursor(40, 16);

  display.print("Timer Fan");

  display.display();
  delay(2000);

  display.clearDisplay();



  display.setCursor(60, 8);

  display.print("H  M");

  display.display();

  display.setCursor(60, 16);

  display.print(HourConv + " " + minConv);

  display.display();

  display.clearDisplay();



  Serial.begin(9600);
}

void loop()
{
  time = millis();

  String HourConv = String(timeHour);
  String minConv = String(timeMin);



  valueKey = keyBord.getKey();

    actionKey();

  if (valueKey != ' ')
  {

    display.setCursor(60, 8);

    display.print("H  M");

    display.display();

    display.setCursor(60, 16);

    display.print(HourConv + " " + minConv);

    display.display();

    display.clearDisplay();
  }

  
  // Verifica se horário atual é igual a do timer

  if (compareTime() == true)
  {

    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
  }
  else
  {

    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
  }
}
