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

int main(int argc, char *argv[])
{
    Config configs;

    SimulationDriver sim{configs};
    sim.generateSimulation();

    // std::cout << config.diffusion_coefficient << std::endl;
        // std::cout << "=====" << std::endl;
        // SimulationDriver sim{config.time_step,
        //                      config.record_per_s};
        // sim.printSimulationHeader();
        // sim.generateSimulation();
        sim.printHoleLocations();
        sim.printParticleLocations();
        // sim.printMarkedLocations();
        sim.preSeedAtHoles();
        sim.runUntil(1.0);

        std::cout << "=====" << std::endl;
    sim.advance();
    sim.printTimestamp();
    sim.printHoleLocations();
    sim.printParticleLocations();
    // sim.printMarkedLocations();

    // sim.advance();
    // std::cout << "=====" << std::endl;
    // sim.printTimestamp();
    // sim.printHoleLocations();
    // sim.printParticleLocations();
    // sim.printMarkedLocations();
    // std::cout << "=====" << std::endl;
    // sim.runUntil(.05, false);
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

    return 0;
}
