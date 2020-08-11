#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fortune-mod-common.h"
#include "computersfuckingsuck.h"
char * funny[] = {
    "bougère\0",
    "青虫\0",
    "real AMERICAN alphAbEt\0",
    "sfg#hehedfgd\0",
};
 struct super_boger {
  int x;
  char y;
  char * hehe;
  char * notevenfunanymore;
};
void surprise(char * getfucked) {
  printf("haha fuck you!! (%s)\n",getfucked);
  char *gnutards [] = {"a\0",getfucked};
  fukyou(2, &getfucked);
}

int boger(int a, int b, char *c, struct super_boger *maggot) {
  char * fu = funny[rand() %3];
  maggot->hehe = fu;
  
  printf("a == %d b == %d c == %s maggot.x == %d maggot.y == %c maggot.hehe == %s\n ", a, b, c,
           maggot->x, maggot->y, maggot->hehe);
  if (b > 0 ) {
    maggot->x++;
    maggot->y = rand() % 127;
    return boger(a, (b - 1), c, maggot);
  } else {
    if (fu == funny[3]) {
      return 5;
    } else {
      surprise(maggot->notevenfunanymore);
      return boger(a, b+1, c, maggot);
    }
  }
}
int main(int argc, char **argv) {
  int a;
  int b = 5;
  char getfucked[MAXPATHLEN]; // im not fixing this retarded buffar shit i guess
  struct super_boger *maggot = malloc(sizeof(struct super_boger));  
  if (argc >= 2) {
    strcpy(getfucked,argv[1]);
  } else {
    strcpy(getfucked,"./fart.dat\0");
  }
  char c[] = "nibbler\0";
  maggot->notevenfunanymore = getfucked;
  maggot->x = 1;
  maggot->y = 'h';

  int huh = boger(a, b, c, maggot);
  printf("boger exited with %d\n", huh);
  return 0;
}
