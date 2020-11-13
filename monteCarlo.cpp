#include <random>
#include <iostream>

double fun(double x) //f(x) = x;
{
    return x;
}

double MonteCarloIntegration (double a, double b, int n)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  if(a > b)
    {
    return MonteCarloIntegration(b, a, n);
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

int main(int argc,char * argv[]) {

  if (argc < 2)
    {
    std::cerr << "use: " << argv[0]
              << " Numer_of_Random_samples (n) \n";
    std::cerr << " Example:\n  " << argv[0] << " 1000000 \n\n";
    return -1;
    }

  double b = 4.0; //lower bound
  double a = 7.0; //upper bound

  int n = atoi(argv[1]);

  std::cout << MonteCarloIntegration(a,b,n) << std::endl;
  return 0;
}
