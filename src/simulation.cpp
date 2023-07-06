#include "simulation.hpp"
#include "config.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cmath>

SimulationDriver::SimulationDriver(const Config &configs_struct)
{

    config_ = configs_struct;
    filename_ = config_.filename;
    simulation_save_dir_ = config_.save_dir;

    // Generate simulation timestamp identifier
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

    axis_len_ = config_.axis_len;
    diffusion_coeff_ = config_.diffusion_coefficient;
    timestep_size_ = config_.timestep_size;
    timestep_record_ = config_.record_per_s;
    p_entry_ = config_.p_entry;
    p_exit_ = config_.p_exit;
    p_reaction_ = config_.p_reaction;
    num_holes_ = config_.num_holes;
    hole_width_ = config_.hole_width;
    precision_epsilon_ = config_.precision_epsilon;

    // add parameter values to filename
    filename_ += "_nH" + std::to_string(num_holes_);
    filename_ += "_w" + std::to_string(hole_width_);
    filename_ += "_pRX" + std::to_string(p_reaction_);
    filename_ += "_pI" + std::to_string(p_entry_);
    filename_ += "_pO" + std::to_string(p_exit_);
    std::cout << filename_ << std::endl;

    // simulation_axis_(axis_len_, p_reaction_, diffusion_coeff_);
    simulation_axis_ = std::make_unique<Axis>(axis_len_, p_reaction_, diffusion_coeff_);

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
    simulation_axis_->addHoles(num_holes_,
                              hole_width_,
                              p_entry_, p_exit_);
}
void SimulationDriver::preSeedAtHoles()
{
    for (const auto &hole : simulation_axis_->getHoles())
    {
        std::shared_ptr<Particle> new_particle = std::make_shared<Particle>(hole.getRandomPosition(),
                                                                            diffusion_coeff_,
                                                                            p_reaction_);
        simulation_axis_->addParticle(new_particle);
    }
}

void SimulationDriver::printHoleLocations() const
{
    std::cout << "Hole locations: \n";
    for (const auto &hole : simulation_axis_->getHoles())
    {
        std::cout << hole.getCenterPosition() << "\n";
    }
}

void SimulationDriver::printParticleLocations() const
{
    const auto &particles = simulation_axis_->getParticles();
    for (const auto &particle_ptr : particles)
    {
        std::cout << "Particle ID: " << particle_ptr->getId()
                  << ", Position: " << particle_ptr->getPosition()
                  << std::endl;
    }
}

void SimulationDriver::printMarkedLocations() const
{
    const std::vector<float> &marked_pts = simulation_axis_->getMarkedPts();
    for (const auto &location : marked_pts)
    {
        std::cout << location << std::endl;
        // << "Marked location: "
    }
}

void SimulationDriver::saveMarkedPts2File(std::string save_path)
{
    std::cout << save_path << std::endl;
    std::ofstream outfile(save_path);
    if (outfile.is_open())
    {

        const std::vector<float> &marked_pts = simulation_axis_->getMarkedPts();
        for (const auto &location : marked_pts)
        {
            outfile << location << std::endl;
        }
        outfile.close();
    }
    else
    {
        std::cout << "Unable to open file: " << save_path << std::endl;
    }
}

void SimulationDriver::advance()
{
    simulation_axis_->moveParticles(timestep_size_);
    simulation_axis_->reactParticles();
    simulation_axis_->handleHoles();
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

void SimulationDriver::runUntil(float stop_time)
{
    while (timestamp_ < stop_time)
    {
        advance();
        if (record_frames_ && (std::fabs(std::remainder(timestamp_, timestep_record_)) < precision_epsilon_))
        {
            std::cout << "OK2 " << timestamp_ << std::endl;
            std::string filename = getSimulationTimeStamp() + "_" + filename_ + "_" + std::to_string(timestamp_) + ".txt";
            saveMarkedPts2File(filename);
        }
    }
}


void SimulationDriver::runToStopTime()
{
    while (timestamp_ < stop_time_)
    {
        advance();
        if (record_frames_ && (std::fabs(std::remainder(timestamp_, timestep_record_)) < precision_epsilon_))
        {
            std::cout << "OK2 " << timestamp_ << std::endl;
            std::string filename = getSimulationTimeStamp() + "_" + filename_ + "_" + std::to_string(timestamp_) + ".txt";
            saveMarkedPts2File(filename);
        }
    }
}
