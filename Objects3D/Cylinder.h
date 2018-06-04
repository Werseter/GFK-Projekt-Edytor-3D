#pragma once

#include "BaseObject.h"

class Cylinder : public BaseObject {
	protected:
		// Fields describing cylinder's properties
		// Two vectors of three points each, one starting, one ending
		std::vector<float> start;
		std::vector<float> end;

		// Radius for the bases
		float radius;

		// And informations in how many tetragons cyinder has to be split
		unsigned int nTetragons;

	public:
		// Line is constructed with basic properties
		Cylinder(std::vector<float> start, std::vector<float> end, float radius, unsigned int nTetragons) : BaseObject("cylinder"), start(start), end(end), radius(radius), nTetragons(nTetragons) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + getCoordinatesString(start) + " " + getCoordinatesString(end) + " " + toString(radius); }
};
