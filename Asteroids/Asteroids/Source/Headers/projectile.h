#include "stdafx.h"
#include "resource.h"

#ifndef _PROJECTILE_NUMBER
#define _PROJECTILE_NUMBER 3
#endif

#ifndef PROJECTILE_H
#define PROJECTILE_H
class Projectile
{
private:

public:
	ALLEGRO_BITMAP *projectile[3]; // create array here
	bool projectile_can_be_fired = true;

	struct attrib
	{
		float x_pos;
		float y_pos;
		int speed = 12;
		int angle;
		int side = 3;
		bool is_displayed = false;
	};
	attrib traits[_PROJECTILE_NUMBER];

	bool init_projectile_bitmaps(ALLEGRO_DISPLAY *display)
	{
		for (int i = 0; i < _PROJECTILE_NUMBER; i++)
		{
			projectile[i] = al_create_bitmap(traits[i].side, traits[i].side);
			if (projectile == NULL)
			{
				return false;
			}
			al_set_target_bitmap(projectile[i]);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			al_set_target_backbuffer(display);
		}
		return true;
	}
	void move_all_onscreen_projectiles(float s_width, float s_height)
	{
		for (int i = 0; i < _PROJECTILE_NUMBER; i++)
		{
			if (traits[i].is_displayed)
			{
				move_projectile(i);
				check_bounds(s_width, s_height, i);
				draw_projectiles();
			}
		}
	}
	void place_projectile(int playerx, int playery, int angle, int bitmapheight)
	{
		int new_bullet = get_next_available_projectile();
		if (new_bullet == -1)
			return;
		traits[new_bullet].angle = ((360 - angle)+180);
		traits[new_bullet].x_pos = playerx + (cos((angle - 90) * (M_PI / 180)) * bitmapheight);
		traits[new_bullet].y_pos = playery + (sin((angle - 90) * (M_PI / 180)) * bitmapheight);
		traits[new_bullet].is_displayed = true;
		return;
	}
	void move_projectile(int bulletnum)
	{
		traits[bulletnum].x_pos += (cos(((360 - traits[bulletnum].angle) + 90) * (M_PI / 180)) * traits[bulletnum].speed); //x component vector of movement
		traits[bulletnum].y_pos += (sin(((360 - traits[bulletnum].angle) + 90) * (M_PI / 180)) * traits[bulletnum].speed); //y component vector of movement
	}
	void draw_projectiles()
	{
		for (int i = 0; i < _PROJECTILE_NUMBER; i++)
		{
			if (traits[i].is_displayed)
			{
				al_draw_bitmap(projectile[i], traits[i].x_pos, traits[i].y_pos, 0);
			}
		}
		return;
	}	
	void check_bounds(float s_width, float s_height, int bulletnum)
	{
		if (!traits[bulletnum].is_displayed)
		{
			return;
		}
		if (traits[bulletnum].x_pos < 0 - traits[bulletnum].side)
		{
			remove_projectile(bulletnum);
			return;
		}
		else
		{
			if (traits[bulletnum].x_pos > s_width + traits[bulletnum].side)
			{
				remove_projectile(bulletnum);
				return;
			}
		}
		if (traits[bulletnum].y_pos < 0 - traits[bulletnum].side)
		{
			remove_projectile(bulletnum);
			return;
		}
		else
		{
			if (traits[bulletnum].y_pos > s_height + traits[bulletnum].side)
			{
				remove_projectile(bulletnum);
				return;
			}
		}
		return;
	}
	int get_next_available_projectile()
	{
		for (int i = 0; i <= _PROJECTILE_NUMBER - 1; i++)
		{
			if (!traits[i].is_displayed)
			{
				std::cout << i << std::endl;
				return i; //bullet can be created
			}
		}
		return -1; // no bullets can be created
	}
	void remove_projectile(int bulletnum)
	{
		traits[bulletnum].x_pos = 0;
		traits[bulletnum].y_pos = 0;
		traits[bulletnum].is_displayed = false;
	}
	void destroy_anim_sprites()
	{
		for (int i = 0; i < _PROJECTILE_NUMBER - 1; i++)
		{
			al_destroy_bitmap(projectile[i]);
		}
		return;
	}
};
#endif