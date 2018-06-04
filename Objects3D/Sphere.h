#pragma once

#include "BaseObject.h"

class Sphere : public BaseObject {
	protected:
		// Fields describing sphere's properties
		float radius;
		// In pdf named as n and m
		unsigned int meridians;
		unsigned int parallels;
		std::vector<float> pos;

	public:
		// Sphere is constructed with basic properties
		Sphere(std::vector<float> pos, float radius, unsigned int meridians, unsigned int parallels) : BaseObject("sphere"), radius(radius), pos(pos), meridians(meridians), parallels(parallels) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + getCoordinatesString(pos) + " " + toString(radius); }
};
