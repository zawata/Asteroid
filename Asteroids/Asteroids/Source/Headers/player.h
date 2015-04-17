#include "stdafx.h"
#include "iostream"
#include "resource.h"

#ifndef PLAYER _H
#define PLAYER_H
class Player
{
private:
public:
	ALLEGRO_BITMAP *player_base = NULL;
	ALLEGRO_BITMAP *player_flaming = NULL;

	struct attrib
	{
		float x_pos;
		float y_pos;
		int act_angle;
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
		player_base = al_load_bitmap("C:/Users/Zach/Documents/GitHub/Asteroid/Asteroids/Asteroids/Resources/ship_smaller.png");
		player_flaming = al_load_bitmap("C:/Users/Zach/Documents/GitHub/Asteroid/Asteroids/Asteroids/Resources/ship.png");
		if (player_base == NULL || player_flaming == NULL)
		{
			return false;
		}
		traits.x_pos = 200;
		traits.y_pos = 200;
		traits.act_angle = 0;
		traits.height = al_get_bitmap_height(player_base);
		traits.width = al_get_bitmap_width(player_base);
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
	void check_bounds(float s_width, float s_height)
	{
		if (traits.x_pos < 0 - traits.height)
		{
			traits.x_pos = s_width + traits.height;
		}
		else
		{
			if (traits.x_pos > s_width + traits.height)
			{
				traits.x_pos = 0 - traits.height;
			}
		}
		if (traits.y_pos < 0 - traits.height)
		{
			traits.y_pos = s_height + traits.height;
		}
		else
		{
			if (traits.y_pos > s_height + traits.height)
			{
				traits.y_pos = 0 - traits.height;
			}
		}
		return;
	}
};
#endif
