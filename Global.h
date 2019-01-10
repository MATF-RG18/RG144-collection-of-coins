#include <stdbool.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 10

int animation_ongoing; // promenljiva za pokretanje animacije
float rotation_speed; // promenljiva koja regulise rotaciju lopte
int width_window; // sirina prozora
int height_window; // visina prozora
float z_1; // za koliko transliram stazu
float z_2; // promenljiva za ubrzanje
float x_ball; // x-kordinata lopte
int niz_random[1000]; // generisanje random niza
float niz_random_coin[25];
int i; 
int lm ,rm ; // promenljive za kretanje lopte(levo,desno)
float z_ball; // z-kordinata lopte
float y_ball; // y-kordinata lopte
bool in_hole; // promenljiva za upadanje u rupu
int jump; // promenljiva za skok
float translate_x; // promenljiva za transliranje lopte(levo,desno) za 0.2
int num_of_coins; //broj pokupljenih novcica