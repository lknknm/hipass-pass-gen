#include <random>
#include "rand.h"

extern "C" {
int random_nr(int min, int max) {
	std::uniform_int_distribution dist{min, max};
	static std::random_device     device;
	static std::mt19937           engine{device()}; // seed engine
	return dist(engine);
}
}
