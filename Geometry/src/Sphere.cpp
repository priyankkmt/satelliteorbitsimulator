#include "pch.h"
#include "Sphere.h"
#include<vector>

Sphere::Sphere()
{
}

Sphere::Sphere(Point3D gCenter, float gRadius):center(gCenter),radius(gRadius)
{
}

Sphere::~Sphere()
{
}

void Sphere::drawCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, Point3D circleColor)
{
	for (int j = 0; j < 360; ++j) {
		float theta = float(j) * 3.1415926f / 180.0f;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		float z = 0.0f;

		mVertices.push_back(x);
		mVertices.push_back(y);
		mVertices.push_back(z);
		
		mColors.push_back(circleColor.x());
		mColors.push_back(circleColor.y());
		mColors.push_back(circleColor.z());
	}
}

void Sphere::drawSphere(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor)
{
	for (int i = 0; i < 180; i++) //PHI
	{
		float phi = float(i) * 3.1415926f / 180.0f;
		for (int j = 0; j < 360; j++) //THETA
		{
			float theta = 3.1415926f * float(j) / 180.0f;			
			float x = radius * sinf(theta) * cosf(phi);
			float y = radius * sinf(theta) * sinf(phi);
			float z = radius * cosf(theta);

			mVertices.push_back(cx + x);
			mVertices.push_back(cy + y);
			mVertices.push_back(0.0f + z);

			mColors.push_back(circleColor.x());
			mColors.push_back(circleColor.y());
			mColors.push_back(circleColor.z());
		}
	}
}