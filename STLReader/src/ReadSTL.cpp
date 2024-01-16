#include "pch.h"
#include "ReadSTL.h"

ReadSTL::ReadSTL()
{

}

ReadSTL::~ReadSTL()
{

}

void ReadSTL::readSTL(std::vector<float>& mVertices, std::vector<float>& mColors, int& spherePoints)
{
    std::string filePath = "D:/Work_space/satelliteorbitsimulator/SatelliteOrbitSimulator/resource/Sphere3.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(dataFile, line))
    {
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices.push_back(x * 0.12);
            mVertices.push_back(y * 0.12);
            mVertices.push_back(z * 0.12);

            mColors.push_back(0.0);
            mColors.push_back(0.0);
            mColors.push_back(1.0);

            spherePoints += 3;
        }
    }
}
