#pragma once
#include "pch.h"

class Time
{
	public:

	//Calculates time deltas.
	static void Update();

	//Returns the time it took to render the last frame in 
	static double DeltaTime();

	//Returns the the average DeltaTime for the previous second.
	static double GetAvgDelta();

	/*
	* Returns the time since the start of the application in seconds.
	*/
	static double GetStartTimer();

	private:
	static void CalcAVGDelta();
	static double beginTimer;
	static std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
	static std::vector<double> deltas;
	static double mDeltaTime;
	static double avgDeltaTime;
};