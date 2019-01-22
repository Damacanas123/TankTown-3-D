#pragma once

enum ATTR_LOCATION {
	POSITION = 0,
	NORMAL = 1,
	UV = 2,
};

namespace config {
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float SCREEN_RATIO = (float)config::SCREEN_WIDTH / (float)SCREEN_HEIGHT;
}