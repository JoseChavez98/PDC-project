#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <random>
#include <iostream>
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
  RngStream gen;
  gen = RngStream_CreateStream("generator_1");

  if(a > b)
    {
    return URDMonteCarloIntegration(b, a, n);
    }
  double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
  for (int i = 1; i <= n; i++)
    {

    double r = RngStream_RandU01(gen);
    sum = sum + fun(a+((b-a)*r));
    }
  sum = ((b-a)/n)*sum;
  return sum;
}

#endif