#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 10

static int animation_ongoing;
static float rotation_speed;

static void initialize(void);
static void on_display(void);
static void on_reshape(int width, int height);
static void create_track(void);
static void create_sphera(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer_1(int value_1);
static void create_hole(void);
static void check_hole(float xl,float xd,float yg,float yd);
static void check_hole2(float xl,float xd,float zd,float zg);
static void up_speed(void);
static void left_wall(void);
static void rigth_wall(void);
static void game_over_hole(void);
static void specialKeys(int key, int x, int y);
static void finish(void);

int width_window = 700;
int height_window = 500;
float z_1 = 0.7; // za koliko transliram stazu
float z_2 = 0.02; // promenljiva za ubrzanje
float x_ball = 0.0; // x-kordinata lopte
int niz_random[1000]; // generisanje random niza
int i, lm = 0, rm = 0;
float z_ball = 0.5; // z-kordinata lopte
float y_ball = 0; // y-kordinata lopte
bool in_hole = false;
int jump = 0;
float translate_x = 0.0;

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutInitWindowSize(width_window, height_window);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  animation_ongoing = 0;
  rotation_speed = 0;

  for( i=0; i<1000; i++) {
    niz_random[i] = rand() % 10;
  }
    
  initialize();
  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);
  glutSpecialFunc(specialKeys);
  
  glutMainLoop();

  return 0;
}

static void initialize(void){
  glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void on_keyboard(unsigned char key, int x, int y){
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

// kretanje levo, desno
static void specialKeys(int key, int x, int y){
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

static void on_timer_1(int value_1){
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
    
    if(lm == 1){
      translate_x += 0.01;
      x_ball += 0.01;
      if(translate_x > 0.2) {
          lm = 0;
          translate_x = 0;
      }
      
      if(x_ball > 0.8) {
	  animation_ongoing = 0;
          sleep(3);
	  exit(0);
      }
    }
    
    if(rm == 1){
      translate_x += 0.01;
      x_ball -= 0.01;
      if(translate_x > 0.2) {
          rm = 0;
          translate_x = 0;
      }
      
      if(x_ball < -0.8) {
	  animation_ongoing = 0;
	  sleep(3);
	  exit(0);
      }
    }
    
    // skakanje
    if(jump == 1) {
        y_ball += 0.01;
        if(y_ball > 0.3) {
            jump = 2;
        }
    }
    
    if(jump == 2) {
        y_ball -= 0.01;
        if(y_ball < 0) {
            jump = 0;
            y_ball = 0;
        }
    }
  
  glutPostRedisplay();

  if(animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer_1, TIMER_ID);
  }
}

static void on_display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        game_over_hole();
  }
  
  finish();
  
  glutSwapBuffers();
}

static void on_reshape(int width, int height){
  width_window = width;
  height_window =  height;

  glViewport(0,0,width_window,height_window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(53,width_window/(float)height_window,1, 15);

}

// iscrtavanje sfere
static void create_sphera(void){
  glPushMatrix();
    glShadeModel(GL_FLAT);
    glutSolidSphere(0.115,15,15);
  glPopMatrix();
}

// iscrtavanje staze
static void create_track(void){
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

// iscrtavanje rupa
static void create_hole(void) {
  int i;
  float x;
  for(i=0; i<1000; i=i+6) {
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
        glVertex3f(x,0,i*0.2+0.4);
        glVertex3f(x,0,i*0.2);
        glVertex3f(x-0.3,0,i*0.2);
        glVertex3f(x-0.3,0,i*0.2+0.4);
     glEnd();   
    }
  }
}

// isrtavanje strelica za ubrzanje
static void up_speed(void){
  int i;
  float x;
  for(i=1; i<1000; i=i+10) {
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
            glVertex3f(x,0,i*0.2);
            glVertex3f(x-0.3,0,i*0.2);
            glVertex3f((x+x-0.3)/2,0,i*0.2+0.2);
        glEnd();
        
        glColor3d(1,1,1);
        glBegin(GL_POLYGON);
            glVertex3f(x,0,i*0.2-0.1);
            glVertex3f(x-0.3,0,i*0.2-0.1);
            glVertex3f((x+x-0.3)/2,0,i*0.2+0.2-0.1);
        glEnd();
        
        glColor3d(0,1,0);
        glBegin(GL_POLYGON);
            glVertex3f(x,0,i*0.2-0.2);
            glVertex3f(x-0.3,0,i*0.2-0.2);
            glVertex3f((x+x-0.3)/2,0,i*0.2+0.2-0.2);
        glEnd();
    }
  }     
}

// provera upadanja u rupu
void check_hole(float xl,float xd,float zg,float zd){
     if((x_ball <= (xl-0.05)) && (x_ball >= (xd+0.05)) && 
         (zg >= z_ball-z_1) && (zd+0.2 <= z_ball-z_1) && (y_ball == 0)) {
       in_hole = true;
       animation_ongoing = 0;
     }
}

// provera za ubrzanje
void check_hole2(float xl,float xd,float zd,float zg){
    if((x_ball <= xl) && (x_ball >= xd) && 
         (zg >= z_ball-z_1) && (zd+0.2 <= z_ball-z_1) && (y_ball == 0)){
        
        z_2 = 0.2;
    }
}

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


// isrtavanje desnog zida
static void rigth_wall(void){
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
static void left_wall(void){
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

void game_over_hole(void){

    char ispis[20];
    sprintf(ispis, "Game over");

    glPushMatrix();
        glColor3d(1,1,0);
        glRasterPos3f(0.2,0,2);
        int len = strlen(ispis);
        for(int i =0; i<len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ispis[i]);
        }
    glPopMatrix();
} 