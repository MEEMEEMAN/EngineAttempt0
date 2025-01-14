#include "Time.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Time::startTimePoint;
double Time::mDeltaTime = 0;
std::vector<double> Time::deltas;
double Time::avgDeltaTime = 0;
double Time::beginTimer = 0.0;

double Time::DeltaTime()
{
	return mDeltaTime;
}

double Time::GetAvgDelta()
{
	return avgDeltaTime;
}

void Time::Update()
{
	auto endTime = std::chrono::high_resolution_clock::now();

	auto delta = endTime - startTimePoint;

	static int frame = 0;

	//Converting from nanoseconds to seconds.
	if(frame > 0)
	mDeltaTime = delta.count() * 1e-9;
	CalcAVGDelta();
	
	if (frame > 0)
	{
		beginTimer += mDeltaTime;
	}
	else
	{
		frame++;
	}

	startTimePoint = endTime;
}

double Time::GetStartTimer()
{
	return beginTimer;
}

void Time::CalcAVGDelta()
{
	static double frameTimer = 0;

	if (frameTimer >= 1)
	{
		frameTimer = 0;

		double sum = 0;
		for (size_t i = 0; i < deltas.size(); i++)
		{
			sum += deltas[i];
		}
		avgDeltaTime = sum / deltas.size();

		deltas.clear();
	}
	else
	{
		deltas.push_back(mDeltaTime);
		frameTimer += mDeltaTime;
	}
}