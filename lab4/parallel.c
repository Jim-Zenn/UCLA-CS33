// OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Qingwei Zeng
 * UCLA ID : 005181694
 * Email : zenn@ucla.edu
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void work_it_par(long *old, long *new) {
  int i, j, k;
  int u, v, w;
  long compute_it;
  long aggregate = 1;

  const long DIM2 = DIM * DIM;
  const long DIM3 = DIM2 * DIM;

  const double we_need_the_var = we_need_the_func();
  const long gimmie_the_var = gimmie_the_func();

  for (i = DIM2; i < DIM3 - DIM2; i += DIM2) {
    for (j = i + DIM; j < i + DIM2 - DIM; j += DIM) {
      for (k = j + 1; k < j + DIM - 1; k++) {
        compute_it = old[k] * we_need_the_var / gimmie_the_var;
        aggregate += compute_it;
      }
    }
  }

  printf("AGGR:%ld\n", aggregate);

  for (i = 1; i < DIM - 1; i++) {
    for (j = 1; j < DIM - 1; j++) {
      for (k = 1; k < DIM - 1; k++) {
        new[i * DIM2 + j * DIM + k] = 0;
        for (u = -1; u <= 1; u++) {
          for (v = -1; v <= 1; v++) {
            for (w = -1; w <= 1; w++) {
              new[i * DIM2 + j * DIM + k] +=
                  old[(i + u) * DIM2 + (j + v) * DIM + (k + w)];
            }
          }
        }
        new[i * DIM2 + j * DIM + k] /= 27;
      }
    }
  }

  for (i = 1; i < DIM - 1; i++) {
    for (j = 1; j < DIM - 1; j++) {
      for (k = 1; k < DIM - 1; k++) {
        u = (new[i * DIM2 + j * DIM + k] / 100);
        if (u <= 0)
          u = 0;
        if (u >= 9)
          u = 9;
        histogrammy[u]++;
      }
    }
  }
}