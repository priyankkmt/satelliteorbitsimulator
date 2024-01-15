#pragma once
#include "Point3D.h"
#include <vector>

class GEOMETRY_API Sphere
{
public: 
	Sphere();
	~Sphere();

public:
	void drawSphere(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, Point3D circleColor);

private:
	const float PI = 3.1415926f;
};
