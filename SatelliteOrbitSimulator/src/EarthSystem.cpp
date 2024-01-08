#include "stdafx.h"
#include "EarthSystem.h"


EarthSystem::EarthSystem()
{
	mSatelliteColor ={ Point3D(1.0, 0.0, 0.0) };  // Red

	sphere = new Sphere();
}

EarthSystem::~EarthSystem()
{
}

void EarthSystem::drawPlanetSatelliteSystem(std::vector<float>& mVertices, std::vector<float>& mColors)
{
	//6.371 as earths radius is 6371 km
	sphere->drawSphere(mVertices, mColors, 0.0f, 0.0f, 6.371f, Point3D(0.0, 0.0, 1.0)); // Earth
	drawOrbitingSatellite(mVertices, mColors); // satellite
}

void EarthSystem::drawOrbitingSatellite(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{
	float theta = float(mSatelliteAngle) * 3.1415926f / 180.0f; // setting of new position angle (theta)
	float x = mSatelliteDistance * cosf(theta); // setting new x & y position
	float y = mSatelliteDistance * sinf(theta);

	if(mSatelliteSpeed > 0.0f && mSatelliteSpeed <= 100.0f){ // move only if there is some speed
		if (mSatelliteSpeed < mOrbitVelocity) // fall condition
		{
			mSatelliteDistance -= 0.1f;
		}
		else if(mSatelliteSpeed > mEscapeVelocity) // escape condition
		{
			mSatelliteDistance += 0.09f;
		}
	}

	sphere->drawSphere(mVertices, mColors, x, y, 0.4f, mSatelliteColor);

	mSatelliteAngle += mSatelliteSpeed/4; // while moving input speed is too much so divide it by 4

	if (mSatelliteDistance <= 6.371f) // if it touches earth then it stop moving
	{
		mSatelliteSpeed = 0.0f;
	}

	// Angle Should be 360 degrees
	if (mSatelliteAngle >= 360.0f) {
		mSatelliteAngle -= 360.0f;
	}
}                               

void EarthSystem::resetPositions() // reset satellite's height and it's angle so it will come at initial pos
{
	mSatelliteDistance = mAltitude;
	mSatelliteAngle = 0.0f;
}

void EarthSystem::setSatelliteRadius(float& size) // input is in m so converted to km
{
	mSatelliteRadius = size/(2*1000);
}

void EarthSystem::setSatelliteDistance(float& altitude) // Altitude is divided by 10 to set it in window
{
	mAltitude += altitude / 10;
	mSatelliteDistance += altitude/10;
}

void EarthSystem::setSatelliteSpeed(float& speed) 
{
	mSatelliteSpeed = speed;
}

void EarthSystem::calculateOrbitVelocity(float& altitude) // orbital velocity calculation
{
	float numerator = 398583.96f;
	float denomerator = 6371 + altitude * 100 + mSatelliteRadius; // altitude is *100 to set it in Km
	mOrbitVelocity = sqrt(numerator / denomerator);
}
