#pragma once
class CollisionCooldown {
public:
	bool running;
	int frames;
	CollisionCooldown() {
		frames = 0;
		running = false;
	};
};