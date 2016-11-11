#include <stdio.h>

typedef struct {
  int weight;
  int temp;
} tolerance;

int read_tolerance(tolerance *t, FILE *fp) {
  char line[80];
  if (fgets(line, sizeof(line), stdin) == NULL) {
    return 0;
  }
  sscanf(line, "%d %d", &t->weight, &t->temp);
  return 1;
}

int main(int argc, char *argv[]) {
  tolerance goldilocks;
  tolerance table_setting;
  FILE *fp = stdin;
  int chair;

  if (read_tolerance(&goldilocks, fp)) {
    chair = 1;
    while (read_tolerance(&table_setting, fp)) {
      if (table_setting.weight >= goldilocks.weight &&
          table_setting.temp <= goldilocks.temp) {
        printf("%d ", chair);
      }
      ++chair;
    }
  }
}
