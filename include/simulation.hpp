#include <vector>
#include <string>

#include "objects.hpp"
#pragma once


class SimulationDriver
{
    float timestep_size_{0.0};
    Axis simulation_axis_;
    std::vector<float> marked_pts;
public:
    SimulationDriver(float timestep_size);
    void generateSimulation();
    void preSeedAtHoles();
    void advance();
    void runUntil();
    void saveMarkedPts2File(std::string save_path);
    void printHoleLocations() const;
    void printParticleLocations() const;
    void printMarkedLocations() const;

};