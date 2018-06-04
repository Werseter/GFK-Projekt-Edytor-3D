all:
	g++ *.cpp -ggdb -std=c++11 `wx-config --cxxflags --libs std` -o Graphics3D	
