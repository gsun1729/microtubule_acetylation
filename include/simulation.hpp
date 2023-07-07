#include <vector>
#include <string>
#include <fstream>

#include "config.hpp"

#include "objects.hpp"
#pragma once

class SimulationDriver
{
    Config config_;
    std::string filename_;
    std::string simulation_time_stamp_header_;
    std::string simulation_save_dir_;
    static int simulation_number_;
    int sim_ID_;

    float axis_len_;
    float diffusion_coeff_;
    // Timestep size to advance per frame of the simulation
    float timestep_size_{0.0};
    /* Timestamp to capture simulation state for every X
    seconds in the simulation */
    float timestep_record_{0.0};
    float p_entry_, p_exit_;
    float p_reaction_;

    float hole_width_;
    int num_holes_;

    float stop_time_;
    bool record_frames_{false};
    bool end_holes_{false};
    float timestamp_{0.0};
    float precision_epsilon_;
    std::unique_ptr<Axis> simulation_axis_;

public:
    SimulationDriver(const Config &configs_struct);
    std::string getSimulationTimeStamp() const;
    void printSimulationHeader() const;
    void generateSimulation();
    void preSeedAtHoles();
    void advance();
    void runUntil(float stop_time);
    void runToStopTime();
    void saveMarkedPts2File(std::string save_path);
    float getTimestamp() const;
    void printTimestamp() const;
    void printHoleLocations() const;
    void printParticleLocations() const;
    void printMarkedLocations() const;
};