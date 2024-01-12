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

void EarthSystem::drawOrbitingSatellite(std::vector<float>& vertices, std::vector<float>& colors)
{
    float theta = static_cast<float>(mSatelliteAngle) * PI / 180.0f;
    float x = mSatelliteDistance * cosf(theta);
    float y = mSatelliteDistance * sinf(theta);

    mXCoordinate = x;
    mYCoordinate = y;

    if (mSatelliteSpeed > 0.0f && mSatelliteSpeed <= 100.0f) {
        if (mSatelliteSpeed < mOrbitVelocity) {
            mSatelliteDistance -= FALL_VELOCITY;
        }
        else if (mSatelliteSpeed > mEscapeVelocity) {
            mSatelliteDistance += ESCAPE_VELOCITY;
        }
    }

    sphere->drawSphere(vertices, colors, x, y, 0.4f, mSatelliteColor);

    mSatelliteAngle += mSatelliteSpeed / 2;

    if (mSatelliteDistance <= EARTH_RADIUS) {
        mSatelliteSpeed = 0.0f;
    }

    if (mSatelliteAngle >= 360.0f) {
        mSatelliteAngle -= 360.0f;
    }
}

void EarthSystem::calculatePath(std::vector<GLfloat>& vertices, std::vector<GLfloat>& colors, int& pathPoints)
{
    vertices.push_back(mXCoordinate);
    vertices.push_back(mYCoordinate);
    vertices.push_back(0.0);

    colors.push_back(1.0);
    colors.push_back(0.0);
    colors.push_back(0.0);

    pathPoints += 3;
}

void EarthSystem::resetPositions() 
{
    // reset satellite's height and it's angle so it will come at initial pos
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
    float adjustedAltitude = altitude * 100.0f; // Convert altitude to kilometers

    float denominator = EARTH_RADIUS_KM + adjustedAltitude + mSatelliteRadius;
    mOrbitVelocity = sqrt(GRAVITATIONAL_CONSTANT / denominator);
}
