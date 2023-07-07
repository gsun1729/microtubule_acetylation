#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <vector>

#include "probability.hpp"
#include "config.hpp"
#include "objects.hpp"
#include "simulation.hpp"

void runSimulation(const Config &config, int iter)
{
    SimulationDriver sim{config};
    sim.generateSimulation();
    sim.preSeedAtHoles();
    sim.runToStopTime();
}

int main(int argc, char *argv[])
{
    std::vector<Config> config_list;

    for (float hole_width : {0.01, 0.015, 0.02})
    {
        for (int num_holes : {0, 1, 3, 7, 15, 31, 63})
        {
            for (float p_reaction : {0.00001, 0.0001})//, 0.001, 0.01})
            {
                Config sub_config;
                sub_config.hole_width = hole_width;
                sub_config.num_holes = num_holes;
                sub_config.p_reaction = p_reaction;
                config_list.push_back(sub_config);
            }
        }
    }
    unsigned int max_threads = std::thread::hardware_concurrency(); // number of cores
    std::vector<std::thread> threads;

    for (const Config &sub_config : config_list)
    {
        for (int i = 0; i <=1; i++)
        {
            // Wait for a free core if all are busy.
            if (threads.size() >= max_threads)
            {
                for (auto &thread : threads)
                {
                    thread.join();
                }
                threads.clear();
            }

            threads.push_back(std::thread(runSimulation, sub_config, i));
        }
    }
    // Wait for the remaining threads to finish.
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}
// Config config;
// config.num_holes=0;
// SimulationDriver sim{config};
// std::cout << "=====" << std::endl;
// sim.printTimestamp();
// sim.printHoleLocations();
// sim.printParticleLocations();
// std::cout << "=====" << std::endl;
// sim.generateSimulation();
// sim.preSeedAtHoles();
// std::cout << "=====" << std::endl;
// sim.printTimestamp();
// sim.printHoleLocations();
// sim.printParticleLocations();
// sim.printMarkedLocations();
// std::cout << "=====" << std::endl;
// Axis a;
// a.printDimensions();
// std::cout << "=====" << std::endl;
// a.addHoles(1.0,1.0,0.0);
// a.printHoleLocations();
// a.addHoles(1,1.0);
// std::cout<<std::endl;
// a.addHoles(3,1.0);
// std::cout<<std::endl;
// a.addHoles(7,1.0);
// a.printHoleLocations();
// std::cout << "=====" << std::endl;

// std::vector<std::shared_ptr<Particle>> particles(10);

// srand(time(NULL));
// float rand_pos;
// for (auto &particle : particles)
// {
// 	rand_pos = rand() / double(RAND_MAX);
// 	particle = std::make_shared<Particle>(rand_pos, 0.1, 0.1);
// 	std::cout << particle->getId() << "\t" << particle->getPosition() << std::endl;
// }

// for (auto &particle : particles)
// {
// 	particle->Move(0.1);
// 	std::cout << particle->getPosition() << std::endl;
// }

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

// return 0;
// }
