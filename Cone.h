#pragma once

#include "BaseObject.h"

class Cone : public BaseObject {
	protected:
		// Fields describing cones's properties
		// Two vectors of three points each, one starting, one ending
		Data3D start;
		Data3D end;

		// Also two radiuses for two bases
		float radius1;
		float radius2;
			
		// And informations in how many tetragons cone has to be split
		unsigned int nTetragons;

	public:
		// Line is constructed with basic properties
		Cone(Data3D start, Data3D end, float radius1, float radius2, unsigned int nTetragons) : BaseObject("cone"), start(start), end(end), radius1(radius1), radius2(radius2), nTetragons(nTetragons) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(start) + " " + toString(radius1) + " " + GetCoordinatesString(end) + " " + toString(radius2); }

		void GeneratePoints() {}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				start[i] += vec[i];
				end[i]   += vec[i];
			}
		}
};
