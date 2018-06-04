#pragma once

#include "BaseObject.h"

class Box : public BaseObject {
	protected:
		// Fields describing box's properties
    // Two vectors of three points each, one starting, one ending
		std::vector<float> start;
    std::vector<float> end;

	public:
		// Box is constructed with basic properties
		Box(std::vector<float> start, std::vector<float> end) : BaseObject("box"), start(start), end(end) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + getCoordinatesString(start) + " " + getCoordinatesString(end); }
};
