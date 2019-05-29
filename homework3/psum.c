/*
 * psum1.c
 * Copyright (C) 2019 Jim Zenn <zenn@ucla.edu>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>

#define N 5

void psum1(float a[], float p[], long n);

int mpin() {
  float a[N];
  float p[N];
  long n = N, i;

  for (i = 0; i < N; i ++)
    a[i] = i;

  psum1(a, p, n);

  for (i = 0; i < N; i ++)
    printf("%.0f ", p[i]);
  printf("\n");

  return 0;
}

void psum(float a[], float p[], long n) {
  float last_val;
  float pi0, pi1, pi2, pi3, pi4;
  long i;
  last_val = a[0];
  p[0] = last_val;
  while (i < n - 4) {
    pi0 = last_val + a[i];

    pi1 = pi0 + a[i+1];
    p[i] = pi0;

    pi2 = pi1 + a[i+2];
    p[i+1] = pi1;

    pi3 = pi2 + a[i+3];
    p[i+2] = pi2;

    pi4 = pi3 + a[i+4];
    p[i+3] = pi3;

    p[i+4] = pi4;
    last_val = pi4;

    i += 4;
  }
  float pi = last_val;
  while (i < n) {
    pi = pi + a[i];
    p[i] = pi;
    i ++;
  }
}
