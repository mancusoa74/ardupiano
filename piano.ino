#include <CapacitiveSensor.h>

//definizione Note
#define NOTA_C4  262
#define NOTA_D4  294
#define NOTA_E4  330
#define NOTA_F4  349
#define NOTA_G4  392
#define NOTA_A4  440
#define NOTA_B4  494

#define BUZZER_PIN 13
#define DURATA_NOTA 250
#define PAUSA (DURATA_NOTA * 1.3)

long valore_tasti[7] = {0, 0, 0, 0, 0, 0, 0};
int note[7] = {NOTA_C4, NOTA_D4, NOTA_E4, NOTA_F4, NOTA_G4, NOTA_A4, NOTA_B4};

//inizializza i tasti capacitivi
CapacitiveSensor tasti[7] = {
                            CapacitiveSensor(4,5),
                            CapacitiveSensor(4,6),
                            CapacitiveSensor(4,7),
                            CapacitiveSensor(8,9),
                            CapacitiveSensor(8,10),
                            CapacitiveSensor(8,11),
                            CapacitiveSensor(8,12)                        
};



void play_nota(int nota){
    tone(BUZZER_PIN, nota, DURATA_NOTA);
    delay(PAUSA);
    noTone(BUZZER_PIN);
}

void setup(){
    pinMode(13,OUTPUT);
    digitalWrite(13, LOW);

    Serial.begin(115200);
    for (int i = 0; i < 7; i++) {
       tasti[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
    }
}


void loop(){
    
    for (int i = 0; i < 7; i++) {
      valore_tasti[i] = tasti[i].capacitiveSensor(50);
      Serial.println(valore_tasti[i]);
    }
    Serial.println("----------");
        
    for (int i = 0; i < 7; i++) {
      if (valore_tasti[i] > 1500) {        
        play_nota(note[i]);
      } 
      valore_tasti[i] = 0;
    }
    delay(20);
}


