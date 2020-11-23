#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <random>
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "RngStream.h"

double fun(double x) //f(x) = x;
{
    return x;
}

double URDMonteCarloIntegration (double a, double b, int n)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  if(a > b)
    {
    return URDMonteCarloIntegration(b, a, n);
    }
  double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
  for (int i = 1; i <= n; i++)
    {

    double r = dis(gen);
    sum = sum + fun(a+((b-a)*r));
    }
  sum = ((b-a)/n)*sum;
  return sum;
}

double RNGMonteCarloIntegration (double a, double b, int n)
{


  if(a > b)
    {
    return RNGMonteCarloIntegration(b, a, n);
    }
  double sum = 0.0;

#pragma omp parallel
{
  auto s = std::to_string(omp_get_thread_num());
  //std::cout<<omp_get_thread_num()<<std::endl;
  const char* x = s.c_str();
  RngStream gen;
  gen = RngStream_CreateStream(x);

 #pragma omp for reduction(+:sum)
  for (int i = 1; i <= n; i++)
    {
    double r = RngStream_RandU01(gen);
    sum = sum + fun(a+((b-a)*r));
  }
}
  sum = ((b-a)/n)*sum;
  return sum;
}

#endif
