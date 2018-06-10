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
		Sphere() : BaseObject("sphere", false) {}
		// Sphere is constructed with basic properties
		Sphere(Data3D pos, float radius, unsigned int meridians, unsigned int parallels) : BaseObject("sphere"), radius(radius), pos(pos), meridians(meridians), parallels(parallels) {}

		// Each object has its own representation, this method supplements main representation printing method
		std::string Repr() const { return BaseObject::Repr() + GetCoordinatesString(pos) + " " + toString(radius); }

		void GeneratePoints() {}

		void MoveOrigins(Data3D vec) {
			for (int i = 0; i < 3; ++i) {
				pos[i] += vec[i];
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
		}

		Sphere* Copy() const {
			return new Sphere();
		}
};
