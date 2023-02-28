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

int Check_Error(char *str) {
  if (!(strncmp("circle", str, 6))) {
    if (!(isdigit(*(strchr(str, '(') + 1))) &&
        !(*(strchr(str, '(') + 1) == '-') &&
        !(*(strchr(str, '(') + 1) == '+')) {
      printf("%s", str);
      for (int i = 0; i < strchr(str, '(') - &str[0] + 1; i++)
        printf(" ");
      printf("^\n");
      printf("Ошибка в столбце %ld: ожидалось \'double\'\n\n",
             strchr(str, '(') - &str[0] + 1);
      return 0;
    }
    if (!(isdigit(*(strchr(str, ' ') + 1))) &&
        !(*(strchr(str, ' ') + 1) == '-') &&
        !(*(strchr(str, ' ') + 1) == '+')) {
      printf("%s", str);
      for (int i = 0; i < (strchr(str, ' ') - &str[0] + 1); i++)
        printf(" ");
      printf("^\n");
      printf("Ошибка в столбце %ld: ожидалось \'double\'\n\n",
             strchr(str, ' ') - &str[0] + 1);
      return 0;
    }
    if (!(isdigit(*(strchr(str, ',') + 2))) &&
        !(*(strchr(str, ',') + 1) == '+')) {
      printf("%s", str);
      for (int i = 0; i < (strchr(str, ',') - &str[0] + 2); i++)
        printf(" ");
      printf("^\n");
      printf("Ошибка в столбце %ld: ожидалось \'double\'\n\n",
             strchr(str, ',') - &str[0] + 1);
      return 0;
    }
    if (strtod(strchr(str, ',') + 1, NULL) <= 0) {
      printf("%s", str);
      for (int i = 0; i < strchr(str, ',') - &str[0] + 2; i++)
        printf(" ");
      printf("^\n");
      printf("Ошибка в столбце %ld: радиус: \'0\' или "
             "отрицательный"
             "Значение\n\n",
             strchr(str, ',') - &str[0] + 2);
      return 0;
    } else
      return 1;
  } else {
    printf("%s \n^\n", str);
    printf("Ошибка в столбце 0: ожидалось \'circle\'\n\n");
    return 0;
  }
}

int main(int argc, char **argv) {
  struct circle *circle;
  int nCircle = 0;
  int code;
  char str[100];
  FILE *data = argc > 1 ? fopen(argv[1], "r") : NULL;
  if (data == NULL) {
    printf("Неудалось открыть файл!\n");
    return 1;
  }

  while (fgets(str, 100, data) != NULL) {
    code = Check_Error(str);
    if (!code)
      continue;
    if (code) {
      nCircle++;
      circle = realloc(circle, nCircle * (sizeof(struct circle)));
      circle[nCircle - 1].point.x = strtod(strchr(str, '(') + 1, NULL);
      circle[nCircle - 1].point.y = strtod(strchr(str, ' ') + 1, NULL);
      circle[nCircle - 1].r = strtod(strchr(str, ',') + 1, NULL);
    }
  }

  for (int i = 0; i < nCircle; i++) {
    printf(" %d. Окружность(%.2lf %.2lf, %.2lf) \n", i + 1, circle[i].point.x,
           circle[i].point.y, circle[i].r);
    printf("\tПериметр = %.2f\n", 2 * M_PI * circle[i].r);
    printf("\tПлощадь = %.2f\n", M_PI * circle[i].r * circle[i].r);
    printf("\tПересечения: \n");
    for (int j = 0; j < nCircle; j++) {
      if (i == j)
        continue;
      if (circle[i].r + circle[j].r >=
          sqrt(pow(circle[i].point.x - circle[j].point.x, 2) +
               pow(circle[i].point.y - circle[j].point.y, 2)))
        printf("\t  %d. Окружность \n", j + 1);
    }
    printf("\n");
  }

  free(circle);
  return 0;
}
