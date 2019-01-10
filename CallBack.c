#include <GL/glut.h>
#include <stdbool.h>
#include "Global.h"
#include "CallBack.h"
#include "DrawingElements.h"
#include "Print.h"

// postavljanje inicijalnih vrednosti
void initialize(void){
  glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glEnable(GL_DEPTH_TEST);
}

// ukljucivanje tastature
void on_keyboard(unsigned char key, int x, int y){
  
    switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'g':
      if(!animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_1, TIMER_ID);
        animation_ongoing = 1;
      }
      break;
    case 's':
      animation_ongoing = 0;
      break;
    case 32:
        jump = 1;
        break;
  }
}

// ukljucivanje specijalnih tastera(strelice)
void specialKeys(int key, int x, int y){
  
    switch (key) {
    case GLUT_KEY_LEFT:
      lm = 1;
      rm = 0;
      break;
    case GLUT_KEY_RIGHT:
      rm = 1;
      lm = 0;
      break;
  }  
}

void on_reshape(int width, int height){
 
  width_window = width;
  height_window =  height;

  glViewport(0,0,width_window,height_window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(53,width_window/(float)height_window,1, 15);

}

void on_display(void){
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // postavljanje pogleda i kamere
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-0.6,0,0,1.5,0,1,0);
  
  // postavljanje vrste svetala
  GLfloat light_position[] = {0,0.5,-1,0};
  GLfloat ambient_light[] = {0,0,0,1};
  GLfloat diffuse_light[] = {0.7,0.7,0.7,1};
  GLfloat specular_light[] = {0.9,0.9,0.9,1};

  GLfloat ambient_coeffs[] = {1.0,0.1,0.1,1};
  GLfloat diffuse_coeffs[] = {0.0,0.0,0.8,1};
  GLfloat specular_coeffs[] = {1,1,1,1};

  GLfloat shininess = 20;
  
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_light);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_light);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular_light);

  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffs);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);
  
  glPushMatrix();
    glTranslated(0,0,z_1);
    create_track();
    up_speed();
    create_hole();
    create_coin();
    left_wall();
    rigth_wall();
  glPopMatrix();
       
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glPushMatrix();
    glTranslated(x_ball,y_ball,z_ball);
    glRotatef(rotation_speed,1,0,0);
    create_sphera();
  glPopMatrix();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  if(animation_ongoing == 0 && in_hole == true) {
        game_over();
  }
  
  finish();
  score();
  
  glutSwapBuffers();
}


void on_timer_1(int value_1){
    
    if(value_1 != TIMER_ID)
        return;

    rotation_speed += 8;
    
    z_1 -= z_2;
    if(z_2 >= 0.02) {
        z_2 -= 0.01;
    }
    else {
        z_2 = 0.02;
    }
    
    // provera da ne izadje van staze(levo) i pomeranje lopte za po 0.2
    if(lm == 1){
      translate_x += 0.01;
      if((x_ball+0.01) < (0.7-0.115)){
            x_ball += 0.01;
            if(translate_x > 0.2) {
                lm = 0;
                translate_x = 0;
            }
      }
    }
    
    // provera da ne izadje van staze(desno) i pomeranje lopte za po 0.2
    if(rm == 1){
      translate_x += 0.01;
      if((x_ball-0.01) > (-0.7+0.115)){
            x_ball -= 0.01;
            if(translate_x > 0.2) {
                rm = 0;
                translate_x = 0;
            }
      }
    }
    
    // skakanje
    if(jump == 1) {
        y_ball += 0.01;
        if(y_ball > 0.35) {
            jump = 2;
        }
    }
    
    if(jump == 2) {
        y_ball -= 0.01;
        if(y_ball < 0.115) {
            jump = 0;
            y_ball = 0.115;
        }
    }
    
    // propadanje u rupu
    if(y_ball <= 0.114) {
        y_ball -= 0.03;
    }
    
    if(y_ball <= -1) {
        animation_ongoing = 0;
        in_hole = true;
    }
  
  glutPostRedisplay();

  if(animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer_1, TIMER_ID);
  }
}