#include "axis.hpp"



Hole::Hole(double pos, double width, 
						double influxProb, double efluxProb){
	position_ = pos;
	width_ = width;
	influxProbability_ = influxProb;
	efluxProbability_ = efluxProb;
	start_pos_ = pos - (width/2.0);
	end_pos_ = pos + (width/2.0);
}

bool Hole::isParticleInside(const Particle& p){
	float particle_pos = p.getPosition();
	if (particle_pos >= start_pos_ && particle_pos<= end_pos_){
		return(true);
	} else { 
		return(false);
	}
}
