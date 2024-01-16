#include "pch.h"
#include "Sphere.h"
#include<vector>

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}



void Sphere::drawSphere(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, Point3D circleColor)
{
	for (int i = 0; i < 180; i++) //PHI - angle around x-axis
	{
		float phi = float(i) * PI / 180.0f;

		for (int j = 0; j < 360; j++) //THETA - angle around z-axis
		{
			float theta = PI * float(j) / 180.0f;			
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