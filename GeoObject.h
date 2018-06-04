#pragma once

#include <vector>
#include <sstream>

template <typename T> std::string to_string(const T& n) {
	std::ostringstream stm;
	stm << n;
	return stm.str();
}


class GeoObject {
	private:
		static int topId;
	protected:
		int id;
		std::string type;
	public:
		GeoObject(std::string _type) : id(topId++), type(_type) {}
		virtual std::string Repr() const { return to_string(id) + " " + type + " "; }
};

class Sphere : public GeoObject {
	protected:
		float radius;
		int n;
		int m;
		std::vector<float> pos;
	public:
		Sphere(std::vector<float> _pos, float _radius, int _n, int _m) : GeoObject("sphere"), radius(_radius), pos(_pos), n(_n), m(_m) {}
		std::string Repr() const { return GeoObject::Repr() + "(" + to_string(pos[0]) + ", " + to_string(pos[1]) + ", " + to_string(pos[2]) + ") " + to_string(radius); }
};
