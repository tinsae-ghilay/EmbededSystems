//
// Created by tgk on 5/24/24.
//

#ifndef BITOPERATIONS_H
#define BITOPERATIONS_H

// setzt das Bit (d.h. das Bit nimmt den Wert 1 an) an der Stelle POSITION.
#define SB(VALUE,POSITION)   ((VALUE) |=  (1<<(POSITION)))
// löscht das Bit (d.h. das Bit nimmt den Wert 0 an) an der Stelle POSITION.
#define CB(VALUE,POSITION)  ((VALUE) &= ~(1<<(POSITION)))

//  "toggelt" (hin- und herschalten) das Bit an der Stelle POSITION.
#define TB(VALUE,POSITION)   ((VALUE) ^=  (1<<(POSITION)))

// prüft, ob das bit an der Stelle POSITION gesetzt ist (d.h. ob es den Wert 1 hat).
#define IBS(VALUE,POSITION)  ((VALUE) &  (1<<(POSITION)))
#endif //BITOPERATIONS_H
