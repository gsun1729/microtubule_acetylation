#pragma once

class Particle {
    bool has_reacted_;
    double p_reaction_;
    double position_;
    double diff_coeff_;
public:
    Particle();
    Particle(double pos, double diff_coeff, double p_reaction);
    // move the particle according to its diffusion coefficient
    void Move(double dt); 
    // make the particle blink with a certain probability
    bool HasReacted(); 

    double getPosition() const;

    double ReturnDiffusionCoeff();

    void PrintSelf();
};

