#include <iostream>
#include "probability.hpp"
#include "config.hpp"
#include "objects.hpp"
#include "axis.hpp"
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <thread>
#include <stdlib.h>
class Simulation
{
public:
   void test()
   {
      Hole H = Hole(0, 0.5, 0, 0);
      float rand_pos = rand() / double(RAND_MAX);
      Particle p = Particle(rand_pos, 0.1, 0.1);

      bool p_inside_H = H.isParticleInside(p);
      std::cout << "in\t" << p_inside_H << std::endl;
   }
};

int main(int argc, char *argv[])
{
   // std::cout << config.diffusion_coefficient << std::endl;

   std::cout << "=====" << std::endl;

   std::vector<std::shared_ptr<Particle>> particles(10);

   srand(time(NULL));
   float rand_pos;
   for (auto &particle : particles)
   {
      rand_pos = rand() / double(RAND_MAX);
      particle = std::make_shared<Particle>(rand_pos, 0.1, 0.1);
      std::cout << particle->getId() << "\t" << particle->getPosition() << std::endl;
   }

   for (auto &particle : particles)
   {
      particle->Move(0.1);
      std::cout << particle->getPosition() << std::endl;
   }

   Particle test = Particle(0,0,0.5);
   for (int i = 0; i < 20; i ++){
      std::cout<<test.HasReacted()<<std::endl;
   }

   return 0;
   // std::vector<std::thread> threads;

   // for (int i = 0; i <= 5; i++)
   // {
   //    Simulation *sim = new Simulation();

   //    threads.push_back(std::thread(&Simulation::test, sim));
   // }

   // for (auto &thread : threads)
   // {
   //    thread.join();
   // }

   return 0;
}
