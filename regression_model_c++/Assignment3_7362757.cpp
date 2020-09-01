#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <math.h>


// This function takes in the slope value and constant and plots it
// Linear regression
void lin_reg (double a, double b, std::string filename){
  std::ofstream fout(filename);
  if(!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  for (double i = -10; i <= 10; i = i + 0.0001){
    fout << i << " " << a+b*i << '\n';
    //std::cout << i << " " << a+b*i << std::endl;
  }
}

// This function simply takes all the stress and strain points and plots them
// alongside the linear equation
void plot_points (std::vector<double> strain, std::vector<double> stress, std::string filename){
  std::ofstream fout(filename);
  if(!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  for (int i = 0; i < strain.size(); i++){
    fout << strain.at(i) << " " << stress.at(i) << '\n';
  }
}

void elongation_study (std::vector<double> elongation, std::string filename){
  std::ofstream fout (filename);
  if (!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  for (int i = 0; i < 20; i++){
    fout << i+1 << " " << elongation.at(i) << '\n';
    std::cout <<"Number of Beam(s): " << i+1 << " " << "Elongation: " << elongation.at(i) << '\n';
  }
}


int main(){
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                    ASS 3                            |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";

  // Taking in all the constants given in the assignment
  double length = 1000; // cm
  double area = 10.54; //cm^2
  double mass = 13000;
  std::vector <double> strain = {0.0020, 0.0045, 0.0060, 0.0013, 0.0085, 0.0005}; // x
  std::vector <double> stress = {4965, 5172, 5517, 3586, 6896, 1241}; // y

  // n is the size of the array that will be used throughout the code to
  // avoid using strain.size()
  int n = strain.size();

  // Setting up the vectors for all the summations and squares
  // needed for calculating the linear equation
  std::vector<double> x_y(n,0);
  std::vector<double> x_sqr(n,0);
  std::vector<double> y_sqr(n,0);
  std::vector <double> mod_elasticity (n,0);

  // squaring the values
  for (int i = 0; i < n; i++){
    x_sqr.at(i) = pow(strain.at(i), 2);
    y_sqr.at(i) = pow(stress.at(i), 2);
    x_y.at(i) = strain.at(i)*stress.at(i);
  }

  // doing all the summations
  double x_y_sum = 0;
  double x_sqr_sum = 0;
  double y_sqr_sum = 0;
  double x_sum = 0;
  double y_sum = 0;
  for (int i = 0; i < strain.size(); i++){
    x_y_sum = x_y_sum + x_y.at(i);
    x_sqr_sum = x_sqr_sum + x_sqr.at(i);
    y_sqr_sum = y_sqr_sum + y_sqr.at(i);
    x_sum = x_sum + strain.at(i);
    y_sum = y_sum + stress.at(i);
  }

  // calculating the constants A and B
  double a = 0;
  double b = 0;
  std::vector<double> l (n,0);
  a = ((y_sum * x_sqr_sum) - (x_sum*x_y_sum))/(n*x_sqr_sum - pow(x_sum, 2));
  b = (n*x_y_sum - x_sum*y_sum)/(n*x_sqr_sum - pow(x_sum, 2));
  std::cout << "The constatn A: " << a << std::endl << "The constant B: "<< b << std::endl;

  // Calculting the modulus of Elasticity
  for (int i = 0; i < strain.size(); i++){
    mod_elasticity.at(i) = stress.at(i)/strain.at(i);
  }
  std::cout << "The Modulus of Elasticity is: " << b << std::endl;

  // Calculating the elongation in the beams as a function of
  // beam number.
  std::vector<double> elongation;
  double elong_val;

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                     ELONGATION                      |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  for (int i = 0; i < 20; i++){
    elong_val = (mass*-9.81*length)/((i+1)*area*b);
    elongation.push_back(elong_val);
  }

  elongation_study (elongation, "elongation_study.dat");
  lin_reg (a, b, "lin_reg.dat");
  plot_points (strain, stress, "points.dat");
}
