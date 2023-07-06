#include <vector>
#include <algorithm>
#include <memory>
#pragma once

class Particle
{
    float p_reaction_;
    float position_;
    float diff_coeff_;
    static int next_id_;
    int id_;

public:
    Particle();
    Particle(float pos, float diff_coeff, float p_reaction);
    int getId() const { return id_; }
    // move the particle according to its diffusion coefficient
    void Move(float dt);
    bool HasReacted();
    float getPosition() const;
    float getDiffusionCoeff() const;
    float getRxnProbability() const;
    void printSelf() const;
};

class Hole
{
    float position_;
    float width_;
    float start_pos_, end_pos_;
    float influxProbability_;
    float efluxProbability_;

public:
    Hole(float pos, float width, float influxProb, float efluxProb);
    // check if a given particle is inside this hole
    bool isParticleInside(const Particle &p);
    float getCenterPosition() const;
    float getWidth() const;
    float getRandomPosition() const;
    float getEFluxProb() const;
    float getInFluxProb() const;
    void printPosition() const;
    void printProbability() const;
    void printSelf() const;
};

class Axis
{
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
    bool isHoleDuplicate(const Hole&hole);
    void addHole(const Hole &hole);
    void addHoles(int num_holes, float hole_width);
    void addHoles(float hole_width, float hole_separation, float seed_pt);
    const std::vector<Hole>& getHoles() const;
    const std::vector<std::shared_ptr<Particle>>& getParticles() const;
    void addParticle(std::shared_ptr<Particle> particle);
    void rmParticle(std::shared_ptr<Particle> particle);
    // move all particles along the axis
    void moveParticles(float dt);
    // handle influx/eflux of particles in each hole
    void handleHoles();
    void printDimensions() const;
    void printHoleLocations() const;
    void printParticlePositions() const;
    void printAcetylationPoints() const;
};
