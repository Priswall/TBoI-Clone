#include "SFML/Graphics.hpp"
#include "Animation.h"

Animation::Animation() {};

void Animation::load(std::vector<Frame>& _frames)
{
	frames = _frames;
}

void Animation::stop()
{
	frame = 0;
	currentFrame = 0;
	startFrame = 0;
	isPlaying = false;
}

void Animation::play()
{
	if (isPlaying)
	{
		frame++;
		if (frame - startFrame > frames[currentFrame].frames)
		{
			if(loop) 
				currentFrame = (currentFrame + 1) % static_cast<int>(frames.size());
			else
				currentFrame++;
			startFrame = frame;
		}
		if (currentFrame + 1 > static_cast<int>(frames.size()) && !loop)
		{
			stop();
			isFinished = true;
		}
	}
}