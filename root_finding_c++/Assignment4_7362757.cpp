#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <math.h>
#include <functional>
#include <ctime>
#include <chrono>

// Using typedefs for all functions
using function_type = std::function<double(double)>;

// Using a template returning bool which checks if
// two numbers have the same sign
// TEMPLATE DECLERATION
template <typename T>
inline bool SameSign(T x, T y);

// Template implementation
template <typename T>
inline bool SameSign(T x, T y){
  return (x >= 0) ^ (y < 0);
}

// Function computing the bi seciotional method
double bi_section_method(function_type f, double a, double b, double iterations, double tolerance){

  // Starting a timer to see how long this function takes
  auto start = std::chrono::high_resolution_clock::now();

  double mid;
  double result;
  for (int i = 0; i < iterations; i++){
    mid = (a+b)/2;
    // if (f(mid) == 0 || (b-a)/2 < tolerance){
    //   result = mid;
    // }

    if ( SameSign(f(mid), f(a)) ){
      a = mid;
    } else {b = mid;}

    if (i == iterations - 1){result = (a+b)/2;}
  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << '\n';

  std::cout << "Bi Section Method using " << iterations << " iterations: " << result << std::endl;
  std::cout << '\n';
  return result;
}

// Function computing the false position method
double false_position (function_type f, double a, double b, double iterations, double tolerance){

  auto start = std::chrono::high_resolution_clock::now();

  double c;
  double result;
  for (int i = 0; i < iterations; i++){
    c = (a*f(b) - b*f(a))/(f(b) - f(a));
    // if (f(c) == 0 || (b-a)/2 < tolerance){
    //   result = c;
    // }

    if (f(a)*f(c) < 0){
      b = c;
    } else{ a = c; }

    if (i == iterations - 1){result = (a+b)/2;}

  }

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << '\n';

  std::cout << "Fale Position Method using " << iterations << " iterations: " << result << std::endl;
  std::cout << '\n';
  return c;
}



int main(){

  auto f = [](double d){
    return 16*pow(d,2.5) + 20000*pow(d,2) - 931.95*d - 480.886;
  };

  // VALUES
  double iterations = 1000;
  double a = 0.15;
  double b = 0.19;
  double tolerance = 0;

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                  BI-SECTIONAL METHOD               |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";

  bi_section_method (f, a, b, iterations, tolerance);

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                  FALSE POSITION METHOD             |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  false_position (f, a, b, iterations, tolerance);


}
