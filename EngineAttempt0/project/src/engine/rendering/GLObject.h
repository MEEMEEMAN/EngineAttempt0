#pragma once

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