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
		bool is_fired = false;
	};
	attrib traits[_PROJECTILE_NUMBER];
	bool init_projectile_sprite(int bulletnum, ALLEGRO_DISPLAY *display)
	{
		projectile[bulletnum] = al_create_bitmap(traits[bulletnum].side, traits[bulletnum].side);
		if (projectile == NULL)
		{
			return false;
		}
		al_set_target_bitmap(projectile[bulletnum]);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_set_target_backbuffer(display);
		return true;
	}
	void move_all_onscreen_projectiles(float s_width, float s_height)
	{
		for (int i = 0; i < _PROJECTILE_NUMBER; i++)
		{
			if (projectile[i] != NULL)
			{
				move_projectile(i);
				check_bounds(s_width, s_height, i);
				draw_projectiles();
			}
		}
	}
	bool place_projectile(int playerx, int playery, int angle, int bitmapheight, ALLEGRO_DISPLAY *display)
	{
		int new_bullet = get_next_available_projectile();
		if (new_bullet == -1)
			return false;
		if (!init_projectile_sprite(new_bullet, display))
		{
			return false;
		}
		traits[new_bullet].angle = angle;
		traits[new_bullet].x_pos = playerx + (cos(((360 - angle) + 90) * (M_PI / 180)) * bitmapheight);
		traits[new_bullet].y_pos = playery + (sin(((360 - angle) + 90) * (M_PI / 180)) * bitmapheight);
		return true;
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
			if (projectile[i] != NULL)
			{
				al_draw_bitmap(projectile[i], traits[i].x_pos, traits[i].y_pos, 0);
			}
			else
			{
				std::cout << "draw" << std::endl;
			}
		}
		return;
	}	
	void check_bounds(float s_width, float s_height, int bulletnum)
	{
		if (projectile[bulletnum] == NULL)
		{
			return;
		}
		if (traits[bulletnum].x_pos < 0 - traits[bulletnum].side)
		{
			al_destroy_bitmap(projectile[bulletnum]);
			return;
		}
		else
		{
			if (traits[bulletnum].x_pos > s_width + traits[bulletnum].side)
			{
				al_destroy_bitmap(projectile[bulletnum]);
				return;
			}
		}
		if (traits[bulletnum].y_pos < 0 - traits[bulletnum].side)
		{
			al_destroy_bitmap(projectile[bulletnum]);
			return;
		}
		else
		{
			if (traits[bulletnum].y_pos > s_height + traits[bulletnum].side)
			{
				al_destroy_bitmap(projectile[bulletnum]);
				return;
			}
		}
		return;
	}
	int get_next_available_projectile()
	{
		for (int i = 0; i <= _PROJECTILE_NUMBER - 1; i++)
		{
			if (projectile[i] == NULL)
			{
				std::cout << i << std::endl;
				return i; //bullet can be created
			}
		}
		return -1; // no bullets can be created
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