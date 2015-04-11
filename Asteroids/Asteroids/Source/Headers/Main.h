#include "allegro5\allegro.h"
#include "iostream"

#ifndef MAIN_H
#define MAIN_H
class Main
{
public:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY *init()
	{
		display = NULL;
		if (al_init())
		{
			display = al_create_display(640, 480);
			if (display)
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
			}
			else
				fprintf(stderr, "failed to create display!\n");
		}
		else
			fprintf(stderr, "failed to initialize allegro!\n");
		return display;
	}
private:

protected:
};
#endif