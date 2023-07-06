#include <string>
#pragma once

struct Config
{
    const std::string filename = "testing_runs";
    const float axis_len = 10;                // microtubule length in um
    const float diffusion_coefficient = 0.27; // aTAT1 diffusion 1D um2/s
    const float time_step = 0.01;
    const float p_entry = 0.00005;
    const float p_exit = 0.00005;
    const float p_reaction = 0.0000003;
    const float divider_width = 0.015; // defect size 10-20nm
    const int num_dividers = 3;
    const float stop_time = 300.0; // seconds
};

extern const Config config;
