#pragma once

/*
* A basic class for assigning an opengl id to.
*/
class GLObject
{
	public:
	inline unsigned int GetID()
	{
		return mID;
	}

	protected:
	unsigned int mID = 0;
};