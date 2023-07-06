#include "simulation.hpp"
#include "config.hpp"

#include <iostream>

SimulationDriver::SimulationDriver(float timestep_size)
{
    timestep_size_ = timestep_size;
}

void SimulationDriver::generateSimulation()
{
    simulation_axis_.addHoles(config.num_dividers,
                              config.divider_width);
}
void SimulationDriver::preSeedAtHoles()
{
    for (const auto &hole : simulation_axis_.getHoles())
    {
        std::shared_ptr<Particle> new_particle = std::make_shared<Particle>(hole.getRandomPosition(),
                                                                            config.diffusion_coefficient,
                                                                            config.p_reaction);
        simulation_axis_.addParticle(new_particle);
    }
}

void SimulationDriver::printHoleLocations() const {
    std::cout << "Hole locations: \n";
    for(const auto& hole : simulation_axis_.getHoles()) {
        std::cout << hole.getCenterPosition() << "\n";
    }
}

void SimulationDriver::printParticleLocations() const {
    const auto& particles = simulation_axis_.getParticles();
    for(const auto& particle_ptr : particles) {
        std::cout << "Particle ID: " << particle_ptr->getId() 
                  << ", Position: " << particle_ptr->getPosition() 
                  << std::endl;
    }
}

void SimulationDriver::printMarkedLocations() const {
    for(const auto& location : marked_pts) {
        std::cout << "Marked location: " << location << std::endl;
    }
}
