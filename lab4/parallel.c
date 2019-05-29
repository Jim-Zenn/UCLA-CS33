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

  for (i = DIM2; i < DIM3 - DIM2; i += DIM2) {
    for (j = i + DIM; j < i + DIM2 - DIM; j += DIM) {
      for (k = j + 1; k < j + DIM - 1; k++) {
        tmp = 0;
        for (u = -1; u <= 1; u++)
          for (v = -1; v <= 1; v++)
            for (w = -1; w <= 1; w++)
              tmp += old[k + u * DIM2 + v * DIM + w];
        tmp /= 27;
        new[k] = tmp;
        /*
         * update histogrammy array
         */
        u = tmp / 100;
        if (u <= 0) histogrammy[0]++;
        else if (u >= 9) histogrammy[9]++;
        else histogrammy[u]++;
      }
    }
  }
}