#include "vecmat.h"

Vector4::Vector4() {
	data[0] = data[1] = data[2] = 0.0;
	data[3] = 1.0;
}

void Vector4::Print() const {
	printf("(%2.3lf,%2.3lf,%2.3lf,%2.3lf)", data[0], data[1], data[2], data[3]);
}

void Vector4::Set(float d1, float d2, float d3) {
 data[0] = d1;
 data[1] = d2;
 data[2] = d3;
}

float Vector4::GetX() const {
	return data[0];
}

float Vector4::GetY() const {
	return data[1];
}

float Vector4::GetZ() const {
	return data[2];
}

Vector4& Vector4::Normalize() {
	data[0] /= data[3];
	data[1] /= data[3];
	data[2] /= data[3];
	data[3] = 1;
	return *this;
}

Vector4 Vector4::operator- (const Vector4& gVector) const {
	Vector4 Result;
	for (int i = 0; i < 4; ++i) {
		Result.data[i] = data[i] - gVector.data[i];
	}
	return Result;
}

Vector4 operator* (const Vector4& gVector, float val) {
	Vector4 Result;
	for (int i = 0; i < 4; ++i) {
		Result.data[i] = gVector.data[i] * val;
	}
	return Result;
}

Matrix4::Matrix4() {
 data[0][0] = 0.0; data[0][1] = 0.0; data[0][2] = 0.0; data[0][3] = 0.0;
 data[1][0] = 0.0; data[1][1] = 0.0; data[1][2] = 0.0; data[1][3] = 0.0;
 data[2][0] = 0.0; data[2][1] = 0.0; data[2][2] = 0.0; data[2][3] = 0.0;
 data[3][0] = 0.0; data[3][1] = 0.0; data[3][2] = 0.0; data[3][3] = 1.0;
}

void Matrix4::Print() const {
 printf("\n|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[0][0], data[0][1], data[0][2], data[0][3]);
 printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[1][0], data[1][1], data[1][2], data[1][3]);
 printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[2][0], data[2][1], data[2][2], data[2][3]);
 printf("|%2.3lf,%2.3lf,%2.3lf,%2.3lf|\n",data[3][0], data[3][1], data[3][2], data[2][3]);
}

Matrix4 Matrix4::operator* (const Matrix4& gMatrix) const {
	Matrix4 tmp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			tmp.data[i][j] = 0.0;
			for (int k = 0; k < 4; ++k) {
				tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
			}
		}
	}
	return tmp;
}

Vector4 operator* (const Matrix4& gMatrix, const Vector4& gVector) {
	Vector4 tmp;
	for (int i = 0; i < 4; ++i) {
		tmp.data[i] = 0.0;
		for (int j = 0; j < 4; ++j) {
			tmp.data[i] = tmp.data[i] + (gMatrix.data[i][j] * gVector.data[j]);
		}
	}
	return tmp;
}
