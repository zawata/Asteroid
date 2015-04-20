#include "stdafx.h"
#include "resource.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H
class Projectile
{
private:
	
public:
	ALLEGRO_BITMAP *projectile = NULL;
	bool projectile_fired = false;

	struct attrib
	{
		float x_pos;
		float y_pos;
		int act_angle;
		int height = 2;
		int width = 2;
		int x_cen;
		int y_cen;
		float x_vec;
		float y_vec;
	};
	attrib traits;
	bool init_projectile()
	{
		projectile = al_create_bitmap(traits.width, traits.height);
		if (projectile == NULL)
			return false;
		al_set_target_bitmap(projectile);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		return true;
	}
};
#endif