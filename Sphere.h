#pragma once

#include "BaseObject.h"

class Sphere : public BaseObject {
	protected:
		// Fields describing sphere's properties
		float radius;
		// In pdf named as n and m
		unsigned int meridians;
		unsigned int parallels;
		Data3D pos;

	public:
		Sphere() : BaseObject("sphere") {}
		// Sphere is constructed with basic properties
		Sphere(Data3D pos, float radius, unsigned int meridians, unsigned int parallels) : BaseObject("sphere"), radius(radius), pos(pos), meridians(meridians), parallels(parallels) { GeneratePoints(); }

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(pos) + " " + toString(radius); }

		void GeneratePoints() {
			const float PI = acosf(-1);
			float diff_1 = PI / meridians;
			float diff_2 = PI / parallels;

			for (float phi = 0.0; phi < 2 * PI; phi += PI / meridians) {
				for (float theta = 0.0; theta < PI; theta += PI / parallels) {
					Data3D temp(6);
					temp[0] = radius * cosf(phi) * sinf(theta) + pos[0];
					temp[1] = radius * sinf(phi) * sinf(theta) + pos[1];
					temp[2] = radius * cosf(theta) + pos[2];
					temp[3] = radius * cosf(phi + diff_1) * sinf(theta + diff_2) + pos[0];
					temp[4] = radius * sinf(phi + diff_1) * sinf(theta + diff_2) + pos[1];
					temp[5] = radius * cosf(theta + diff_2) + pos[2];
					points.push_back(temp);
				}
			}
		}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				pos[i] += vec[i];
			}
		}

		void RotationShift(Matrix4 transform) {
			Vector4 pt;
			pt.Set(pos[0], pos[1], pos[2]);
			pt = transform * pt - pt;
			for (int i = 0; i < 3; ++i) {
				pos[i] += pt.data[i];
			}
		}

		std::string GetSaveData() const {
			std::stringstream data;
			data << BaseObject::GetSaveData();
			for (float x : pos) data << x << " ";
			data << radius << " " << meridians << " " << parallels;
			data << std::endl;
			return data.str();
		}

		void SetData(std::string rotationsString, std::string dataString) {
			BaseObject::SetData(rotationsString, dataString);
			std::stringstream ss(dataString);
			pos = Data3D(3);
			for (int i = 0; i < 3; ++i) {
				ss >> pos[i];
			}
			ss >> radius >> meridians >> parallels;
			GeneratePoints();
			Rotate(rotations);
		}

		Sphere* Copy() const {
			return new Sphere();
		}
};
