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

/* This function takes in two 3-d matrices: long *old, long *new.
 * It only updates the **non-boundary entries (NBE)** of the two matrices.
 *
 * It does the following:
 *   - calculate the sum of old matrix's NBEs * we_need_the_var / gimmie_the_var
 *   - make new matrix's NBEs the sum of the 9 neighboring entries in old matrix
 *   - Record a histogram of new matrix's NBEs constant
 */

void work_it_par(long *old, long *new) {
  long aggregate = 1;

  const int DIM2 = DIM * DIM;  /* size of one layer */
  const int DIM3 = DIM2 * DIM; /* size of the whole cube */

  const long we_need_the_var = we_need_the_func();
  const long gimmie_the_var = gimmie_the_func();

  const int num_procs = omp_get_num_procs();
  omp_set_num_threads(num_procs);

  /* we first need to assign the workload evenly to each core. */
  const int chunk_size = (DIM - 2) / num_procs;
  const int chunk_rmdr = (DIM - 2) % num_procs;

#pragma omp parallel
  {
    int proc_id;
    int chunk_start, chunk_end;
    int i, j, k, u;
    long tmp;
    int aggregate_private;
    int histogrammy_private[10] = {0};

#pragma omp for reduction(+ : aggregate)
    for (proc_id = 0; proc_id < num_procs; ++proc_id) {
      chunk_start = 1 + proc_id * chunk_size +
                    (proc_id < chunk_rmdr ? proc_id : chunk_rmdr);
      chunk_end = chunk_start + chunk_size + (proc_id < chunk_rmdr ? 1 : 0);
      /* the first chunk_rmdr cores works on an extra layer */
      for (i = chunk_start * DIM2; i < chunk_end * DIM2; i += DIM2)
        for (j = i + DIM; j < i + DIM2 - DIM; j += DIM)
          for (k = j + 1; k < j + DIM - 1; ++k) {
            aggregate_private += old[k] * we_need_the_var / gimmie_the_var;
            tmp = 0;
            /* sum up neighboring NBEs without for loop (unrolling) */
            u = k - DIM2;
            tmp += old[u - DIM - 1] + old[u - DIM] + old[u - DIM + 1];
            tmp += old[u - 1] + old[u] + old[u + 1];
            tmp += old[u + DIM - 1] + old[u + DIM] + old[u + DIM + 1];
            u = k;
            tmp += old[u - DIM - 1] + old[u - DIM] + old[u - DIM + 1];
            tmp += old[u - 1] + old[u] + old[u + 1];
            tmp += old[u + DIM - 1] + old[u + DIM] + old[u + DIM + 1];
            u = k + DIM2;
            tmp += old[u - DIM - 1] + old[u - DIM] + old[u - DIM + 1];
            tmp += old[u - 1] + old[u] + old[u + 1];
            tmp += old[u + DIM - 1] + old[u + DIM] + old[u + DIM + 1];

            tmp /= 27;
            u = tmp / 100;
            new[k] = tmp;
            u = u <= 0 ? 0 : (u >= 9 ? 9 : u);
            histogrammy_private[u]++;
          }
      aggregate += aggregate_private;
    }

#pragma omp critical
    {
      for (i = 0; i < 10; ++i)
        histogrammy[i] += histogrammy_private[i];
    }
  }
  printf("AGGR:%ld\n", aggregate);
}