#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
  double x;
  double y;
};

struct circle {
  struct point point;
  double r;
};

int main(int argc, char **argv) {
  struct circle *circle;
  int nCircle = 0;
  char str[100];
  FILE *data = argc > 1 ? fopen(argv[1], "r") : NULL;
  if (data == NULL) {
    printf("Неудалось открыть файл!\n");
    return 1;
  }

  while (fgets(str, 100, data) != NULL) {
    nCircle++;
    circle = realloc(circle, nCircle * (sizeof(struct circle)));
    circle[nCircle - 1].point.x = strtod(strchr(str, '(') + 1, NULL);
    circle[nCircle - 1].point.y = strtod(strchr(str, ' ') + 1, NULL);
    circle[nCircle - 1].r = strtod(strchr(str, ',') + 1, NULL);
  }

  for (int i = 0; i < nCircle; i++) {
        printf(" %d. Окружность(%.2lf %.2lf, %.2lf) \n",
               i + 1,
               circle[i].point.x,
               circle[i].point.y,
               circle[i].r);
        printf("\tПериметр = %.2f\n", 2 * M_PI * circle[i].r);
        printf("\tПлощадь = %.2f\n", M_PI * circle[i].r * circle[i].r);
  }

  free(circle);
  return 0;
}
