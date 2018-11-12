#pragma once
#include "SFML/Graphics.hpp"
#include "Frame.h"

class Animation
{
public:
	std::vector<std::vector<Frame>> frames;
	bool isPlaying = false, isFinished = false;
	bool loop = false;
	int frame = 0, currentFrame = 0, startFrame = 0;
	sf::Sprite sprite;
	sf::RenderTexture tar;

	Animation();
	Animation(const Animation&);
	Animation operator= (const Animation&);

	void play();
	void stop();
	void load(std::vector<std::vector<Frame>>& _frames);
};