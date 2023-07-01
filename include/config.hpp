#pragma	once

struct Config {
	const float microtubule_len = 0.1;
	const float diffusion_coefficient = 0.23;
	const float time_step = 0.1;
	const float p_entry = 0.1;
	const float p_exit = 0.1;
	const float p_reaction = 0.243;
	const float divider_width = 0.1;
	const int num_dividers = 3;
};

extern const Config config;
