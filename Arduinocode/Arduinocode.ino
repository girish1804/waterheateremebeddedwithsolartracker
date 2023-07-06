#include <Servo.h>      //including the library of servo motor 
Servo sg90;             //initializing a variable for servo named sg90
int initial_position = 90;   //Declaring the initial position at 90
int LDR1 = A0;          //Pin at which LDR is connected
int LDR2 = A1;          //Pin at which LDR is connected
int error = 5;          //initializing variable for error
int servopin=9;
float a = A2;         // Pin at which temperature sensor is connected
int greenLed = 5;
int redLed = 7;
int analogValue = 0;
float voltage = 0;
int ledDelay = 1000;
void setup() 
{ 

  sg90.attach(servopin);  // attaches the servo on pin 9
  pinMode(LDR1, INPUT);   //Making the LDR pin as input
  pinMode(LDR2, INPUT);
  Serial.begin(9600);
  pinMode(a, INPUT);
  sg90.write(initial_position);   //Move servo at 90 degree
  delay(2000);            // giving a delay of 2 seconds
  pinMode(4, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed,OUTPUT);
}  
 
void loop() 
{ 
  int R1 = analogRead(LDR1); // reading value from LDR 1
  int R2 = analogRead(LDR2); // reading value from LDR 2
  int diff1= abs(R1 - R2);   // Calculating the difference between the LDR's
  int diff2= abs(R2 - R1);
  analogValue = analogRead(A3);
  voltage = 0.0048*analogValue;
  if((diff1 <= error) || (diff2 <= error))
  {
    Serial.println("CENTERED  LDR values: ");
    Serial.println(R1);
    Serial.println(R2);

    //if the difference is under the error then do nothing
  } else {    
    if(R1 > R2)
    {
      initial_position = --initial_position; 
      Serial.println("MOVES RIGHT"); //Move the servo towards 0 degree
    }
    if(R1 < R2) 
    {
      initial_position = ++initial_position;
      Serial.println("MOVES LEFT"); //Move the servo towards 180 degree
    }
  }
  sg90.write(initial_position); // write the position to servo
  delay(100);
  a=analogRead(2); // reading value from Temperature sensor
  float c=(a/965.0)*5;// Converting to degree celcius

  Serial.print("Temperature:");  
  Serial.println(c);
  if(c>38)
  {
    digitalWrite(4,HIGH);
       // Sound buzzer if temp>38
  }
  else
    digitalWrite(4,LOW);
  if( voltage >= 1.5 )
  {
    digitalWrite(greenLed, HIGH);
    Serial.print("VOLTAGE: ");
    Serial.println(voltage);
  }  
  else if( voltage <= 1)
    {
      digitalWrite(redLed, HIGH);
      Serial.println("Battery LOW");
    }
    
  delay(ledDelay);
  digitalWrite(4,LOW);
  digitalWrite(redLed, LOW); 
  digitalWrite(greenLed, LOW);  
}