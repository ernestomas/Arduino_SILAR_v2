#include <Stepper.h>            //Librer\'ia del Adafruit Motor Shield V1
#include <AFMotor.h>            //Librer\'i interna de Arduino para Stepers

AF_Stepper plate(200, 1);       //Nombre del motor(pasos por vueltas, a la puerta M1 M2)
AF_Stepper crane(50, 2);        //Nombre del motor(pasos por vueltas, a la puerta M3 M4)

int pasos;


void setup()
{  
   Serial.begin(9600);           //Comunicaci\'on serial con la PC
      delay(30);                 //Esperar 30 milisegundos
      crane.setSpeed(50);        //Define velocidad de giro en rpm de la grua
      plate.setSpeed(6);         //Define velocidad de giro en rpm de la base
}

void loop()
{  
   if (Serial.available()){
    String orden = Serial.readString();                             //lee la orden 

    if (orden == "up"){
    crane.step(50, BACKWARD, MICROSTEP);
    delay(5000);
    for (int k = 0 ;k < 50; k++){
          plate.step(1, FORWARD, MICROSTEP);
          //Serial.println("la grua da "+String(j)+" hacia atras");
        }
    }else if (orden == "down"){
    crane.step(50, FORWARD, MICROSTEP);
    delay(5000);
    for (int k = 0 ;k < 50; k++){
          plate.step(1, BACKWARD, MICROSTEP);
          //Serial.println("la grua da "+String(j)+" hacia atras");
        }  
    }else if (orden == "right"){
    plate.step(50, BACKWARD, MICROSTEP);
    delay(5000);
    for (int k = 0 ;k < 50; k++){
          plate.step(1, FORWARD, MICROSTEP);
          //Serial.println("la grua da "+String(j)+" hacia atras");
        }
    }else if (orden == "left"){
    plate.step(50, FORWARD, MICROSTEP);
    delay(5000);
    for (int k = 0 ;k < 50; k++){
          plate.step(1, BACKWARD, MICROSTEP);
          //Serial.println("la grua da "+String(j)+" hacia atras");
        }
    }
   }
}


