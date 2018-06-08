#pragma once

#include "BaseObject.h"

class Line : public BaseObject {
	protected:
		// Fields describing line's properties
		// Two vectors of three points each, one starting, one ending
		Data3D start;
		Data3D end;

	public:
		// Line is constructed with basic properties
		Line(Data3D start, Data3D end) : BaseObject("line"), start(start), end(end) { GeneratePoints(); }

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(start) + " " + GetCoordinatesString(end); }

		void GeneratePoints() {
			Data3D temp(6);
			temp = { start[0], start[1], start[2], end[0], end[1], end[2] };
			points.push_back(temp);
		}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				start[i] += vec[i];
				end[i]   += vec[i];
			}
		}
};
