// Variable Moteur
const int PWMG = 10; // Moteur Gauche
const int PWMD = 9; // Moteur Droit
const int SENSG = 11; // Sens Moteur Gauche
const int SENSD = 12; // Sens Moteur Droit

const int jack = 4; // PIN Jack

// Variable Capteur Sharp
const int pinSharpFront = A2;

void setup() {
  pinMode(PWMG, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(SENSG, OUTPUT);
  pinMode(SENSD, OUTPUT);
  pinMode(pinSharpFront, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Distance : "+(String) ((4.0/(analogRead(pinSharpFront)*0.00340))*2) + ";" );
  if(isJack()==true)
  {
    if(sharpFront()==false)
    {
      forward(25);
    }
    else
    {
      backward(25);
      delay(500);
      stop();
      left45();
    }
  }
  else {
    stop();
  }
}

bool isJack()
{
  return digitalRead(jack);
}

byte convertSpeed(int speedFunc)
{
  return map(speedFunc, 0, 100, 0, 255);
}

void forward(int speedFunc)
{
  analogWrite(PWMG,convertSpeed(speedFunc));
  analogWrite(PWMD,convertSpeed(speedFunc));
  digitalWrite(SENSG,HIGH);
  digitalWrite(SENSD,LOW);
}

void backward(int speedFunc)
{
  analogWrite(PWMG,convertSpeed(speedFunc));
  analogWrite(PWMD,convertSpeed(speedFunc));
  digitalWrite(SENSG,LOW);
  digitalWrite(SENSD,HIGH);
}

void left45()
{
  analogWrite(PWMG,convertSpeed(25));
  analogWrite(PWMD,convertSpeed(25));
  digitalWrite(SENSG,LOW);
  digitalWrite(SENSD,LOW);
  delay(800/2);
  stop();
}

void stop()
{
  analogWrite(PWMG,0);
  analogWrite(PWMD,0);
}

bool sharpFront()
{
  float distance = 25.0;
  if( ((4.0/(analogRead(pinSharpFront)*0.00340))*2) < distance )
  {
    return true;
  }
  else
  {
    return false;
  }
}