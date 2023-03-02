#pragma once

#include <random>

class IERandomNumber
{

public:
    virtual ~IERandomNumber() { }

	static int randInt(int lower, int upper);
	static double randDouble(double lower, double upper);
	static float randFloat(float lower, float upper);
};

