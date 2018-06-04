#pragma once

#include "BaseObject.h"

class Line : public BaseObject {
	protected:
		// Fields describing line's properties
    // Two vectors of three points each, one starting, one ending
		std::vector<float> start;
    std::vector<float> end;

	public:
		// Line is constructed with basic properties
		Line(std::vector<float> start, std::vector<float> end) : BaseObject("line"), start(start), end(end) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + getCoordinatesString(start) + " " + getCoordinatesString(end); }
};
