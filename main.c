#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 50
static int animation_ongoing;
static float rotation_speed;

static void initialize(void);
static void on_display(void);
static void on_reshape(int width, int height);
static void create_track(void);
static void create_sphera(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer_1(int value_1);
static void on_timer_2(int value_2);
static void on_timer_3(int value_3);
static void create_hole(void);

int width_window = 700;
int height_window = 500;
float y_1 = -0.7;
float x_1 = 0.0;
float z_camera = -1.6;
int niz_random[100];


int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(width_window, height_window);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  animation_ongoing = 0;
  rotation_speed = 0;

  for(int i=0; i<200; i=i+2) {
    niz_random[i] = rand() % 10;
  }

  initialize();
  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);

  glutMainLoop();

  return 0;
}

static void initialize(void){
  glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-1.75,0,0,0,0,0,1);
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
    case 'a':
      if(animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_2, TIMER_ID);
      }
      break;
    case 'd':
      if(animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer_3, TIMER_ID);
      }
      break;
    case 's':
      animation_ongoing = 0;
  }
}

static void on_timer_1(int value_1){
  if(value_1 != TIMER_ID)
    return;

  y_1 += 0.02;
  z_camera += 0.02;

  rotation_speed += 8;

  glutPostRedisplay();

  if(animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer_1, TIMER_ID);
  }
}

// timer_2 za skretanje u levo
static void on_timer_2(int value_2){
  if(value_2 != TIMER_ID)
    return;

  x_1 += 0.02;

  if(animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer_2, TIMER_ID);
  }
}

// // timer_3 za skretanje u desno
static void on_timer_3(int value_3){
  if(value_3 != TIMER_ID)
    return;

  x_1 -= 0.02;

  if(animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer_3, TIMER_ID);
  }
}

static void on_display(void){
  glClear(GL_COLOR_BUFFER_BIT);

  // pomeranje kamere sa kretanjem sfere
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,z_camera,0,0,1.75+z_camera,0,0,1);
  glRotatef(90,1,0,0);

  // postavljanje vrste svetala
  GLfloat light_position[] = {-0.7,0,-1,0};
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

  create_track();
  create_hole();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  create_sphera();
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);

  glutSwapBuffers();
}

static void on_reshape(int width, int height){
  width_window = width;
  height_window =  height;

  // postavljanje kamere
  glViewport(0,0,width_window,height_window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(53,width_window/(float)height_window,1, 15);

}

// iscrtavanje sfere
static void create_sphera(void){
  glTranslated(x_1,y_1,0);
  glRotatef(360*rotation_speed/360,1,0,0);
  glShadeModel(GL_FLAT);
  glutSolidSphere(0.115,15,15);
  glRotatef(-(360*rotation_speed/360),1,0,0);
  glTranslated(-x_1,-y_1,0);
}

// iscrtavanje staze
static void create_track(void){
  for(int i=1;i<1000; i++) {
    switch (i%2) {
      case 0:
        glColor3d(0.2,0.2,0.2);
        break;
      case 1:
        glColor3d(0,1,0);
        break;
    }
    glBegin(GL_POLYGON);
      glVertex3d(0.7,-1+(0.2*(i-1)),0);
      glVertex3d(0.7,-1+(0.2*i),0);
      glVertex3d(-0.7,-1+(0.2*i),0);
      glVertex3d(-0.7,-1+(0.2*(i-1)),0);
    glEnd();
  }
}

// iscrtavanje rupa
static void create_hole(void) {
  int i;
  float x;
  for(i=0; i<200; i=i+2) {
    // -0.7 do 0.7 ide x a sirina rupe je 0.3
    if(niz_random[i] % 2 != 0){
      x = -niz_random[i] * 0.1;
    }
    else{
      x = niz_random[i] *0.1;
    }
    glColor3d(0,0,0);
    glBegin(GL_POLYGON);
      glVertex3d(x,i*0.2+0.4,0);
      glVertex3d(x,i*0.2,0);
      glVertex3d(x-0.3,i*0.2,0);
      glVertex3d(x-0.3,i*0.2+0.4,0);
    glEnd();
  }
}
