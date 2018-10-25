#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Frame.h"

Animation::Animation() {};

void Animation::load(std::vector<Frame>& _frames)
{
	frames = _frames;
}

void Animation::play()
{
	if (isPlaying)
	{
		frame++;
		if (currentFrame + 1 > static_cast<int>(frames.size()) && !loop)
		{
			stop();
			isFinished = true;
		}
		if (frame - startFrame > frames[currentFrame].frames)
		{
			currentFrame = (currentFrame + 1) % static_cast<int>(frames.size());
			startFrame = frame;
		}
	}
}

void Animation::stop()
{
	frame = 0;
	currentFrame = 0;
	startFrame = 0;
	isPlaying = false;
}