#pragma once
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Sphere.h"
#include<vector>

class EarthSystem
{
public:
	EarthSystem();
	~EarthSystem();

public: 	
	void drawPlanetSatelliteSystem(std::vector<float>& mVertices, std::vector<float>& mColors);
	void resetPositions(); 
	void setSatelliteRadius(float& size);
	void setSatelliteDistance(float& altitude);
	void setSatelliteSpeed(float& speed);
	void calculateOrbitVelocity(float& altitude);

private:
	void drawOrbitingSatellite(std::vector<float>& vertices, std::vector<float>& colors);

private:
	float mSatelliteRadius   = { 0.2f }; // set it to 0.2 for visualization
	float mSatelliteDistance = { 6.371f }; // Earth's radius in Km
	float mSatelliteAngle    = { 0.0f };

	float mOrbitVelocity;
	float mSatelliteSpeed;

	float mEscapeVelocity = { 11.2f }; // 11.2 Km/s for earth
	float mAltitude       = { 6.371f };

	Point3D mSatelliteColor;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;

	Sphere* sphere;
};
