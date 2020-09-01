#include <vector>
#include <utility>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <functional>

using function_type = std::function<double(double)>;

void output_solution(function_type solution, const std::string filename){
  std::ofstream fout(filename);
  if(!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  for (double t = 0; t < 180; t = t + 0.1){
    fout <<  t << " " << solution(t) << '\n';
    std::cout << t << " " << solution(t) << '\n';
  }
}

void output_to_file(const std::vector<double> ts, const std::vector<double> ys, const std::string filename){
  if (ts.size() != ys.size()){
    throw std::runtime_error("Vectors have different sizes");
  }

  std::ofstream fout(filename);
  if (!fout){
    throw std::runtime_error("Could not open file: " + filename);
  }

  for (int i = 0; i < ts.size(); ++i){
    fout << std::setw(30) << ts[i] << std::setw(30) << ys[i] << '\n';
    std::cout << std::setw(30) << ts[i] << std::setw(30) << ys[i] << '\n';
  }
}

auto forward_euler(double h0, double t, double h, double delta_t, int num, function_type ode){

  std::vector<double> times({0.0});
  std::vector<double> hs({h0});

  for (int i = 0; i < num; i++){
    h = h + delta_t * ode(h);
    t += delta_t;
    times.push_back(t);
    hs.push_back(h);
  }

  return std::make_pair(times, hs);
}

auto runge_kutta (double h0, double t, double h, double delta_t, int num, function_type ode){

  std::vector<double> times({0.0});
  std::vector<double> hs({h0});
  double k1, k2, k3, k4;

  for (int i = 0; i < num; i++){
    k1 = ode(h);
    k2 = ode(h + k1*delta_t/2);
    k3 = ode(h + k2*delta_t/2);
    k4 = ode(h + k3*delta_t);

    h = h + (delta_t*(k1 + 2*k2 + 2*k3 + k4))/6;
    t += delta_t;
    times.push_back(t);
    hs.push_back(h);
  }

  return std::make_pair(times, hs);
}

void pendulum(){
  double m1 = 2;
  double m2 = 0.1;
  double l = 0.5;
  double g = 9.81;
  double final_time = 30;
  int num = 1000;



  auto ode_theta = [](const double theta){
    return (2+0.1)*9.81*theta/(2*0.5) - sin(theta)/(2*0.5);
  };

  auto ode_x = [](const double x){
    return -0.1*9.81*x/2 + sin(x)/2;
  };

  double theta0 = 0.1;
  double x0 = 0.1;
  double t = 0.0;
  double theta = theta0;
  double x = x0;

  double delta_t = final_time/static_cast<double>(num);

  auto theta_result = forward_euler(theta0, t, theta, delta_t, num, ode_theta);
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                   THETA                            |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  output_to_file(theta_result.first, theta_result.second, "theta.dat");
  auto x_result = forward_euler(x0, t, x, delta_t, num, ode_x);
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                   X                                |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  output_to_file(x_result.first, x_result.second, "x.dat");
}


int main(){

  double final_time = 182;
  int num = 10;


  auto ode = [](const double h) {
    return (-sqrt(2*32.3)*0.25*pow(h, -1.5)) / (3.14*pow(0.4,2));
  };

  auto solution = [](const double t) {
    return pow(-2.5*sqrt(2*32.3)*0.25*t/(3.14*pow(0.4,2)) + pow(20, 2.5) , 0.4);
  };

  double h0 = solution(0.0);
  double t = 0.0;
  double h = h0;
  double delta_t = final_time/static_cast<double>(num);

  auto forward_euler_result = forward_euler(h0, t, h, delta_t, num, ode);
  auto runge_kutta_result = runge_kutta(h0, t, h, delta_t, num, ode);

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                    FORWARD EULER                   |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  output_to_file(forward_euler_result.first,forward_euler_result.second, "forward_euler.dat");

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                     RUNGE KUTTA                    |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  output_to_file(runge_kutta_result.first, runge_kutta_result.second, "runge_kutta.dat");

  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "|                      SOLUTION                      |\n";
  std::cout << "------------------------------------------------------\n";
  std::cout << "------------------------------------------------------\n";
  output_solution(solution, "solution.dat");

  pendulum();

}
