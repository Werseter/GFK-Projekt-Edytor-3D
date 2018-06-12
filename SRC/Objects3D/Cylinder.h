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
		Cylinder() : BaseObject("cylinder") {}
		// Line is constructed with basic properties
		Cylinder(Data3D start, Data3D end, float radius, unsigned int nTetragons) : BaseObject("cylinder"), start(start), end(end), radius(radius), nTetragons(nTetragons) { GeneratePoints(); }

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(start) + " " + GetCoordinatesString(end) + " " + toString(radius); }

		void GeneratePoints() {
			float slice = 2 * acosf(-1) / nTetragons;
			DataVector tops(nTetragons);
			DataVector bots(nTetragons);
			for (unsigned int i = 0; i < nTetragons; ++i) {
				tops[i] ={ end[0] + radius * cosf(slice * i), end[1]  , end[2] + radius * sinf(slice * i) };
				bots[i] ={ start[0] + radius * cosf(slice * i), start[1], start[2] + radius * sinf(slice * i) };
			}
			for (unsigned int i = 0; i < nTetragons; ++i) {
				Data3D temp(6);
				temp ={ tops[i][0], tops[i][1], tops[i][2], tops[(i + 1) % nTetragons][0],  tops[(i + 1) % nTetragons][1],  tops[(i + 1) % nTetragons][2] };
				points.push_back(temp);
				temp ={ bots[i][0], bots[i][1], bots[i][2], bots[(i + 1) % nTetragons][0],  bots[(i + 1) % nTetragons][1],  bots[(i + 1) % nTetragons][2] };
				points.push_back(temp);
				temp ={ bots[i][0], bots[i][1], bots[i][2], tops[i][0], tops[i][1], tops[i][2] };
				points.push_back(temp);
			}
		}
		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				start[i] += vec[i];
				end[i]   += vec[i];
			}
		}

		void RotationShift(Matrix4 transform) {
			Vector4 pt, pt2;
			pt.Set(start[0], start[1], start[2]);
			pt = transform * pt - pt;
			pt2.Set(end[0], end[1], end[2]);
			pt2 = transform * pt2 - pt2;
			for (int i = 0; i < 3; ++i) {
				start[i] += pt.data[i];
				end[i]   += pt2.data[i];
			}
		}

		std::string GetSaveData() const {
			std::stringstream data;
			data << BaseObject::GetSaveData();
			for (float x : start) data << x << " ";
			for (float x : end) data << x << " ";
			data << radius << " " << nTetragons;
			data << std::endl;
			return data.str();
		}

		void SetData(std::string rotationsString, std::string dataString) {
			BaseObject::SetData(rotationsString, dataString);
			std::stringstream ss(dataString);
			start = Data3D(3);
			end   = Data3D(3);
			for (int i = 0; i < 3; ++i) {
				ss >> start[i];
			}
			for (int i = 0; i < 3; ++i) {
				ss >> end[i];
			}
			ss >> radius >> nTetragons;
			GeneratePoints();
			Rotate(rotations);
		}

		Cylinder* Copy() const {
			return new Cylinder();
		}
};
