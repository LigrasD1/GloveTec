
class Pulsador {
  private:
    bool estado;
    int  rebotes;
    int  pulsador;
    unsigned long espera;
	
  public:
    Pulsador(int pin, int rbt = 50) {
      pulsador = pin;
      estado = false;
      espera = 0;
      rebotes = rbt;
      pinMode(pulsador, INPUT_PULLUP);
    }
    
    bool click() {
      if(espera > millis()) return false;
      if(digitalRead(pulsador) == estado) {
        espera = millis() + rebotes;
        estado = !estado;
        return estado;
      }
      return false;
    }
};
