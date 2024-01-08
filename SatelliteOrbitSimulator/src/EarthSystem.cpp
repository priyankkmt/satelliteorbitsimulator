#include "stdafx.h"
#include "EarthSystem.h"


EarthSystem::EarthSystem()
{
	mPlanetColors ={ Point3D(1.0, 0.0, 0.0) };  // Red

	sphere = new Sphere();

	//satelliteOrbitPeriod = {365.0f};
}

EarthSystem::~EarthSystem()
{
}

void EarthSystem::drawPlanetSatelliteSystem(std::vector<float>& mVertices, std::vector<float>& mColors)
{
	//6.371 as earths radius is 6371 km
	sphere->drawSphere(mVertices, mColors, 0.0f, 0.0f, 6.371f, 600, Point3D(0.0, 0.0, 1.0));
	drawOrbitingSatellite(mVertices, mColors);
}

void EarthSystem::drawOrbitingSatellite(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{
	float theta = float(satelliteAngle) * 3.1415926f / 180.0f;
	float x = satelliteDistance * cosf(theta);
	float y = satelliteDistance * sinf(theta);

	if(satelliteSpeed > 0.0f && satelliteSpeed <= 100.0f){
		if (satelliteSpeed < orbitVelocity)
		{
			satelliteDistance -= 0.1f;
		}
		else if(satelliteSpeed > escapeVelocity)
		{
			satelliteDistance += 0.2f;
		}
	}

	sphere->drawSphere(mVertices, mColors, x, y, 0.4f, 600, mPlanetColors);

	satelliteAngle += satelliteSpeed/4;

	if (satelliteDistance <= 6.371f)
	{
		satelliteSpeed = 0.0f;
	}

	// Angle Should be 360 degrees
	if (satelliteAngle >= 360.0f) {
		satelliteAngle -= 360.0f;
	}
}                               

void EarthSystem::resetPositions()
{
	satelliteDistance = mAltitude;
	satelliteAngle = 0.0f;
}

void EarthSystem::setSatelliteRadius(float& size) 
{
	satelliteRadius = size/(2*1000);
}

void EarthSystem::setSatelliteDistance(float& altitude) 
{
	mAltitude += altitude / 10;
	satelliteDistance += altitude/10;
}

void EarthSystem::setSatelliteSpeed(float& speed) 
{
	satelliteSpeed = speed;
}

void EarthSystem::calculateOrbitVelocity(float& altitude)
{
	float numerator = 398583.96f;
	float denomerator = 6371 + altitude * 100 + satelliteRadius;
	orbitVelocity = sqrt(numerator / denomerator);
}