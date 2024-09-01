#include "Pulsador/Pulsador.h"
#include <Keyboard.h> // Incluir la biblioteca SoftwareSerial

int x = 0;
Pulsador Btnp(6); 
Pulsador Btni(7);
Pulsador Btnm(8);
Pulsador Btna(9);
Pulsador Btnmq(10);
unsigned long tiempo = 0;
int c = 0;
int SM = 1000;
char Letras[29] = {'a', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ','#'};
 

void setup() {
  Serial.begin(9600);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  randomSeed(analogRead(0));
}

void loop() {

  
  // Imprime de la A a la C
  if (Btnp.click() && !Btni.click() && !Btnm.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    if (c <= 0 || c >= 4) {
      c = 0;
    }
    c++;
  }
  // Imprime de la D a la J
  if (Btni.click() && !Btnp.click() && !Btnm.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    if (c <= 3 || c >= 11) {
      c = 3;
    }
    c++;
  }
  // Imprime de la K a la P
  if (Btnm.click() && !Btni.click() && !Btnp.click() && !Btna.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    if (c <= 10 || c >= 17) {
      c = 10;
    }
    c++;
  }
  // Imprime de la Q a la W
  if (Btna.click() && !Btni.click() && !Btnm.click() && !Btnp.click() && !Btnmq.click()) {
    tiempo = millis() + SM;

    if (c <= 17 || c >= 24) {
      c = 17;
    }
    c++;
  }

  // Imprime de la X a la Z
  if (Btnmq.click() && !Btni.click() && !Btnm.click() && !Btna.click() && !Btnp.click()) {
    tiempo = millis() + SM;
    if (c <= 24 || c >= 30) {
      c = 24;
    }
    c++;
  }

  // Imprime las letras
  if (millis() > tiempo && c > 0) {
    char letra = Letras[c];
    Keyboard.print(letra);w
   // Serial.print(letra);// Enviar la letra por Bluetooth
    c = 0;
  }
}
