#include <vector>
#include <string>
#include <fstream>

#include "objects.hpp"
#pragma once

class SimulationDriver
{
    // Timestep size to advance per frame of the simulation
    float timestep_size_{0.0};
    /* Timestamp to capture simulation state for every X
    seconds in the simulation */
    float timestep_record_{0.0};

    float timestamp_{0.0};

    std::string simulation_time_stamp_header_;
    Axis simulation_axis_;

public:
    SimulationDriver(float timestep_size, float timestep_record);
    std::string getSimulationTimeStamp() const;
    void printSimulationHeader() const;
    void generateSimulation();
    void preSeedAtHoles();
    void advance();
    void runUntil(float stop_time, bool record_frames);
    void saveMarkedPts2File(std::string save_path);
    float getTimestamp() const;
    void printTimestamp() const;
    void printHoleLocations() const;
    void printParticleLocations() const;
    void printMarkedLocations() const;
};