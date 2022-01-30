/* ========================================
 *
 *Starblaster program for Microcontroller
 *System Design CPE 3280
 *Written by Cypress Payne
 *
 * ========================================
*/
#include "project.h"
#include <stdlib.h>
#include <stdio.h>

int TARGETX;
int TARGETY;

//declaration of functions
void drawStars(int arr[200][2]);
void remStars(int arr[200][2]);
void drawTarget(int x, int y);
void remTarget(int x, int y);
void drawBlast(int x, int y);
void drawSuperBlast(int x, int y);
void starTwinkle(int arr[200][2]);
void starScroll(int arr[200][2], int dir);

int main(){
//intialize screen
    GLCD_Start();
    GLCD_Clear(GLCD_BLACK);
    Backlight_Write(1);
    LED_Blue_Write(1); LED_Green_Write(0); LED_Red_Write(1);

// generate stars
      int sky[200][2];
      int starNum = 100 + rand()%100;
      int16 i;
      for(i = 0; i < starNum; i++){
        int starX = rand()%131;
        int starY = rand()%131;
        sky[i][0] = starX;
        sky[i][1] = starY;
        GLCD_Pixel(starX, starY, GLCD_WHITE);
       }
//generate target
        TARGETX = 63;
        TARGETY = 63;
        drawTarget(TARGETX,TARGETY);

    int32 counter = 0;
//infinite loop
    for(;;)
    {
        starTwinkle(sky);

//check time for blast
         if (counter%10 == 0){
           if(LED_Green_Read() == 0){
            LED_Green_Write(1);
            LED_Blue_Write(0);
         }
           if(LED_Red_Read() == 0){
            LED_Red_Write(1);
            LED_Green_Write(0);
        }
        }
//check if buttons are pressed
        while(PinA_Read() == 0) {
           if(TARGETX > 15){
            remTarget(TARGETX,TARGETY);
            TARGETX -= 1;
            drawTarget(TARGETX,TARGETY);
            }
            else{starScroll(sky,0);}
        }
        while(PinB_Read() == 0) {
           if(TARGETY < 120){
            remTarget(TARGETX,TARGETY);
            TARGETY += 1;
            drawTarget(TARGETX,TARGETY);
            }
            else {starScroll(sky,1);}
        }
        while(PinC_Read() == 0) {
           if (TARGETX < 120){
            remTarget(TARGETX,TARGETY);
            TARGETX += 1;
            drawTarget(TARGETX,TARGETY);
            }
            else{starScroll(sky,2);}
        }
        while(PinD_Read() == 0) {
           if(TARGETY > 15){
            remTarget(TARGETX,TARGETY);
            TARGETY -= 1;
            drawTarget(TARGETX,TARGETY);
            }
            else{starScroll(sky,3);}
        }

        while(PinCenter_Read() == 0) {
            if(LED_Green_Read() == 0){
                drawBlast(TARGETX,TARGETY);
                drawStars(sky);
                drawTarget(TARGETX,TARGETY);
                LED_Green_Write(1);
                LED_Red_Write(0);

            }
            if (LED_Blue_Read() == 0) {
                drawSuperBlast(TARGETX,TARGETY);
                drawStars(sky);
                drawTarget(TARGETX,TARGETY);
                LED_Blue_Write(1);
                LED_Red_Write(0);
            }
        }
        counter++;
    }
}

/*function definitions*/

//draws stars for background
void drawStars(int arr[200][2]){
   for(int i = 0; i < 200; i++){
        int x,y;
        x = arr[i][0];
        y = arr[i][1];
        GLCD_Pixel(x, y, GLCD_WHITE);
            }
}

//removes stars in background leaving black sky
void remStars(int arr[200][2]){
    for(int i = 0; i < 200; i++){
        int x,y;
        x = arr[i][0];
        y = arr[i][1];
        GLCD_Pixel(x, y, GLCD_BLACK);
    }
}

//draws target
void drawTarget(int x, int y){
    GLCD_DrawCircle(x, y,5,GLCD_YELLOW);
    GLCD_DrawLine(x,y-10,x,y+10,GLCD_YELLOW);
    GLCD_DrawLine(x-10,y,x+10,y,GLCD_YELLOW);
}

//removes target
void remTarget(int x, int y){
    GLCD_DrawCircle(x, y,5,GLCD_BLACK);
    GLCD_DrawLine(x,y-10,x,y+10,GLCD_BLACK);
    GLCD_DrawLine(x-10,y,x+10,y,GLCD_BLACK);
}

//draws blast
void drawBlast(int x, int y){
    int rad;
        for(rad = 0; rad < 20; rad++){
            CyDelay(15);
            GLCD_DrawCircle(x,y,rad,GLCD_GREEN);
            }
        for(rad = 0; rad < 20; rad++){
            CyDelay(15);
            GLCD_DrawCircle(x,y,rad,GLCD_BLACK);
            }
}

//draws superblast for when blast has charged
void drawSuperBlast(int x, int y){
int rad;
        for(rad = 0; rad < 20; rad++){
            CyDelay(15);
            GLCD_DrawCircle(x,y,rad,GLCD_GREEN);
            }
        for(rad = 20; rad < 30; rad++){
            CyDelay(15);
            GLCD_DrawCircle(x,y,rad,GLCD_BLUE);
        }
        for(rad = 0; rad < 30; rad++){
            CyDelay(15);
            GLCD_DrawCircle(x,y,rad,GLCD_BLACK);
            }
}

//makes stars twinkle
void starTwinkle(int arr[200][2]){
      int16 i;
      for(i = 0; i < 10; i++){
        int x, y, randi;
        randi = rand()%200;
        x = arr[randi][0];
        y = arr[randi][1];
        GLCD_Pixel(x, y, GLCD_BLACK);
        CyDelay(100);
        GLCD_Pixel(x, y, GLCD_WHITE);
        i++;
    }
}

//allows for scrolling in all directions
void starScroll(int arr[200][2], int dir){
    remStars(arr);
    if (dir == 0){
        for(int i = 0; i < 200; i++){
            int curX = arr[i][0];
            if (curX == 131){
                arr[i][0] = 0;
            }
            else{arr[i][0] += 1;}
        }
        drawStars(arr);
        drawTarget(TARGETX,TARGETY);

    }
    else if (dir == 1){
        for(int i = 0; i < 200; i++){
            int curX = arr[i][1];
            if (curX == 0){
                arr[i][1] = 131;
            }
            else{arr[i][1] -= 1;}
        }
        drawStars(arr);
        drawTarget(TARGETX,TARGETY);

    }
    else if (dir == 2){
        for(int i = 0; i < 200; i++){
            int curX = arr[i][0];
            if (curX == 0){
                arr[i][0] = 131;
            }
            else{arr[i][0] -= 1;}
        }
        drawStars(arr);
        drawTarget(TARGETX,TARGETY);

    }
    else if (dir == 3){
        for(int i = 0; i < 200; i++){
            int curX = arr[i][1];
            if (curX == 131){
                arr[i][1] = 0;
            }
            else{arr[i][1] += 1;}
        }
        drawStars(arr);
        drawTarget(TARGETX,TARGETY);

    }
}

/* [] END OF FILE */
