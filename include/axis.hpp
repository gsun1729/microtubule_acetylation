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
    void printPosition()const;
    void printProbability()const;
    void printSelf() const;
};




class Axis {
    float length_;
    float start_position_;
    float end_position_;
    float center_position_{0};

    int num_holes_{-1};
    float hole_width_{-1};
    float hole_separation_{-1};

    std::vector<Hole> hole_list_;
    std::vector<std::shared_ptr<Particle>> particle_list_;

public:
    Axis();
    Axis(float start_pos, float end_pos);
    void addHole(const Hole& hole);
    void addHoles(int num_holes, float hole_width);
    void addHoles(float hole_width, float hole_separation, float seed_pt);
    void addParticle(const Particle& particle);
    void rmParticle(const Particle& particle);
    // move all particles along the axis
    void moveParticles(float dt); 
    // handle influx/eflux of particles in each hole
    void handleHoles(); 
    void printDimensions()const;
    void printHoleLocations() const ;
    void printAcetylationPoints();
};
