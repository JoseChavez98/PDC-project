#include <iostream>
#include "montecarlo.h"
#include <chrono> 
using namespace std::chrono;

int main(){

  int times[] = {100,1000,10000,100000,1000000,10000000,100000000, 1000000000};

  double b = 4.0; //lower bound
  double a = 7.0; //upper bound

  printf("\n URDMonteCarloIntegration \n");
  printf("result  time\n");

  for(int i=0;i<7;i++){
    auto start = high_resolution_clock::now();
    auto r = URDMonteCarloIntegration(a,b,times[i]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printf("%f  %lld seconds\n", r ,duration.count());
  }

  printf("\n RNGMonteCarloIntegration \n");
  printf("result  time\n");

  for(int i=0;i<7;i++){
    auto start = high_resolution_clock::now();
    auto r = RNGMonteCarloIntegration(a,b,times[i]);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printf("%f  %lld seconds\n", r ,duration.count());
  }

  
  return 0;
}