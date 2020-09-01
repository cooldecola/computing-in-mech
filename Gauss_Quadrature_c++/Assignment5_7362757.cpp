#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <math.h>
#include <functional>
#include <ctime>
#include <chrono>

using namespace std; 
// Using typedefs for all functions
using function_type = function<double(double)>;

auto gauss_weights(int n){
  vector<pair<double,double>> w; 
  if (n == 2){
    w.push_back(make_pair(-0.5773502691896257, 1.0000000000000000));
    w.push_back(make_pair(0.5773502691896257, 1.0000000000000000));
  }

  if (n == 3){
    w.push_back(make_pair(0.0000000000000000, 0.8888888888888888));
    w.push_back(make_pair(-0.7745966692414834, 0.5555555555555556));
    w.push_back(make_pair(0.7745966692414834, 0.5555555555555556));  
  }

  if (n == 4){
    w.push_back(make_pair(-0.3399810435848563, 0.6521451548625461));
    w.push_back(make_pair(0.3399810435848563, 0.6521451548625461));
    w.push_back(make_pair(-0.8611363115940526, 0.3478548451374538)); 
    w.push_back(make_pair(0.8611363115940526, 0.3478548451374538)); 
  }

  if (n == 5){
    w.push_back(make_pair(0.0000000000000000, 0.5688888888888889));
    w.push_back(make_pair(-0.5384693101056831, 0.4786286704993665));
    w.push_back(make_pair(0.5384693101056831, 0.4786286704993665));
    w.push_back(make_pair(-0.9061798459386640, 0.2369268850561891));
    w.push_back(make_pair(0.9061798459386640, 0.2369268850561891));
  }

  if (n == 6){
    w.push_back(make_pair(0.6612093864662645, 0.3607615730481386));
    w.push_back(make_pair(-0.6612093864662645, 0.3607615730481386));
    w.push_back(make_pair(-0.2386191860831969, 0.4679139345726910));
    w.push_back(make_pair(0.2386191860831969, 0.4679139345726910));
    w.push_back(make_pair(-0.9324695142031521, 0.1713244923791704));
    w.push_back(make_pair(0.9324695142031521, 0.1713244923791704));    
  }

  if (n == 7){
    w.push_back(make_pair(0.0000000000000000, 0.4179591836734694));
    w.push_back(make_pair(0.4058451513773972, 0.3818300505051189));
    w.push_back(make_pair(-0.4058451513773972, 0.3818300505051189));
    w.push_back(make_pair(-0.7415311855993945, 0.2797053914892766));
    w.push_back(make_pair(0.7415311855993945, 0.2797053914892766));
    w.push_back(make_pair(-0.9491079123427585, 0.1294849661688697));
    w.push_back(make_pair(0.9491079123427585, 0.1294849661688697));      
  }

  if (n == 8){
    w.push_back(make_pair(-0.1834346424956498, 0.3626837833783620));
    w.push_back(make_pair(0.1834346424956498, 0.3626837833783620));
    w.push_back(make_pair(-0.5255324099163290, 0.3137066458778873));
    w.push_back(make_pair(0.5255324099163290, 0.3137066458778873));
    w.push_back(make_pair(-0.7966664774136267, 0.2223810344533745));
    w.push_back(make_pair(0.7966664774136267, 0.2223810344533745));
    w.push_back(make_pair(-0.9602898564975363, 0.1012285362903763)); 
    w.push_back(make_pair(0.9602898564975363, 0.1012285362903763));      
  }

  if (n == 9){
    w.push_back(make_pair(0.0000000000000000, 0.3302393550012598));
    w.push_back(make_pair(-0.8360311073266358, 0.1806481606948574));
    w.push_back(make_pair(0.8360311073266358, 0.1806481606948574));
    w.push_back(make_pair(-0.9681602395076261, 0.0812743883615744));
    w.push_back(make_pair(0.9681602395076261, 0.0812743883615744));
    w.push_back(make_pair(-0.3242534234038089, 0.3123470770400029));
    w.push_back(make_pair(0.3242534234038089, 0.3123470770400029)); 
    w.push_back(make_pair(-0.6133714327005904, 0.2606106964029354)); 
    w.push_back(make_pair(0.6133714327005904, 0.2606106964029354));     
  }

  if (n == 10){
    w.push_back(make_pair(-0.1488743389816312, 0.2955242247147529));
    w.push_back(make_pair(0.1488743389816312, 0.2955242247147529));
    w.push_back(make_pair(-0.4333953941292472, 0.2692667193099963));
    w.push_back(make_pair(0.4333953941292472, 0.2692667193099963));
    w.push_back(make_pair(-0.6794095682990244, 0.2190863625159820));
    w.push_back(make_pair(0.6794095682990244, 0.2190863625159820));
    w.push_back(make_pair(-0.8650633666889845, 0.1494513491505806)); 
    w.push_back(make_pair(0.8650633666889845, 0.1494513491505806)); 
    w.push_back(make_pair(-0.9739065285171717, 0.0666713443086881));
    w.push_back(make_pair(0.9739065285171717, 0.0666713443086881));     
  }

  return w; 

}

double simposons_method (function_type f, double a, double b, double del_x, double n){
  double sum = f(a);

  for (int i = 0; i < n+1 ; i++){

    a = a + del_x;

    if (((i-1)%2)+1 == 1){
      sum = sum + 4*f(a);
    }

    if (((i-1)%2)+1 == 2){
      sum = sum + 2*f(a);
    }

  }

  sum = sum + f(b);
  return (del_x/3)*sum;
}

double guass_quad (function_type f, double iter){
  double sum = 0; 

  auto w = gauss_weights(iter); 

  for (int i = 0; i < iter; i++){
    sum = sum + f(w[i].first)*w[i].second;
  }

  sum = sum*150; 
  return sum; 

}


int main() {

  // The constants
  double a = -100;
  double b = 200;
  double n = 9000;
  double del_x = (b-a)/n;
  double num_of_iter = 5;


    // Functions for temprature 
    auto c = [](double t){
      return 0.132 + 1.56*pow(10,-4)*t + 2.64*pow(10,-7)*pow(t,2);
    };

    auto c_gauss = [](double t1){
      return 0.132 + 1.56*pow(10,-4)*(150*t1+150) + 2.64*pow(10,-7)*pow( (150*t1 + 150), 2);
    };

    // auto f = [](double x){
    //   return pow(x,2)*sin(x);
    // };

    // auto f_gauss = [](double x1){
    //   return pow((1.5*x1 + 1.5), 2)*sin((1.5*x1 + 1.5)); 
    // };

    cout << "------------------------------------------------------\n";
    cout << "------------------------------------------------------\n";
    cout << "|                 SIMPSONS METHOD                    |\n";
    cout << "------------------------------------------------------\n";
    cout << "------------------------------------------------------\n";

    double ans = simposons_method(c, a, b, del_x, n);

    cout << ans << '\n';

    cout << "------------------------------------------------------\n";
    cout << "------------------------------------------------------\n";
    cout << "|             GUASS-QUADRATURE METHOD                |\n";
    cout << "------------------------------------------------------\n";
    cout << "------------------------------------------------------\n";

    double ans_2 = guass_quad(c_gauss, num_of_iter);
    cout << ans_2 << '\n';

}
