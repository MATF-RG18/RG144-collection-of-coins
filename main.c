#include <GL/glut.h>
#include "CallBack.h"
#include <stdbool.h>
#include "Global.h"

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  width_window = 700;
  height_window = 500;
  animation_ongoing = 0;
  rotation_speed = 0;
  z_1 = 0.7; 
  z_2 = 0.02; 
  x_ball = 0.0; 
  niz_random[1000]; 
  niz_random_coin[25]; 
  lm = 0, rm = 0;
  z_ball = 0.5; 
  y_ball = 0.115; 
  in_hole = false;
  jump = 0;
  translate_x = 0.0;

  glutInitWindowSize(width_window, height_window);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  for( i=0; i<1000; i++) {
    niz_random[i] = rand() % 10;
  }
  
  float min_broj = -0.7 + 0.115;
  float max_broj = 0.7 - 0.115;
    
  // generisem brojeve na intervalu [min_broj,max_broj]
  for(int i = 0 ; i < 25 ; i++ ) {
    float max2 = (max_broj - min_broj);   
    float sl_broj = max2 * ((float)rand()/(float)RAND_MAX) + min_broj;        
    niz_random_coin[i] = sl_broj;
  }
    
  initialize();
  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);
  glutSpecialFunc(specialKeys);
  
  glutMainLoop();

  return 0;
}