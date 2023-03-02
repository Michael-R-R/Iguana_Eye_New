#include "IERandomNumber.h"

int IERandomNumber::randInt(int lower, int upper)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

	return dist(generator);
}

double IERandomNumber::randDouble(double lower, double upper)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<double> dist(lower, upper);

	return dist(generator);
}

float IERandomNumber::randFloat(float lower, float upper)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<float> dist(lower, upper);

	return dist(generator);
}
