#pragma once
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Sphere.h"

#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>

class EarthSystem
{
public:
	EarthSystem();
	~EarthSystem();

public: 	
	void drawOrbitingSatellite(std::vector<float>& vertices, std::vector<float>& colors);
	void resetPositions(); 
	void setSatelliteRadius(float& size);
	void setSatelliteDistance(float& altitude);
	void setSatelliteSpeed(float& speed);
	void calculateOrbitVelocity(float& altitude);
	void calculatePath(std::vector<float>& vertices, std::vector<float>& colors, int& pathPoints);

private:
	float mSatelliteRadius = 0.2f ; // set it to 0.2 for visualization
	float mSatelliteDistance = 6.371f ; // Earth's radius in Km
	float mSatelliteAngle = 0.0f ;

	float mOrbitVelocity;
	float mSatelliteSpeed;

	float mXCoordinate;
	float mYCoordinate;

	float mEscapeVelocity = 11.2f; // 11.2 Km/s for earth
	float mAltitude = 6.371f;

	Point3D mSatelliteColor;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;

	const float PI = 3.1415926f;
	const float FALL_VELOCITY = 0.1f;
	const float ESCAPE_VELOCITY = 0.09f;
	const float EARTH_RADIUS = 6.371f;
	const float GRAVITATIONAL_CONSTANT = 398583.96f;
	const float EARTH_RADIUS_KM = 6371.0f;

	Sphere* sphere;
};
