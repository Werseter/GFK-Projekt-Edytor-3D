#pragma once
#include <stdio.h>

class Vector4 {
	public:
		double data[4];
		Vector4();
		void Print() const;
		void Set(double d1, double d2, double d3);
		double GetX() const;
		double GetY() const;
		double GetZ() const;
		Vector4 operator-(const Vector4&) const;
		Vector4& Normalize();
		friend Vector4 operator*(const Vector4&, double);
};

class Matrix4 {
	public:
		double data[4][4];
		Matrix4();
		void Print() const;
		Matrix4 operator*(const Matrix4&) const;
		friend Vector4 operator*(const Matrix4&, const Vector4&);
};
