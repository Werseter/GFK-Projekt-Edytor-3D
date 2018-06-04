#pragma once

#include "BaseObject.h"

class Cone : public BaseObject {
	protected:
		// Fields describing cones's properties
    // Two vectors of three points each, one starting, one ending
		std::vector<float> start;
    std::vector<float> end;

    // Also two radiuses for two bases
    float radius1;
    float radius2;
		
    // And informations in how many tetragons cone has to be split
    unsigned int nTetragons;

	public:
		// Line is constructed with basic properties
		Cone(std::vector<float> start, std::vector<float> end, float radius1, float radius2, unsigned int nTetragons) : BaseObject("cone"), start(start), end(end), radius1(radius1), radius2(radius2), nTetragons(nTetragons) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + getCoordinatesString(start) + " " + toString(radius1) + " " + getCoordinatesString(end) + " " + toString(radius2); }
};
