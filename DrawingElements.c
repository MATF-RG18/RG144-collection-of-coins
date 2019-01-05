#include <GL/glut.h>
#include "DrawingElements.h"
#include <math.h>
#include "Global.h"
#include <stdio.h>

#define PI 3.14159265359
#define NUMBER_OF_DOTS 100

// iscrtavanje lopte
void create_sphera(void){
  glPushMatrix();
    glutSolidSphere(0.115,15,15);
  glPopMatrix();
}


// iscrtavanje staze
void create_track(void){
    int i;
    for(i=1; i<1020; i++) {
    if(i == 1018 || i == 1019) {
      int j;
      for(j=0; j<=6; j++) {
	if(i==1018){
	  if(j % 2 == 0){
	    glColor3d(0,0,0);
	  }
	  else{
	    glColor3d(1,1,1);
	  }
	}
	else{
	  if(j % 2 == 0){
	    glColor3d(1,1,1);
	  }
	  else{
	    glColor3d(0,0,0);
	  }  
	}	
	glBegin(GL_POLYGON);
	  glVertex3d(0.7-j*0.2,0,-1+(0.2*(i-1)));
	  glVertex3d(0.7-j*0.2,0,-1+(0.2*i));
	  glVertex3d(0.7-(0.2*(j+1)),0,-1+(0.2*i));
	  glVertex3d(0.7-(0.2*(j+1)),0,-1+(0.2*(i-1)));
	glEnd();
      }
    }
    
    else{
      switch (i%2) {
	case 0:
	  glColor3d(0.2,0.2,0.2);
	  break;
	case 1:
	  glColor3d(1,0,0);
	  break;
      }
      glBegin(GL_POLYGON);
	glVertex3d(0.7,0,-1+(0.2*(i-1)));
	glVertex3d(0.7,0,-1+(0.2*i));
	glVertex3d(-0.7,0,-1+(0.2*i));
	glVertex3d(-0.7,0,-1+(0.2*(i-1)));
      glEnd();
    }
  }
}


// isrtavanje rupa
void create_hole(void) {
  int i;
  float x;
  for(i=1; i<1000; i=i+6) {
    // -0.7 do 0.7 ide x a sirina rupe je 0.3
    if(niz_random[i] % 2 != 0){
      x = -niz_random[i] * 0.1;
      check_hole(x,x-0.3,i*0.2+0.4,i*0.2);
    }
    else{
      x = niz_random[i] * 0.1;
      check_hole(x,x-0.3,i*0.2+0.4,i*0.2);
    }
    
    if(x>-0.7 && x<0.7 && (x-0.3)>-0.7 && (x-0.3)<0.7) {
     glColor3d(0,0,1);
     glBegin(GL_POLYGON);
        glVertex3f(x,0.0001,i*0.2+0.4);
        glVertex3f(x,0.0001,i*0.2);
        glVertex3f(x-0.3,0.0001,i*0.2);
        glVertex3f(x-0.3,0.0001,i*0.2+0.4);
     glEnd();   
    }
  }
}


// iscrtavanje strelica za ubrzanje
void up_speed(void){
  int i;
  float x;
  for(i=0; i<1000; i=i+6) {
    if(niz_random[i] % 2 != 0){
      x = -niz_random[i] * 0.1;
      check_hole2(x,x-0.3,i*0.2-0.2,i*0.2+0.2); 
    }
    else{
      x = niz_random[i] *0.1;
      check_hole2(x,x-0.3,i*0.2-0.2,i*0.2+0.2);
    }
    
    if(x>-0.7 && x<0.7 && (x-0.3)>-0.7 && (x-0.3)<0.7) {
        glColor3d(0,1,0);
        glBegin(GL_POLYGON);
            glVertex3f(x,0.0002,i*0.2);
            glVertex3f(x-0.3,0.0002,i*0.2);
            glVertex3f((x+x-0.3)/2,0.0002,i*0.2+0.2);
        glEnd();
        
        glColor3d(1,1,1);
        glBegin(GL_POLYGON);
            glVertex3f(x,0.0003,i*0.2-0.1);
            glVertex3f(x-0.3,0.0003,i*0.2-0.1);
            glVertex3f((x+x-0.3)/2,0.0003,i*0.2+0.2-0.1);
        glEnd();
        
        glColor3d(0,1,0);
        glBegin(GL_POLYGON);
            glVertex3f(x,0.0004,i*0.2-0.2);
            glVertex3f(x-0.3,0.0004,i*0.2-0.2);
            glVertex3f((x+x-0.3)/2,0.0004,i*0.2+0.2-0.2);
        glEnd();
    }
  }     
}

// iscrtavanje novcica
void create_coin(void){

   int j = 0;
   float translate_z_coin = 0;
   
   for(i=0; i<100; i=i+4) {
       
        glPushMatrix();
            glTranslatef(niz_random_coin[j], 0.115, translate_z_coin);
            glRotatef(-90,1,0,0);
            glRotatef(rotation_speed,0,0,1);
            // donja baza valjka
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0,0,1);
            glVertex2f(0,0);
            for(int i=0; i<=NUMBER_OF_DOTS; i++) {
                glVertex3f(cos(2*i*PI/NUMBER_OF_DOTS)*0.115,
                            0,
                            sin(2*i*PI/NUMBER_OF_DOTS)*0.115
                );
            }
            glEnd();
                
            // omotac valjka
            glColor3f(1,1,0);
            glBegin(GL_QUAD_STRIP);
            for(int i=0; i<= NUMBER_OF_DOTS; i++) {
                    glVertex3f(cos(2*i*PI/NUMBER_OF_DOTS)*0.115,
                            0,
                            sin(2*i*PI/NUMBER_OF_DOTS)*0.115);
                    glVertex3f(cos(2*i*PI/NUMBER_OF_DOTS)*0.115,
                            0.06,
                            sin(2*i*PI/NUMBER_OF_DOTS)*0.115);
            }
            glEnd();
                
            // gornja baza valjka
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0,0,1);
            glVertex2f(0,0);
            for(int i=0; i<= NUMBER_OF_DOTS; i++) {
                    glVertex3f(cos(2*i*PI/NUMBER_OF_DOTS)*0.115,
                            0.06,
                            sin(2*i*PI/NUMBER_OF_DOTS)*0.115);
            }
            glEnd();
        glPopMatrix();
            
        translate_z_coin += niz_random[i];
        j++;
   }
}


// iscrtavanje desnog zida
void rigth_wall(void){
  for( i=1;i<1020; i++) {
    switch (i%2) {
      case 0:
        glColor3d(1,0,0);
        break;
      case 1:
        glColor3d(0.2,0.2,0.2);
        break;
    }
    
    glBegin(GL_POLYGON);
      glVertex3d(-0.7,1.4,-1+(0.2*(i-1)));
      glVertex3d(-0.7,1.4,-1+(0.2*i));
      glVertex3d(-0.7,0,-1+(0.2*i));
      glVertex3d(-0.7,0,-1+(0.2*(i-1)));
    glEnd();
  }
}

// iscrtavanje levog zida
void left_wall(void){
  for( i=1;i<1020; i++) {
    switch (i%2) {
      case 0:
        glColor3d(1,0,0);
        break;
      case 1:
        glColor3d(0.2,0.2,0.2);
        break;
    }
    
    glBegin(GL_POLYGON);
      glVertex3d(0.7,1.4,-1+(0.2*(i-1)));
      glVertex3d(0.7,1.4,-1+(0.2*i));
      glVertex3d(0.7,0,-1+(0.2*i));
      glVertex3d(0.7,0,-1+(0.2*(i-1)));
    glEnd();
  }
}


// provera upadanja u rupu
void check_hole(float xl,float xd,float zg,float zd){
     if((x_ball <= (xl-0.05)) && (x_ball >= (xd+0.05)) && 
         (zg >= z_ball-z_1) && (zd+0.2 <= z_ball-z_1) && (y_ball < 0.116)) {
         y_ball -= 0.01;
     
     }
}

// provera za ubrzanje
void check_hole2(float xl,float xd,float zd,float zg){
    if((x_ball <= xl) && (x_ball >= xd) && 
         (zg >= z_ball-z_1) && (zd+0.2 <= z_ball-z_1) && (y_ball < 0.116)){
        
        z_2 = 0.2;
    }
}