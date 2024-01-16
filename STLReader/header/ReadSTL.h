#pragma once
#include "pch.h"

#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>

class STLREADER_API ReadSTL
{
public:
	ReadSTL();
	~ReadSTL();

	void readSTL(std::vector<float>& mVertices, std::vector<float>& mColors, int& spherePoints);
};