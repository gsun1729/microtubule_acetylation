#include <string>
#pragma once

struct Config
{
    std::string filename = "testing_runs";
    std::string save_dir = "experiments";
    float axis_len = 50;                // microtubule length in um
    float diffusion_coefficient = 0.27; // aTAT1 diffusion 1D um2/s
    float timestep_size = 0.001;
    float stop_time = 300.0; // seconds
    float record_per_s = 60.0;
    bool record_frames{true};


    //Modifiable parameters
    float p_entry = 0.05;
    float p_exit = 0.05;

    float p_reaction = 0.03;
    float hole_width = 0.015; // defect size 10-20nm
    int num_holes = 3;

    float precision_epsilon = 0.001;
};
