#pragma once
#include "objects.hpp"
#include <vector>
#include <algorithm>
#include <memory>

class Hole {
    float position_;
    float width_;
    float start_pos_, end_pos_;
    float influxProbability_;
    float efluxProbability_;
public:
    Hole(float pos, float width, float influxProb, float efluxProb);
    // check if a given particle is inside this hole
    bool isParticleInside(const Particle& p); 
    float getCenterPosition() const;
    float getRandomPosition() const;
    float getEFluxProb() const;
    float getInFluxProb() const;

};




class Axis {
    float length_;
    float start_position_;
    float end_position_;
    std::vector<Hole> hole_list_;
    std::vector<std::shared_ptr<Particle>> particle_list_;
public:
    Axis(float length);
    void addHole(const Hole& hole);
    void addParticle(const Particle& particle);
    void rmParticle(const Particle& particle);
    // move all particles along the axis
    void moveParticles(float dt); 
    // handle influx/eflux of particles in each hole
    void handleHoles(); 
};
