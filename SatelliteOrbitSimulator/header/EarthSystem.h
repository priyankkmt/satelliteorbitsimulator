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
	const std::vector<float>& getCurrentVertices() const { return mCurrentVertices; }
	const std::vector<float>& getCurrentColors() const { return mCurrentColors; }

private:
	void drawOrbitingSatellite(std::vector<float>& vertices, std::vector<float>& colors);

private:

	float satelliteRadius = { 0.2f };
	float satelliteDistance = { 6.371f };
	float satelliteAngle = { 0.0f };

	float orbitVelocity;
	float satelliteSpeed;
	float escapeVelocity = 11.2f; // 11.2 Km/s
	float mAltitude = { 6.371f };

	Point3D mPlanetColors;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;

	Sphere* sphere;
};