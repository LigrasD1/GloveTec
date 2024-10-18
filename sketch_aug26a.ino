// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "Pulsador/pulsador.h"
#include <Mouse.h>
#include <Keyboard.h>
 #define LED 14
#define CONFIG_LED      pinMode(LED, OUTPUT)
#define AJUSTAR_LED(x)  digitalWrite(LED, x)
#define MS_ESPERA   250
unsigned long t=0;
// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;
#define TiempoMouse 100
// Valores RAW (sin procesar) del acelerometro  en los ejes x,y,z
int ax, ay, az;
int XX, YY;
Pulsador BtnClic(4); //inicializa el boton para el clin
Pulsador Btnp(5); //Inicializa el boton del pulgar en el pin de entrada digital 5 del arduino
Pulsador Btni(6);//Inicializa el boton del indice en el pin de entrada digital 6 del arduino
Pulsador Btnm(7);//Inicializa el boton del dedo mayor en el pin de entrada digital 7 del arduino
Pulsador Btna(8);//Inicializa el boton del anular en el pin de entrada digital 8 del arduino
Pulsador Btnmq(9);//Inicializa el boton del meñique en el pin de entrada digital 9 del arduino
unsigned long tiempo = 0; //En esta variable se guarda el tiempo en el que se presiona un boton, para que no se imprima la letra hasta que no se superen los 1000 milisengudos (variable SM)
int c = 0; // Contador que va de 0 a 29, es para saber cuantas veces se presiona cada boton, dependiendo de que boton se presiona determinadas veces se utiliza para ir a la posición del array
int SM = 1000; // milisengundos que debe esperar antes de imprimir la letras

char Letras[29] = {'a', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ','#'};

void setup() {
  Serial.begin(9600);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  pinMode(4, INPUT);//Define como entrada el pulsador del pin digital 4 para el mouse
  pinMode(5, INPUT);//Define como entrada pulsador de pin digital 5
  pinMode(6, INPUT);//Define como entrada pulsador de pin digital 6
  pinMode(7, INPUT);//Define como entrada pulsador de pin digital 7
  pinMode(8, INPUT);//Define como entrada pulsador de pin digital 8
  pinMode(9, INPUT);//Define como entrada pulsador de pin digital 9
  Mouse.begin();
  
  
}

void loop() {
  // Leer las aceleraciones 
  
// Imprime de la A a la C
  if (Btnp.click() && !Btni.click() && !Btnm.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;
    //Como en el array las letras de la A a la C estan del 0 al 4, el contador para el pulgar se mantendra entre esos valores
    if (c <= 0 || c >= 4) {
      c = 0;
    }
    c++;
  }
  // Imprime de la D a la J
  if (Btni.click() && !Btnp.click() && !Btnm.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    //Como en el array las letras de la D a la J estan del 3 al 11, el contador para el indice se mantendra entre esos valoresyzs

    if (c <= 3 || c >= 11) {
      c = 3;
    }
    c++;
  }
  // Imprime de la K a la P
  if (Btnm.click() && !Btni.click() && !Btnp.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    //Como en el array las letras de la K a la P estan del 10 al 17, el contador para el dedo mayor se mantendra entre esos valores

    if (c <= 10 || c >= 17) {
      c = 10;
    }
    c++;
  }
  // Imprime de la Q a la W
  if (Btna.click() && !Btni.click() && !Btnm.click() && !Btnp.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    //Como en el array las letras de la Q a la W estan del 17 al 24, el contador para el Anular se mantendra entre esos valores

    if (c <= 17 || c >= 24) {
      c = 17;
    }
    c++;
  }

  // Imprime de la X a la Z
  if (Btnmq.click() && !Btni.click() && !Btnm.click() && !Btna.click() && !Btnp.click()) {
    tiempo = millis() + SM;

    //Como en el array las letras de la X a la Z estan del 24 al 30, el contador para el meñique se mantendra entre esos valores

    if (c <= 24 || c >= 30) {
      c = 24;
    }
    c++;
  }

  

  Escribir(tiempo,c);
  DetectarGiroscopio();
  MoverMouse(XX,YY);
  BlinkAsimetrico();
  Click();
  
}

void Click(){
   static unsigned long millis_ant=0;
  	

    if(BtnClic.click()){

      Serial.println("estoy aqui");
      Mouse.click();
    }
}
void Escribir(unsigned long t, int cont){
  if (millis() > t && cont > 0) {
    char letra = Letras[c]; //Se guarda la letra en una variable para poder imprimirla, la letra en la posición "C" del contador en el array
    if(letra=='#'){
      Keyboard.press(KEY_BACKSPACE);
      Keyboard.release(KEY_BACKSPACE);
    }else if(letra==' '){
      Keyboard.print(' ');
    }else{
      Keyboard.print(letra); /*imprime la letra con la funcion keyboard (Si se iciera con digitalWrite, se imprime en la consola, de esta forma se imprime en cualquier lado, ya que 
      lo detecta como un teclado)*/
    }
    


    c = 0; // Vuelve el contador a 0 para que no se vuelva a imprimir la letra otra vez
  }
}
void DetectarGiroscopio(){
  if(millis()>t){
    sensor.getAcceleration(&ax, &ay, &az);
    //Calcular los angulos de inclinacion:
    int accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
    int accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);
    //Mostrar los angulos separadas por un [tab]
    
    XX=map(accel_ang_x,0,90,0,100);
    YY=map(accel_ang_y,0,90,0,100);
    Serial.print(XX);
    Serial.print(",");
    Serial.println(YY);

    t=millis()+110;


    }
    
    
    
  }

void MoverMouse(double x,double y){
  unsigned long millisant=0;
  x=x/-10;
  y=y/-10;
  if(millis()-millisant<TiempoMouse)return;
  millisant=millis();
Mouse.move(x,y,0);

}

void BlinkAsimetrico(void)
    {
    static unsigned long millis_ant=0;
  	static bool estado_led=0;
  	
    if(millis() - millis_ant < MS_ESPERA) return;
    millis_ant= millis();
    
    estado_led= !estado_led;
    AJUSTAR_LED(estado_led);
   

    }
