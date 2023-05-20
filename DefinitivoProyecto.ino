#include <LiquidCrystal_I2C.h>
#include <Buzzer.h>
#include <Wire.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
LiquidCrystal_I2C lcd(0x27,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
#define ANALOGPIN     A0
#define ENABLEPIN     7

#include <ML8511.h>
ML8511 light(ANALOGPIN, ENABLEPIN);

Buzzer buzzer(11, 13);

int segundos;
int minutos;
bool FTemp;
unsigned long duracion;
unsigned long tiempoInicio;


void setup() {
  
  Serial.begin(9600);
  FTemp = false;

  lcd.init();
  lcd.backlight();

  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");

  // manually enable / disable the sensor.
  light.enable();
  light.setDUVfactor(1.5);    // calibrate your sensor

  Serial.print("\tmW cm^2");
  Serial.print("\tDUV index");
  Serial.println();


}

void loop() {

  float UV = light.getUV();
  float DUV = light.estimateDUVindex(UV);

  Serial.print(UV, 4);
  Serial.print("\t");
  Serial.print(DUV, 1);
  Serial.println();

  if(DUV<3){
    Baja(DUV,UV);
  }

  if(DUV>3){
    tiempoInicio = millis();
    while (true) {
    // Calcular el tiempo transcurrido desde el inicio
    unsigned long tiempoActual = millis();
    unsigned long tiempoTranscurrido = tiempoActual - tiempoInicio;
      while(DUV>=3 && DUV<6){
        Media(DUV,tiempoTranscurrido,UV);
      }
      while(DUV>=6 && DUV<8){
        Alta(DUV,tiempoTranscurrido,UV);
      }
      while(DUV>=8 && DUV<11){
        muyAlta(DUV,tiempoTranscurrido,UV);
      }
      while(DUV>=11){
        Extrema(DUV,tiempoTranscurrido,UV);
      }
    }
  }

}

float Baja(float DUV, float UV) {
  
  lcd.setCursor (0,0);
  lcd.print(DUV,1);
  lcd.setCursor(6, 0);
  lcd.print("DUV IND");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("No es peligroso, disfruta!");
  for(int i = 0; i<11; i++){
    lcd.scrollDisplayLeft();
    delay(350);
  }
  lcd.clear();
}


float Media(float DUV, unsigned long tiempoTranscurrido,float UV) {
  
  lcd.setCursor (0,0);
  lcd.print(DUV,1);
  lcd.setCursor(6, 0);
  lcd.print("DUV IND");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Ten cuidado, aplicate bloqueador");
  for(int i = 0; i<16; i++){
    lcd.scrollDisplayLeft();
    delay(350);
  }
  lcd.clear();
  while(DUV>=3 && DUV<=3.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(0,10);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=4 && DUV<=4.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(0,10);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=5 && DUV<=5.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(0,10);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("    estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
}


float Alta(float DUV, unsigned long tiempoTranscurrido,float UV) {
  
  lcd.setCursor (0,0);
  lcd.print(DUV,1);
  lcd.setCursor(6, 0);
  lcd.print("DUV IND");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Ten cuidado, aplicate bloqueador");
  for(int i = 0; i<16; i++){
    lcd.scrollDisplayLeft();
    delay(350);
  }
  lcd.clear();
  while(DUV>=6 && DUV<=6.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(29,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("    estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=7 && DUV<=7.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(25,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
}


float muyAlta(float DUV, unsigned long tiempoTranscurrido,float UV) {
  
  lcd.setCursor (0,0);
  lcd.print(DUV,1);
  lcd.setCursor(6, 0);
  lcd.print("DUV IND");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Es muy peligroso, aplicate bloqueador");
  for(int i = 0; i<21; i++){
    lcd.scrollDisplayLeft();
    delay(350);
  }
  lcd.clear();
  while(DUV>=8 && DUV<=8.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(22,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=9 && DUV<=9.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(19,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=10 && DUV<=10.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(18,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
}


float Extrema(float DUV, unsigned long tiempoTranscurrido,float UV) {
  
  lcd.setCursor (0,0);
  lcd.print(DUV,1);
  lcd.setCursor(6, 0);
  lcd.print("DUV IND");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Es muy peligroso, procura no exponerte");
  for(int i = 0; i<22; i++){
    lcd.scrollDisplayLeft();
    delay(350);
  }
  lcd.clear();
  while(DUV>=11 && DUV<=12.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(15,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=12 && DUV<=13.99){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(13,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
  while(DUV>=14){
    float UV = light.getUV();
    float DUV = light.estimateDUVindex(UV);
    duracion = calcularDuracion(12,0);
    if (tiempoTranscurrido >= duracion) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Llevas mucho tiempo bajo el sol");
      lcd.setCursor(0,1);
      lcd.print("      estas sobreexpuesto");
      for(int i = 0; i<15; i++){
        lcd.scrollDisplayLeft();
        delay(350);
      }
      repAlarm();
      lcd.clear();
      tiempoInicio = millis();
    }
  }
}

unsigned long calcularDuracion(int min, int seg) {
  return (min * 60 + seg)*1000;
}

void repAlarm(){
  for(int i=0; i<1; i++){
    
  buzzer.begin(10);
  buzzer.sound(NOTE_A3, 500); 
  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.sound(NOTE_E4, 500); 
  buzzer.sound(NOTE_E4, 500);
  buzzer.sound(NOTE_E4, 500);
  buzzer.sound(NOTE_F4, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_A3, 125);
  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_GS4, 375);
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_FS4, 125);
  buzzer.sound(NOTE_E4, 125);
  buzzer.sound(NOTE_F4, 250);
  buzzer.end(250);
  buzzer.sound(NOTE_AS3, 250);
  buzzer.sound(NOTE_DS4, 500);
  buzzer.sound(NOTE_D4, 375);
  buzzer.sound(NOTE_CS4, 125);

  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_B3, 125);
  buzzer.sound(NOTE_C4, 250);
  buzzer.end(250);
  buzzer.sound(NOTE_F3, 250);
  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_A3, 125);

  buzzer.sound(NOTE_C4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_E4, 1000);

  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_A3, 125);
  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_GS4, 375);
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_FS4, 125);
  buzzer.sound(NOTE_E4, 125);
  buzzer.sound(NOTE_F4, 250);
  buzzer.end(250);
  buzzer.sound(NOTE_AS3, 250);
  buzzer.sound(NOTE_DS4, 500);
  buzzer.sound(NOTE_D4, 375);
  buzzer.sound(NOTE_CS4, 125);

  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_B3, 125);
  buzzer.sound(NOTE_C4, 250);
  buzzer.end(250);
  buzzer.sound(NOTE_F3, 250);
  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.end(2000);
  }
}
