#include "SFML/Graphics.hpp"
#include "Animation.h"

Animation::Animation() {};
Animation::Animation(const Animation& animation)
{
	frames = animation.frames;
	frame = animation.frame;
	currentFrame = animation.currentFrame;
	isPlaying = animation.isPlaying;
	isFinished = animation.isFinished;
	loop = animation.loop;
	startFrame = animation.startFrame;
	sprite = animation.sprite;
}
Animation Animation::operator=(const Animation& animation)
{
	frames = animation.frames;
	frame = animation.frame;
	currentFrame = animation.currentFrame;
	isPlaying = animation.isPlaying;
	isFinished = animation.isFinished;
	loop = animation.loop;
	startFrame = animation.startFrame;
	return *this;
}

void Animation::load(std::vector<std::vector<Frame>>& _frames)
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
		std::vector<std::vector<Frame>> temp = frames;
		std::sort(temp.begin(), temp.end(), [](const std::vector<Frame>& a, const std::vector<Frame>& b) ->bool { return a.size() > b.size(); });
		if (frame - startFrame > temp[0][currentFrame].frames)
		{
			if(loop) 
				currentFrame = (currentFrame + 1) % static_cast<int>(temp[0].size() - 1);
			else
				currentFrame++;
			startFrame = frame;
		}
		tar.create(466, 310);
		tar.clear(sf::Color::Transparent);
		
		for (std::vector<std::vector<Frame>>::iterator i = frames.begin(); i != frames.end(); i++)
		{
			sf::Sprite tempSprite;
			if (currentFrame > i->size() - 1)
			{
				tempSprite = i->at(i->size() - 1).getSprite();
				tempSprite.setPosition(i->at(i->size() - 1).offSet);
			}
			else
			{
				tempSprite = i->at(currentFrame).getSprite();
				tempSprite.setPosition(i->at(currentFrame).offSet);
			}
			tar.draw(tempSprite);
		}

		tar.display();

		sprite.setTexture(tar.getTexture());

		if (currentFrame + 1 > static_cast<int>(temp[0].size() - 1) && !loop)
		{
			stop();
			isFinished = true;
		}
	}
}