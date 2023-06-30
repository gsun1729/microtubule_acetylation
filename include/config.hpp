#pragma	once

struct Config {
	const double microtubule_len = 0.1;
	const double diffusion_coefficient = 0.23;
	const double time_step = 0.1;
	const double p_entry = 0.1;
	const double p_exit = 0.1;
	const double p_reaction = 0.243;
	const double hole_len = 0.1;
	const int n_holes = 3;
};

extern const Config config;
