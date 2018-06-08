#pragma once

#include "BaseObject.h"
#include <iostream>

class Box : public BaseObject {
	protected:
		// Fields describing box's properties
		// Two vectors of three points each, one starting, one ending
		Data3D start;
		Data3D end;

	public:
		// Box is constructed with basic properties
		Box(Data3D start, Data3D end) : BaseObject("box"), start(start), end(end) { GeneratePoints(); }

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(start) + " " + GetCoordinatesString(end); }

		void GeneratePoints() {
			//Temporary access array
			const Data3D* arr[2] = { &start, &end };
			//Iterate over all points
			for (int i = 0; i < 8; ++i) {
				for (int j = i + 1; j < 8; ++j) {
					//Create a line if dimension diffrence == 1
					if (((i&1)^(j&1)) + (((i&2)>>1)^((j&2)>>1)) + (((i&4)>>2)^((j&4)>>2)) == 1) {
						Data3D temp(6);
						temp = {((*arr)[(i&1)])[0], ((*arr)[(i&2)>>1])[1], ((*arr)[(i&4)>>2])[2], ((*arr)[(j&1)])[0], ((*arr)[(j&2)>>1])[1], ((*arr)[(j&4)>>2])[2]};
						points.push_back(temp);
					}
				}
			}
		}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				start[i] += vec[i];
				end[i]   += vec[i];
			}
		}
};
