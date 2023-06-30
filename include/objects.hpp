#pragma once

class Particle {
    bool has_reacted_;
    double p_reaction_;
    double position_;
    double diff_coeff_;
    static int next_id;
    int id_;
public:
    Particle();
    Particle(double pos, double diff_coeff, double p_reaction);
    int getId() const { return id_; }
    // move the particle according to its diffusion coefficient
    void Move(double dt); 
    
    
    bool HasReacted(); 

    double getPosition() const;

    double ReturnDiffusionCoeff();

    void PrintSelf();
};

