/* 
 * File:board.h
 * Author: yiming
 * Comments:lamp active
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOARD_H
#define	BOARD_H

#include <xc.h> // include processor files - each processor file is guarded.  

extern void dataSetLed(uint8_t* tempRxData);
extern void feedbacksignal(uint8_t *tempRxData);

extern void board_init(void);
extern void board_updata(void);



#endif	/* BOARD_H */

