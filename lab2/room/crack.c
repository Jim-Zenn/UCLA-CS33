#include <stdio.h>

int main(int argc, char* argv[]) {
  const char * code = "maduiersnfotvbyl";
  const char * ans = "oilers";
  for (int i = 0; i < 6; i ++) {
    char key;
    int idx;
    for (int j = 0; j < 16; j ++) {
      key = 'a' + j;
      if (code[key & 0xf] == ans[i])
        printf("%c", key);
    }
  }
  printf("\n");
}
