
#include <Stepper.h>
#include <AFMotor.h>

AF_Stepper motor1(200, 1);
int pasos;


void setup()
{  
   Serial.begin(9600);           // set up Serial library at 9600 bps
   Serial.println("Stepper test!");
  
   motor1.setSpeed(10);	
}

void loop()
{  
   if (Serial.available()){
    pasos = Serial.readString().toInt();
    Serial.println(pasos);
    
    motor1.step(pasos, BACKWARD, MICROSTEP);
    }
}
