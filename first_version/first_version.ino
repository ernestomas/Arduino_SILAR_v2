#include <Stepper.h>            //Librer\'ia del Adafruit Motor Shield V1
#include <AFMotor.h>            //Librer\'i interna de Arduino para Stepers

AF_Stepper plate(200, 1);       //Nombre del motor(pasos por vueltas, a la puerta M1 M2)
AF_Stepper crane(50, 2);        //Nombre del motor(pasos por vueltas, a la puerta M3 M4)

int pasos_base;
int pasos_crane;
int initial_position_base = 0;
int initial_position_crane = 0;
int initial_position = 0;


void setup()
{  
   Serial.begin(9600);           //Comunicaci\'on serial con la PC
      delay(30);                 //Esperar 30 milisegundos
      crane.setSpeed(50);        //Define velocidad de giro en rpm de la grua
      plate.setSpeed(6);         //Define velocidad de giro en rpm de la base
}

void loop(){  
   if (Serial.available()){
    
    String orden = Serial.readString();                              //lee la orden 
    
    int comilla = orden.indexOf("["); 
                                  
    int sep1 = orden.indexOf("/");
    
    int pos = orden.substring(comilla+1,sep1).toInt();
    
    int sep2 = orden.indexOf("/",sep1+1);
    
    int base = orden.substring(sep1+1,sep2).toInt();                //Movimiento de la base.  

    int sep3 = orden.indexOf("/",sep2+1);
    
    int crane_step = orden.substring(sep2+1,sep3).toInt();          //Movimiento de la grua.
    
    if (initial_position =! pos){
      
        for (int i = 0; i<initial_position_crane; i++){
          
          crane.step(1, FORWARD, MICROSTEP);
        }
        for (int i = 0; i<initial_position_base; i++){
          
          plate.step(1, BACKWARD, MICROSTEP);
         }
        initial_position_base = 0;
        
        initial_position_crane = 0;

        initial_position = pos;
    }

    pasos_base = base - initial_position_base;
    
    initial_position_base = base;
    
    pasos_crane = crane_step - initial_position_crane;
    
    initial_position_crane = crane_step;
    
    if (pasos_base == 0){
      
      delay(30);
      
    }else if (pasos_base > 0){
      
      for (int j = 0 ;j < pasos_base; j++){
        
        plate.step(1, FORWARD, MICROSTEP);
      }  
    }else if (pasos_base < 0){
      
      for (int j = 0 ;j < pasos_base; j++){
        
        plate.step(1, BACKWARD, MICROSTEP);
        
      }
    }

    if (pasos_crane == 0){

      delay(30);
      
    }else if (pasos_crane > 0){
      
      for (int j = 0 ;j < pasos_crane; j++){
        
        crane.step(1, BACKWARD, MICROSTEP);
      }  
    }else if (pasos_crane < 0){
      
      for (int j = 0 ;j < pasos_crane; j++){
        
        crane.step(1, FORWARD, MICROSTEP);
      }
    }
   
   }
}


