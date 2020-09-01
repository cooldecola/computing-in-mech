#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <functional>
#include <math.h>

// Using typedefs for all functions
using function_type = std::function<double(double)>;

// For calculating the factorials
int factorial (int n){
  if (n > 1){
    return n * factorial(n-1);
  }
  else{return 1;}
}

// Plotting the results in .dat format
void plot (std::vector<double> z, std::string filename){
  std::ofstream fout(filename);
  if(!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  double cnt = 0;
  for (auto it = z.begin(); it != z.end(); it++){
    fout << (-10 + (cnt/10)) << " " << *it << '\n';
    std::cout << (-10 + (cnt/10)) << " " << *it << std::endl;
    cnt++;
  }
}

void plot_lagrange (std::vector<double> z, std::string filename){
  std::ofstream fout(filename);
  if(!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  double cnt = 0;
  for (auto it = z.begin(); it != z.end(); it++){
    fout << (-10 + (cnt/1)) << " " << *it << '\n';
    std::cout << (-10 + (cnt/1)) << " " << *it << std::endl;
    cnt++;
  }
}

////////////////////////////////////////////////////////////////////////////
///////////////////////Taylor Interpolation ///////////////////////////////
//////////////////////////////////////////////////////////////////////////
std::vector<double> taylorInt(function_type y, function_type dydx, double a, double t){

  //tp is a vector which is used to store all the results in
  std::vector<double> tp;

  for (double i = -10; i <= 10; i=i+0.1){
    t = y(a); // resetting the t value as sin(a)

    for (int j = 1; j < 17; j++){

      // In this for loop modulus is used to iterate succesively between
      // all the if statements to use all the four cases in the derivatives
      // sin(x) -> cos(x) -> -sin(x) -> -cos(x) -> sin(x)
      if ( ((j-1)%4)+1 == 1){
        t = t + ( pow(static_cast<double>(i)-a, j) * (dydx(a)) ) / static_cast<double>(factorial(j));
      }

      if ( ((j-1)%4)+1 == 2){
        t = t + ( pow(static_cast<double>(i)-a, j) * (-y(a)) ) / static_cast<double>(factorial(j));
      }

      if ( ((j-1)%4)+1 == 3){
        t = t + ( pow(static_cast<double>(i)-a, j) * (-dydx(a)) ) / static_cast<double>(factorial(j));
      }

      if ( ((j-1)%4)+1 == 4){
        t = t + ( pow(static_cast<double>(i)-a, j) * (y(a)) ) / static_cast<double>(factorial(j));
      }
    }
    tp.push_back(t);
  }
  return tp;
}

////////////////////////////////////////////////////////////////////////////
/////////////////////// Lagrangian Interpolation //////////////////////////
//////////////////////////////////////////////////////////////////////////
std::vector<double> lagInt(function_type y){
  std::vector<double> li;
  std::vector<double> xVals;
  std::vector<double> yVals;
  double prod = 1;
  double sum = 0;
  for (double z = 10; z <= 10; z = z + 0.1){
    xVals.push_back(z);
  }

  for (double x = -10; x <= 10 ; x = x+1){

  for (int i = 0; i < xVals.size(); i++){
    prod = 1;
    sum = 0;
    for (int j = 0; j < xVals.size(); j++){
      if (i != j){
        prod = prod * ( (x - xVals.at(j) ) / ( xVals.at(i) - xVals.at(j) ) );
      }
    }
    //std::cout << prod << std::endl;
    prod = prod * y(x);
    //std::cout << prod << std::endl;
    sum = sum + prod;

  }
  yVals.push_back(sum);

}
  return yVals;
}


////////////////////////////////////////////////////////////////////////////
//////////////////////// MAIN FUNCTION ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int main(){

  // typedefs of sin(x) and cos(x)
  auto y = [](double x){
    return sin(x);
  };

  auto dydx = [](double x){
    return cos(x);
  };

  // The Taylor interpolation centered at a = 1
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                    Taylor Interpolation            |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";

  double a = 0;
  double t = y(a);
  std::vector<double> taylor_int_results;
  taylor_int_results = taylorInt (y, dydx, a, t);

  //Plotting the results
  plot (taylor_int_results, "taylor_int_degr.dat");

  // Lagrangian Interpolation
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                    Lagrangian Interpolation        |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";

  std::vector<double> lag_int_results;
  lag_int_results = lagInt(y);
  plot_lagrange (lag_int_results, "lagrange_int.dat");
}
