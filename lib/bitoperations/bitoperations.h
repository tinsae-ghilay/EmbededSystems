//
// Created by tgk on 5/24/24.
//

#ifndef BITOPERATIONS_H
#define BITOPERATIONS_H

// setzt das Bit (d.h. das Bit nimmt den Wert 1 an) an der Stelle POSITION.
#define SB(VALUE,POSITION)   (VALUE |=  1<<POSITION)
// löscht das Bit (d.h. das Bit nimmt den Wert 0 an) an der Stelle POSITION.
#define CB(VALUE,POSITION)  (VALUE &= ~1<<POSITION)

//  "toggelt" (hin- und herschalten) das Bit an der Stelle POSITION.
#define TB(VALUE,POSITION)   (VALUE ^=  1<<(POSITION))

// prüft, ob das bit an der Stelle POSITION gesetzt ist (d.h. ob es den Wert 1 hat).
#define IBS(VALUE,POSITION)  ((VALUE &  1<<(POSITION)) == 1)

// testing bit oprations 
inline void testBitOperation(){
  Serial.print( "-- TESTING BIT WEIS OPERATIONS __ \n");
    auto set = 0b0000000000000000; // 16 bit binary
    Serial.print("original Binary : ");
    Serial.println(set,BIN),
    Serial.print("Binary after SB(VALUE,3) : ");
    Serial.println(SB(set,3),BIN);
    Serial.print("Binary after SB(VALUE,2): ");
    Serial.println(SB(set,2),BIN);
    Serial.print("Binary after CB(VALUE,2) : ");
    Serial.println(CB(set,2),BIN);
    Serial.print("Binary after TB(VALUE,0) : ");
    Serial.println(TB(set,0),BIN);
    Serial.print("Binary after SB(VALUE,1) : ");
    Serial.println(SB(set,5),BIN);
    Serial.print("Checking Binary using IBS(VALUE,0) : ");
    Serial.println(IBS(set,0),BIN);
    Serial.print("Checking Binary using IBS(VALUE,2) : ");
    Serial.println(IBS(set,2),BIN);
};
#endif //BITOPERATIONS_H
