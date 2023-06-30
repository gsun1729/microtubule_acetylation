#include<iostream>
#include "probability.hpp"
#include "config.hpp"
#include "objects.hpp"
#include "axis.hpp"
#include <stdexcept>
#include <iomanip>


int main(int argc, char *argv[]){
   // std::cout << config.diffusion_coefficient << std::endl;

   std::cout << "====="<<std::endl;

   Hole H = Hole(0, 1, 0,0);

   Particle p = Particle(2, 0.1, 0.1);

   bool p_inside_H = H.isParticleInside(p);
   std::cout<<p_inside_H<<std::endl;

   for (int i=0; i<10; i++){
      p.PrintSelf();
      p.Move(0.1);
}


   // std::cout << std::setprecision(5)<< std::fixed;
   // // }
   // float axis_len = 100;
   // float width = 1;
   // int n_holes = 5;
   // if (width * n_holes > axis_len){
   //    throw std::invalid_argument("axis cannot be all holes");
   // }

   // std::cout<<"Separation\t"<<axis_len/(n_holes+1)<<std::endl;
   // for (int i=0; i<n_holes; i++){
   //    float position = (axis_len/(n_holes+1))*(i+1);
   //    std::cout<<position<<"\t"<<position-width/2<<"\t"<<position + width/2<<std::endl;
   // }




   return 0;
   
}
