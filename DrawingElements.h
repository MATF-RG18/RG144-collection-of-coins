#include <GL/glut.h>

// iscrtavanje staze
void create_track(void);

// iscrtavanje sfere
void create_sphera(void);

// iscrtavanje rupa
void create_hole(void);

// iscrtavanje strelica
void up_speed(void);

// iscrtavanje levog zida
void left_wall(void);

// iscrtavanje desnog zida
void rigth_wall(void);

// iscrtavanje novcica
void create_coin(void);

// provera upadanja u rupu
void check_hole(float xl,float xd,float zg,float zd);

// provera za ubrzanje
void check_hole2(float xl,float xd,float zd,float zg);