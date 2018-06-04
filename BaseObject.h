#pragma once

#include <vector>
#include <sstream>


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
		// Each object has it's id number and type
		unsigned int objId;
		std::string type;

	public:
		// When creating an object a desired type must be given
		// Object initializes with id and a type
		BaseObject(std::string type) : objId(idCounter++), type(type) {}

		// Method for printing object's representation
		virtual std::string Repr() const { return toString(objId) + " " + type + " "; }

		// Method returning cordinates in a string
		std::string getCoordinatesString(std::vector<float> v) const { return "(" + toString(v[0]) + ", " + toString(v[1]) + ", " + toString(v[2]) + ")"; }
};
