#include "simulation.hpp"
#include "config.hpp"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

SimulationDriver::SimulationDriver(float timestep_size, float timestep_record)
    : timestep_size_{timestep_size}, timestep_record_{timestep_record}
{
    // Get the current time
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);

    // Generate the timestamp string
    std::stringstream ss;
    ss << std::put_time(tm, "%Y%m%d%H%M%S");

    // Append milliseconds
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
    ss << std::setfill('0') << std::setw(5) << millis;

    // Store the timestamp
    simulation_time_stamp_header_ = ss.str();
}

std::string SimulationDriver::getSimulationTimeStamp() const
{
    return simulation_time_stamp_header_;
}

void SimulationDriver::printSimulationHeader() const
{
    std::cout << simulation_time_stamp_header_ << std::endl;
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

void SimulationDriver::printHoleLocations() const
{
    std::cout << "Hole locations: \n";
    for (const auto &hole : simulation_axis_.getHoles())
    {
        std::cout << hole.getCenterPosition() << "\n";
    }
}

void SimulationDriver::printParticleLocations() const
{
    const auto &particles = simulation_axis_.getParticles();
    for (const auto &particle_ptr : particles)
    {
        std::cout << "Particle ID: " << particle_ptr->getId()
                  << ", Position: " << particle_ptr->getPosition()
                  << std::endl;
    }
}

void SimulationDriver::printMarkedLocations() const
{
    const std::vector<float>& marked_pts = simulation_axis_.getMarkedPts();
    for (const auto &location : marked_pts)
    {
        std::cout  << location << std::endl;
        // << "Marked location: "
    }
}

// void SimulationDriver::saveMarkedPts2File(std::string save_path)
// {
//     std::ofstream outfile(save_path);
//     if (outfile.is_open())
//     {
//         for (const auto &point : marked_pts)
//         {
//             outfile << point << std::endl;
//         }
//         outfile.close();
//     }
//     else
//     {
//         std::cout << "Unable to open file: " << save_path << std::endl;
//     }
// }

void SimulationDriver::advance()
{
    simulation_axis_.moveParticles(timestep_size_);
    simulation_axis_.reactParticles();
    simulation_axis_.handleHoles();
    timestamp_ += timestep_size_;
}

float SimulationDriver::getTimestamp() const
{
    return timestamp_;
}

void SimulationDriver::printTimestamp() const
{
    std::cout << "Timestamp: \t" << timestamp_ << std::endl;
}

void SimulationDriver::runUntil(float stop_time, bool record_frames)
{
    while (timestamp_ < stop_time)
    {
        advance();
        timestamp_ += timestep_size_;

        // if (record_frames && ((int)timestamp_ % (int)timestep_record_ == 0))
        // {
        //     std::string filename = getSimulationTimeStamp() + "_" + config.filename + "_" + std::to_string(timestamp_) + ".txt";
        //     saveMarkedPts2File(filename);
        // }
    }
}