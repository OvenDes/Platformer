// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/31/2023

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz




void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

//uint32_t turn=1; //1 is red and -1 is yellow
//uint32_t checkturn;
uint32_t SFlag;
uint32_t BFlag;
uint32_t grump=0;

struct character{
    uint32_t x;
    uint32_t y;
    int32_t vy;
    uint32_t x1;
    uint32_t y1;
    //status_t life;

};
    typedef struct character character_t;


 struct rect{

        uint32_t x;
        uint32_t y;
        int vy;
        uint32_t x1;
        uint32_t y1;
    };
 typedef struct rect rect_t;



 rect_t barrier[10]= {
                     {24,25, 0,0,0}, //0
                     {45,55, 0,0,0}, //1
                     {56,85, 0,0,0},  //2
                     {21,115, 0,0,0},  //3
                     {33,145, 0,0,0},  //4
                     {33,175, 0,0,0},  //5
                     {33,205, 0,0,0},  //6
                     {33,235, 0,0,0},  //7
                     {33,265, 0,0,0},  //8
                     {33,295, 0,0,0},  //9
                     //{60,25, 0,0,0}
 };

// int32_t bs= 295;
//int32_t ch= 1000;
 int turn=1;
uint32_t bad=0;
 rect_t regen= { 24, 130, -1,0, 0};

 rect_t regen1= { 35, 150, -1, 0, 0};
    character_t coin1 = {5, 15,0, 40, 15};



        struct scoreboard{
            uint32_t redscore;
            uint32_t yellscore;

        };
            typedef struct scoreboard scoreboard_t;

            scoreboard_t finalscore = {0, 0};

uint32_t next=0;
void TIMG12_IRQHandler(void){
   if((TIMG12->CPU_INT.IIDX) == 1){
       GPIOB->DOUTTGL31_0 = RED; // toggle PB27 (minimally intrusive debugging)
       GPIOB->DOUTTGL31_0 = RED; // toggle PB27 (minimally intrusive debugging)
       uint32_t in= Switch_In();

       SFlag=1;
       if(in==1 && grump==1){
                 //coin1.y= 30;
           coin1.y1= coin1.y;
           coin1.y += 35;
                 coin1.vy= -1;
                 next++;

                 //coin1.x1= coin1.x;
             }
             //uint32_t column;

       int barrierHit = 0;
             uint32_t slidepot= ADCin();

             uint32_t convert1 = (120* slidepot)/4095;
             coin1.x1= coin1.x;
             coin1.x= convert1;

             coin1.y += coin1.vy;
             int32_t temp= coin1.y;

for(int i=0; i<10; i++){
    barrier[i].y1= barrier[i].y;
                barrier[i].y += barrier[i].vy;

}


             static uint32_t get=0;
for(int j=0; j<10; j++){
    if(coin1.x> (barrier[j].x -10) && coin1.x< (barrier[j].x +26) ){

                   if(coin1.y >= (barrier[j].y + 15) && coin1.y<= (barrier[j].y +20)){
                       coin1.y= barrier[j].y+15;
                      coin1.vy= -1;
                       //coin1.vy= 0;
                      for(int k=0;k<10;k++){
                          //Clock_Delay1ms(1);

                         barrier[k].vy= -1;
                      }

                       get++;
                       barrierHit = 1;
                   }

               }





    if (!barrierHit) {
        coin1.vy = -2;
    }


}



//nt ab= barrier[4].y;
//static int ab=1;
static int bs=0;
bs = barrier[9].y;
static int ch=0;
ch= barrier[4].y;

   if(  turn==1 ){




        if(bs<110){
            BFlag=1;
            turn=-1;
            barrier[0].y= 130;
                   barrier[1].y=155;
                   barrier[2].y= 180;
                   barrier[3].y= 200;
                   barrier[4].y= 225;



        }


    }else if (ch<130){
        BFlag=1;
        turn=1;
                   barrier[5].y= 150;
                                          barrier[6].y= 170;
                                          barrier[7].y= 190;
                                          barrier[8].y= 205;
                                          barrier[9].y= 220;

                                          //ch=1000;
                 // bs= barrier[9].y;
                  for(int k=5;k<10;k++){
                                                                      barrier[k].vy = -1;
                                                       }
    }





   if(temp < 15){
                  coin1.y=15;
                  coin1.vy=0;
              }
   }
   if(coin1.y==15 && next!=0){
       bad++;
   }

   GPIOB->DOUTTGL31_0 = RED; // toggle PB27 (minimally intrusive debugging)
   }




// games  engine runs at 30Hz
/*void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot

      uint32_t column;
       uint32_t convert;
        uint32_t slidepot_sample= ADCin();

        convert= (120* slidepot_sample)/4095;

        //while moving slide-pot move coin sprite
        if(turn==1){

            coin1.column1= convert;
            SFlag=1;
        }else if(turn==-1){


            coin2.column2= convert;
            SFlag=1;
        }else{
            coin1.bevo= convert;
            EFlag=1;
        }

    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)

  }
}

*/
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
 int main(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_WHITE);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
 TimerG12_IntArm(80000000/30,2);
  //TimerG6_IntArm(80000000/30,2,3);
  SFlag=0;
  BFlag=0;

  // initialize all data structures
  __enable_irq();

  while(1){
          //Sound_background();

        //beginning screen for the game


         // reset the game board


         ST7735_FillScreen(ST7735_BLACK);            // set screen to black
                  ST7735_SetCursor(1, 1);
                  ST7735_SetTextColor(ST7735_GREEN);
                  ST7735_OutString("Platformer");
                  ST7735_SetCursor(1, 3);
                  ST7735_SetTextColor(ST7735_GREEN);
                  ST7735_SetCursor(1, 7);
                  ST7735_OutString("Press button 1");
                  ST7735_SetTextColor(ST7735_GREEN);
                  ST7735_SetCursor(1, 8);
                  ST7735_OutString("to start game");

                  int tester = Switch_In();

                  while(tester==0){

                      tester = Switch_In();
                      if(tester !=0){
                          break;
                          Clock_Delay1ms(100);
                      }

                  }

                  for(int y=0; y<10; y++){

                      barrier[y].x= Random(110);
                  }

                  uint32_t job=0;
                  ST7735_FillScreen(ST7735_WHITE);
                  while(tester==1){
                      //coin1.vy= -1;
                      grump=1;


                      if(SFlag==1){
                       SFlag=0;
                      ST7735_DrawBitmap(coin1.x1, coin1.y1, blanksq,20 , 20);
                       //Clock_Delay1ms(100);
                      ST7735_DrawBitmap(coin1.x, coin1.y, square3,15 , 15);



                      for(int k=0; k<10; k++){
                            ST7735_DrawBitmap(barrier[k].x, barrier[k].y1, blanksq,30 , 5);
                            ST7735_DrawBitmap(barrier[k].x, barrier[k].y, grect1,30,5 );

                        }//stuff that works

                    //
                      if(BFlag==1){
                          BFlag=0;

                         // tester=2;
                      }
                      //tester=2;




                     }
                      if(bad==1){
                          break;
                      }

                  }

                      ST7735_FillScreen(ST7735_BLACK);            // set screen to black
                                                         ST7735_SetCursor(1, 1);
                                                         ST7735_SetTextColor(ST7735_GREEN);
                                                         ST7735_OutString("Game Over");

  while(1){}




/*while(tester==2){

    if(BFlag==1){
       BFlag=0;


          for(int index=0;index<10; index++ ){
              ST7735_DrawBitmap(barrier[index].x, barrier[index].y1, blanksq,30 , 5);
              ST7735_DrawBitmap(barrier[index].x, barrier[index].y, grect1,30,5 );



                                   }

          if(SFlag==1){
                                 SFlag=0;
                                ST7735_DrawBitmap(coin1.x1, coin1.y1, blanksq,20 , 20);
                                 //Clock_Delay1ms(100);
                                ST7735_DrawBitmap(coin1.x, coin1.y, square3,15 , 15);
          }


    }
}

*/


  }
}
