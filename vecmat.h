#pragma once
#include <stdio.h>

class Vector4 {
	public:
		float data[4];
		Vector4();
		void Print() const;
		void Set(float d1, float d2, float d3);
		float GetX() const;
		float GetY() const;
		float GetZ() const;
		Vector4 operator-(const Vector4&) const;
		Vector4& Normalize();
		friend Vector4 operator*(const Vector4&, float);
};

class Matrix4 {
	public:
		float data[4][4];
		Matrix4();
		void Print() const;
		Matrix4 operator*(const Matrix4&) const;
		friend Vector4 operator*(const Matrix4&, const Vector4&);
};
