#include <GL/glut.h>

static void initialize(void);
static void on_display(void);
static void on_reshape(int width, int height);
static void create_track(void);
static void create_sphera(void);
static void on_keyboard(unsigned char key, int x, int y);
static void set_camera(void);

int width_window = 500;
int height_window = 500;

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(width_window, height_window);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  initialize();
  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);

  glutMainLoop();

  return 0;
}

static void initialize(void){
  glClearColor(0,0,0,0);
}

static void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
  }

}

static void set_camera(void){

  glViewport(0,0,width_window,height_window);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(53,width_window/(float)height_window,1, 15);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0.1,-1.75,0,0,0,0,0,1);
  glRotatef(60,1,0,0);

}

static void on_display(void){

  glClear(GL_COLOR_BUFFER_BIT);

  set_camera();
  create_track();
  create_sphera();

  glutSwapBuffers();

}

static void on_reshape(int width, int height){
  width_window = width;
  height_window =  height;
}

// iscrtavanje sfere
static void create_sphera(void){

  glTranslated(0,-0.7,0);
  GLUquadric* quad = gluNewQuadric();
  glColor3d(0,1,0);
  gluSphere(quad,0.115,150,150);
  //glutSolidSphere(0.2,150,150);
  glTranslated(0,0.7,0);
}

// iscrtavanje staze
static void create_track(void){

  for(int i=1; i<30; i++) {
    switch (i%2) {
      case 0:
        glColor3d(0.3,0,0.7);
        break;
      case 1:
        glColor3d(1,0,0);
        break;
    }
    glBegin(GL_POLYGON);
      glVertex3d(0.5,-1+(0.2*(i-1)),0);
      glVertex3d(0.5,-1+(0.2*i),0);
      glVertex3d(-0.5,-1+(0.2*i),0);
      glVertex3d(-0.5,-1+(0.2*(i-1)),0);
    glEnd();
  }
}
