#pragma once

#include "BaseObject.h"

class Cylinder : public BaseObject {
	protected:
		// Fields describing cylinder's properties
		// Two vectors of three points each, one starting, one ending
		Data3D start;
		Data3D end;

		// Radius for the bases
		float radius;

		// And informations in how many tetragons cyinder has to be split
		unsigned int nTetragons;

	public:
		// Line is constructed with basic properties
		Cylinder(Data3D start, Data3D end, float radius, unsigned int nTetragons) : BaseObject("cylinder"), start(start), end(end), radius(radius), nTetragons(nTetragons) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(start) + " " + GetCoordinatesString(end) + " " + toString(radius); }

		void GeneratePoints() {}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				start[i] += vec[i];
				end[i]   += vec[i];
			}
		}
};
