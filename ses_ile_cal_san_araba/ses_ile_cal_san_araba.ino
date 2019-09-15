
#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <Servo.h>   //Servo library. This is standard library. (Sketch -> Include Library -> Servo)
String voice;

AF_DCMotor motor1 (1, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2 (2, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
Servo myServo; //define servo name
int LED1 = A0; //define LED 1 pin
int LED2 = A1; //define LED 2 pin
int buzzerPin = A2; //define buzzer pin


void setup()
{
  Serial.begin(9600); //start serial communication
  myServo.attach(10); //define our servo pin (the motor shield servo1 input = digital pin 10)
  myServo.write(90);  //servo position is 90 degrees
  pinMode(LED1, OUTPUT); //A0 is output pin
  pinMode(LED2, OUTPUT); //A1 is output pin
  pinMode(buzzerPin, OUTPUT); //A2 is output pin
}

void loop() 
{
  while (Serial.available()){ //Check if there is an available byte to read
     delay(10); //Delay added to make thing stable 
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {break;} //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0){
    if(voice == "*ileri git"){
      forward_car();
      }
    else if(voice == "*geri git"){
      back_car();
      }
    else if(voice == "*sola dön") {
      right_car();
    }
    else if(voice == "*sağa dön") {
      left_car();
    }
    else if(voice == "*far aç") {
      LED_on();
    }
    else if(voice == "*far kapat") {
      LED_off();
    }
    else if(voice == "*korna çal") {
      buzzer_on();
    }
    else if(voice == "*dur") {
      stop_car();
    }
    
  voice=""; //Reset the variable after initiating
  }
}

void forward_car() // 
{
  motor1.run(FORWARD);
  motor1.setSpeed(200);
  motor2.run(FORWARD);
  motor2.setSpeed(200);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void back_car() // geri komutları 
{
  motor1.run(BACKWARD);
  motor1.setSpeed(200);
  motor2.run(BACKWARD);
  motor2.setSpeed(200);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void right_car()
{
  myServo.write(180);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor1.run(FORWARD);
  motor1.setSpeed(90);
  motor2.run(BACKWARD);
  motor2.setSpeed(90);
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
  
void left_car()
{
  myServo.write(
    0);
  delay(1000);
  myServo.write(90);
  delay(1000);
  motor1.run(BACKWARD);
  motor1.setSpeed(100);
  motor2.run(FORWARD);
  motor2.setSpeed(100);
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void LED_on ()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void LED_off ()
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void buzzer_on ()
{
  tone(buzzerPin, 100);
  delay(800);
  noTone(buzzerPin);
}

void stop_car ()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
