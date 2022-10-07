#include <SoftwareSerial.h>
#include <Servo.h>
#define RxD 2
#define TxD 3
#define echoPin 6
#define trigPin 7

Servo myServo;  // create servo object to control a servo
Servo myServo2;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

char recvChar;                                        //variable to store character received
SoftwareSerial blueToothSerial(RxD,TxD);              //bluetooth device acts as a serial communication device
                                                      //receive and transmit with respect to the Arduino board
void setup()
{
    Serial.begin(9600);                               //start serial monitor, for communicating with the PC
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT); 
    pinMode(RxD, INPUT);                              //set mode of receive pin (from bluetooth)
    pinMode(TxD, OUTPUT);                             //set mode of transmit pin (to bluetooth)
    blueToothSerial.begin(9600);                      //start the bluetooth serial "port"
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    myServo.attach(4);
    myServo.write(0); 
    myServo2.attach(5);
    myServo2.write(130); 

 
}
void loop()
{    
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;

  
  if(blueToothSerial.available())                              //if character is received from the serial monitor (PC)
  {
      recvChar  = blueToothSerial.read();                      //store character received
      Serial.print(recvChar);}

      if((distance<=17)||(recvChar=='0')){
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        digitalWrite(12,LOW);
      }
             
      if((recvChar=='F')&&(distance>=17)){
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(12,HIGH);
        } 

      if(recvChar=='B'){
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(11,HIGH);
        digitalWrite(12,LOW);
        }  
               
      if(recvChar=='L'){
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        digitalWrite(12,HIGH);
        }   
      if(recvChar=='R'){
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(12,LOW);
        } 

      if(recvChar=='X'){             //Open compartment  
        myServo.write(90);                 
      }
      
      if(recvChar=='Y'){             //Close compartment  
        myServo.write(0);                
      }

      if(recvChar=='P'){             //Extend RFID key  
        myServo2.write(10);                
      }
      
      if(recvChar=='Q'){             //Retract RFID key 
        myServo2.write(130);             
      }
  

}
