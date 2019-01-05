#include <GL/glut.h>
#include "Print.h"
#include <stdio.h>
#include <string.h>
#include "Global.h"

// ispis kad upadne u rupu
void game_over(void){

    char ispis[20];
    sprintf(ispis, "Game over");

    glPushMatrix();
        glColor3d(1,1,0);
        glRasterPos3f(0.2,0.1,2);
        int len = strlen(ispis);
        for(int i =0; i<len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis[i]);
        }
    glPopMatrix();
}


// ispis kad dodje do cilja
void finish(void) {
    
    if(202.6 <= z_ball - z_1){
        char ispis1[8];
        char ispis2[8];
        char ispis3[8];
        char ispis4[8];
        sprintf(ispis1, "Happy");
        sprintf(ispis2, "New");
        sprintf(ispis3, "Year");
        sprintf(ispis4, "2019");
        
        glPushMatrix();
            glColor3d(1,0,0);
            glRasterPos3f(0.5,0,2);
            int len1 = strlen(ispis1);
            for(int i =0; i<len1; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis1[i]);
            }
            
            glColor3d(0,1,0);
            glRasterPos3f(0,0,2);
            int len2 = strlen(ispis2);
            for(int i =0; i<len2; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis2[i]);
            }
            
            glColor3d(0,0,1);
            glRasterPos3f(-0.4,0,2);
            int len3 = strlen(ispis3);
            for(int i =0; i<len3; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis3[i]);
            }
            
            glColor3d(1,1,0);
            glRasterPos3f(0,0,1.5);
            int len4 = strlen(ispis4);
            for(int i =0; i<len4; i++) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis4[i]);
            }
        glPopMatrix();
        animation_ongoing = 0;
    }
}