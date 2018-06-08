#pragma once

#include <vector>
#include <sstream>

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

		// Method for printing object's representation
		virtual std::string Repr() const { return toString(objId) + " " + type + " "; }

		// Method returning cordinates in a string
		std::string GetCoordinatesString(Data3D v) const { return "(" + toString(v[0]) + ", " + toString(v[1]) + ", " + toString(v[2]) + ")"; }

		// Method rotating an object
		void Rotate(Data3D pos, Data3D angles) { }

		//Method returning rendering data
		const DataVector* GetData() const { return &points; }

		// Method converting object data into rendering points
		virtual void GeneratePoints() = 0;

};
