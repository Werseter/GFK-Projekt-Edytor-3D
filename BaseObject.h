#pragma once

#include <vector>
#include <sstream>
#include "vecmat.h"

typedef std::vector<float>  Data3D;
typedef std::vector<Data3D> DataVector;

template <typename T> std::string toString(const T& n) {
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

// Base class describing 3D objects
class BaseObject {
	private:
		// Each object needs an id used in methods like "delete id"
		// Static counter is responsible for that
		static unsigned int idCounter;

	protected:
		// Each object has it's id number, type and list of 3D rendering points
		unsigned int objId;
		std::string type;
		DataVector points;

	public:
		// When creating an object a desired type must be given
		// Object initializes with id and a type
		BaseObject(std::string type) : objId(idCounter++), type(type) { }

		// Method returning cordinates in a string
		std::string GetCoordinatesString(Data3D v) const { return "(" + toString(v[0]) + ", " + toString(v[1]) + ", " + toString(v[2]) + ")"; }
		//Method returning rendering data
		const DataVector* GetData() const { return &points; }
		unsigned int GetId() const { return objId; }
		// Method for printing object's representation
		virtual std::string Repr() const { return toString(objId) + " " + type + " "; }

		// Method rotating an object
		void Rotate(Data3D pos, Data3D angles) {
			float angle;
			Matrix4 transform1;
			angle = angles[0] * acosf(-1) / 180;
			transform1.data[0][0] =  cos(angle);
			transform1.data[1][1] =  transform1.data[0][0];
			transform1.data[0][1] =  sin(angle);
			transform1.data[1][0] = -transform1.data[0][1];
			transform1.data[2][2] =  1;

			Matrix4 transform2;
			angle = angles[1] * acosf(-1) / 180;
			transform2.data[0][0] =  cos(angle);
			transform2.data[2][2] =  transform2.data[0][0];
			transform2.data[2][0] =  sin(angle);
			transform2.data[0][2] = -transform2.data[2][0];
			transform2.data[1][1] =  1;

			Matrix4 transform3;
			angle = angles[2] * acosf(-1) / 180;
			transform3.data[1][1] =  cos(angle);
			transform3.data[2][2] =  transform3.data[1][1];
			transform3.data[1][2] =  sin(angle);
			transform3.data[2][1] = -transform3.data[1][2];
			transform3.data[0][0] =  1;

			Matrix4 transform4;
			transform4.data[0][3] = pos[0];
			transform4.data[1][3] = pos[1];
			transform4.data[2][3] = pos[2];
			transform4.data[0][0] = transform4.data[1][1] = transform4.data[2][2] = 1;

			Matrix4 transform = transform4 * transform3 * transform2 * transform1;

			Vector4 pt1, pt2;
			for (Data3D& point : points) {
				pt1.Set(point[0], point[1], point[2]);
				pt2.Set(point[3], point[4], point[5]);
				pt1 = (transform * pt1).Normalize();
				pt2 = (transform * pt2).Normalize();
				for (int i = 0; i < 3; ++i) {
					point[i]     = pt1.data[i];
					point[i + 3] = pt2.data[i];
				}
			}
		}

		void Move(Data3D vec) {
			Matrix4 transform1;
			transform1.data[0][3] = vec[0];
			transform1.data[1][3] = vec[1];
			transform1.data[2][3] = vec[2];
			transform1.data[0][0] = transform1.data[1][1] = transform1.data[2][2] = 1;

			Vector4 pt1, pt2;
			for (Data3D& point : points) {
				pt1.Set(point[0], point[1], point[2]);
				pt2.Set(point[3], point[4], point[5]);
				pt1 = (transform1 * pt1).Normalize();
				pt2 = (transform1 * pt2).Normalize();
				for (int i = 0; i < 3; ++i) {
					point[i]     = pt1.data[i];
					point[i + 3] = pt2.data[i];
				}
			}
			MoveOrigins(vec);
		}

		virtual void MoveOrigins(Data3D vec) = 0;
		// Method converting object data into rendering points
		virtual void GeneratePoints() = 0;

};
