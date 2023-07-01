#include "axis.hpp"
#include "probability.hpp"

Hole::Hole(float pos, float width,
		   float influxProb, float efluxProb)
{
	position_ = pos;
	width_ = width;
	influxProbability_ = influxProb;
	efluxProbability_ = efluxProb;
	start_pos_ = pos - (width / 2.0);
	end_pos_ = pos + (width / 2.0);
}

bool Hole::isParticleInside(const Particle &p)
{
	float particle_pos = p.getPosition();
	if (particle_pos >= start_pos_ && particle_pos <= end_pos_)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

float Hole::getCenterPosition() const
{
	return position_;
}

float Hole::getRandomPosition() const
{
	float pos_ratio = sampleUniformDistribution();
	return (width_ * pos_ratio - (width_ / 2.0));
}

float Hole::getEFluxProb() const
{
	return efluxProbability_;
}
float Hole::getInFluxProb() const
{
	return influxProbability_;
}
Axis::Axis(float length)
{
	length_ = length;
	start_position_ = 0;
	end_position_ = length;
}

void Axis::addHole(const Hole &hole)
{
	hole_list_.push_back(hole);
}

void Axis::addParticle(const Particle &particle)
{
	particle_list_.push_back(std::make_shared<Particle>(particle));
}

void Axis::rmParticle(const Particle &particle)
{
    particle_list_.erase(std::remove_if(particle_list_.begin(), particle_list_.end(),
                                        [&](const std::shared_ptr<Particle>& p) {
                                            return p->getId() == particle.getId();
                                        }),
                         particle_list_.end());
}

void Axis::moveParticles(float dt)
{
	for (auto &p : particle_list_)
	{
		p->Move(dt);
	}
}

void Axis::handleHoles()
{
	for (auto &hole : hole_list_)
	{
		if (isRandomSampleGreaterThanValue(hole.getInFluxProb()))
		{
			addParticle(Particle(hole.getRandomPosition(), /*diff_coeff=*/0.1, /*p_reaction=*/0.1));
		}

		for (auto it = particle_list_.begin(); it != particle_list_.end();)
		{
			auto &p = *it;
			if (hole.isParticleInside(*p) && isRandomSampleGreaterThanValue(hole.getEFluxProb()))
			{
				it = particle_list_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}
