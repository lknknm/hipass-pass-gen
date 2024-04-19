#include <random>
#include "rand.h"
#include "lib/randutils.hpp"

extern "C" 
{
//----------------------------------------------------------------------------
// Random number generator that implements the randutils auto_seed_256 seed engine.
// More information on the seed engine in https://www.pcg-random.org/posts/simple-portable-cpp-seed-entropy.html
int random_nr(int min, int max) 
{
	std::uniform_int_distribution dist{min, max};
	static std::mt19937           engine{randutils::auto_seed_128{}.base()};
	return dist(engine);
}
}
