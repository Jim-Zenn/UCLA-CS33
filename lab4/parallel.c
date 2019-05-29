// OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Qingwei Zeng
 * UCLA ID : 005181694
 * Email : zenn@ucla.edu
 */

/* To better comprehend this problem, I think it helps to understand what is
 * actually being done.
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i, j, k;
  int u, v, w;
  int i_o, j_o, k_o;
  long tmp;
  long aggregate = 1;

  const int DIM2 = DIM * DIM;
  const int DIM3 = DIM2 * DIM;

  const double we_need_the_var = we_need_the_func();
  const long gimmie_the_var = gimmie_the_func();

  #pragma omp parallel for reduction(+:aggregate) private(i, j, k)
  for (i = DIM2; i < DIM3 - DIM2; i += DIM2)
    for (j = i + DIM; j < i + DIM2 - DIM; j += DIM)
      for (k = j + 1; k < j + DIM - 1; k++)
        aggregate += old[k] * we_need_the_var / gimmie_the_var;
  printf("AGGR:%ld\n", aggregate);

  i_o = DIM2;
  for (i = 1; i < DIM - 1; i++) {
    j_o = i_o + DIM;
    for (j = 1; j < DIM - 1; j++) {
      k_o = j_o + 1;
      for (k = 1; k < DIM - 1; k++) {
        tmp = 0;
        for (u = -1; u <= 1; u++)
          for (v = -1; v <= 1; v++)
            for (w = -1; w <= 1; w++)
              tmp += old[k_o + u * DIM2 + v * DIM + w];
        tmp /= 27;
        new[k_o] = tmp;
        k_o += 1;
      }
      j_o += DIM;
    }
    i_o += DIM2;
  }

  for (i_o = DIM2; i_o < DIM3 - DIM2; i_o += DIM2) {
    for (j_o = i_o + DIM; j_o < i_o + DIM2 - DIM; j_o += DIM) {
      for (k_o = j_o + 1; k_o < j_o + DIM - 1; k_o++) {
        u = (new[k_o] / 100);
        if (u <= 0)
          u = 0;
        if (u >= 9)
          u = 9;
        histogrammy[u]++;
      }
    }
  }
}