#pragma once
#include "objects.hpp"
#include <vector>
#include <algorithm>
#include <memory>

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
    float getCenterPosition() const;
    float getRandomPosition() const;
    float getEFluxProb() const;
    float getInFluxProb() const;

};




class Axis {
    double length_;
    double start_position_;
    double end_position_;
    std::vector<Hole> hole_list_;
    std::vector<std::shared_ptr<Particle>> particle_list_;
public:
    Axis(double length);
    void addHole(const Hole& hole);
    void addParticle(const Particle& particle);
    void rmParticle(const Particle& particle);
    // move all particles along the axis
    void moveParticles(double dt); 
    // handle influx/eflux of particles in each hole
    void handleHoles(); 
};
