#pragma once
#include "objects.hpp"
#include <vector>


class Hole {
    double position_;
    double width_;
    double start_pos_, end_pos_;
    double influxProbability_;
    double efluxProbability_;
public:
    Hole(double pos, double width, double influxProb, double efluxProb);
    // check if a given particle is inside this hole
    bool isParticleInside(const Particle& p); 
    // determine if a particle in this hole should exit the axis
    bool shouldExit(); 
    // determine if a new particle should enter the axis
    bool shouldInflux(); 
};




class Axis {
    double length;
    std::vector<Hole> holes;
    std::vector<Particle> particles;
public:
    Axis(double length);
    void addHole(const Hole& hole);
    void addParticle(const Particle& particle);
    // move all particles along the axis
    void moveParticles(); 
    // handle influx/eflux of particles in each hole
    void handleHoles(); 
};
