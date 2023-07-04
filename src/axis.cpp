#include <iomanip>
#include "axis.hpp"
#include "probability.hpp"
#include "config.hpp"

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
void Hole::printPosition() const
{
	std::cout << "pos\t" << position_ << std::endl;
	std::cout << "range\t" << start_pos_ << "\t" << end_pos_ << std::endl;
}
void Hole::printProbability() const
{
	std::cout << "in\t" << influxProbability_ << "out\t" << efluxProbability_ << std::endl;
}

void Hole::printSelf() const
{
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << "pos\t" << position_ << "\t";
	std::cout << "width\t" << width_ << "\t";
	std::cout << "pIN\t" << influxProbability_ << "\t";
	std::cout << "pOUT\t" << efluxProbability_ << "\n";
}

Axis::Axis()
{
	length_ = config.axis_len;
	start_position_ = center_position_ - length_ / 2.0;
	end_position_ = center_position_ + length_ / 2.0;
}

Axis::Axis(float start_pos, float end_pos)
{
	length_ = end_pos - start_pos;
	center_position_ = (start_pos + end_pos) / 2.0;
	start_position_ = start_pos;
	end_position_ = end_pos;
}

void Axis::addHole(const Hole &hole)
{
	hole_list_.push_back(hole);
}

void Axis::addHoles(int num_holes, float hole_width)
{
	if (num_holes * hole_width > length_)
	{
		std::cout << "Number of holes and width exceeds length of axis" << std::endl;
		exit(0);
	}
	num_holes_ = num_holes;
	hole_width_ = hole_width;

	for (int i = 0; i < num_holes_; i++)
	{
		Hole newHole(start_position_ + (length_ * (i + 1) / (num_holes_ + 1)),
					 config.divider_width,
					 config.p_entry,
					 config.p_exit);
		this->addHole(newHole);
	}
}

void Axis::addHoles(float hole_width, float hole_separation, float seed_pos)
{
	hole_width_ = hole_width;
	hole_separation_ = hole_separation;

	float adder = 0.0;
	bool reach_front = false, reach_end = false;
	Hole newHole(seed_pos,
				 config.divider_width,
				 config.p_entry,
				 config.p_exit);
	this->addHole(newHole);
	adder += hole_width_ + hole_separation_;

	while (!(reach_front && reach_end))
	{
		reach_end = (seed_pos + adder + hole_width_ / 2) > end_position_;
		reach_front = (seed_pos - adder - hole_width_ / 2) < start_position_;
		if (!reach_front)
		{
			Hole newHole(seed_pos - adder,
						 config.divider_width,
						 config.p_entry,
						 config.p_exit);
			this->addHole(newHole);
		}
		if (!reach_end)
		{
			Hole newHole(seed_pos + adder,
						 config.divider_width,
						 config.p_entry,
						 config.p_exit);
			this->addHole(newHole);
		}
		adder += hole_width_ + hole_separation_;
	}
}

void Axis::addParticle(const Particle &particle)
{
	particle_list_.push_back(std::make_shared<Particle>(particle));
}

void Axis::rmParticle(const Particle &particle)
{
	particle_list_.erase(std::remove_if(particle_list_.begin(), particle_list_.end(),
										[&](const std::shared_ptr<Particle> &p)
										{
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

void Axis::printDimensions() const
{
	std::cout << "length\t" << length_ << std::endl;
	std::cout << "start\t" << start_position_ << std::endl;
	std::cout << "end\t" << end_position_ << std::endl;
	std::cout << "center\t" << center_position_ << std::endl;
}

void Axis::printHoleLocations() const
{
	for (const auto &h : hole_list_)
	{
		h.printSelf();
	}
}