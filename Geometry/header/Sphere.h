#pragma once
#include "Point3D.h"
#include <vector>

class GEOMETRY_API Sphere : public Point3D
{
public: 
	Sphere();
	Sphere(Point3D gCenter, float gRadius);
	~Sphere();

public:
	void drawCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, Point3D circleColor);
	void drawSphere(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor);

private:
	std::vector<Point3D> mPoints;
	float radius;
	Point3D center;
	int sSegments = 600;
	Point3D color;
};