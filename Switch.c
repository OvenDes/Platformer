/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    // write this
    IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00040081;    //input PB16
    IOMUX->SECCFG.PINCM[PB17INDEX] = 0x00040081;    //input PB17


      /* IOMUX->SECCFG.PINCM[PB2INDEX] = 0x00000081; // output PB2: Red South
       GPIOB->DOE31_0 |= 0x04; // enable
       IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00000081; // output PB1: yellow South
       GPIOB->DOE31_0 |= 0x02; // enable
       IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00000081; // output PB0: green South
       GPIOB->DOE31_0 |= 0x01; // enable

       IOMUX->SECCFG.PINCM[PB8INDEX] = 0x00000081; // output PB8: Red West
       GPIOB->DOE31_0 |= 0x100; // enable
       IOMUX->SECCFG.PINCM[PB7INDEX] = 0x00000081; // output PB7: Yellow West
       GPIOB->DOE31_0 |= 0x80; // enable
       IOMUX->SECCFG.PINCM[PB6INDEX] = 0x00000081; // output PB6: Green West
       GPIOB->DOE31_0 |= 0x40; // enable
  */
}
// return current state of switches
uint32_t Switch_In(void){
    // write
    uint32_t input=0;
    uint32_t mask=0x30000;
    input= GPIOB->DIN31_0 & mask;

    bool next=false;
    input= input>>16;

    uint32_t switc=0;

    static uint32_t last=0;

    if((input != 0)&&(last == 0)){
    // just touched, runs once per touch
       // next=true;
        switc= input;

    }
    last = input;





  return switc; //replace this your code

 //   return input;
}
