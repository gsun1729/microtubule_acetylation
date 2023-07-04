#pragma once

class Particle {
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

    void PrintSelf() const;
};

