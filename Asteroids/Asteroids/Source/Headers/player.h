#include "stdafx.h"
#include "iostream"
#include "resource.h"

#ifndef PLAYER _H
#define PLAYER_H
class Player
{
private:
public:
	ALLEGRO_BITMAP *player = NULL;

	struct attrib
	{
		float x_pos;
		float y_pos;
		int act_angle;
		int ez_angle;
		int height;
		int width;
		int x_cen;
		int y_cen;
		float x_vec;
		float y_vec;
	};
	attrib traits;
	bool player_init()
	{
		player = al_load_bitmap("C:/Users/Zach/Documents/GitHub/Asteroid/Asteroids/Asteroids/Resources/ship.png");
		if (player == NULL)
		{
			return false;
		}
		traits.x_pos = 200;
		traits.y_pos = 200;
		traits.ez_angle = 0;
		traits.act_angle = 0;
		traits.height = al_get_bitmap_height(player);
		traits.width = al_get_bitmap_width(player);
		traits.x_cen = (traits.width / 2);
		traits.y_cen = (traits.height / 2);
		traits.x_vec = 0;
		traits.y_vec = 0;
		return true;
	}
	void fix_angle()
	{
		traits.act_angle = traits.act_angle % 360;
		return;
	}
};
#endif
