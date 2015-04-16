#include "stdafx.h"
#include "player.h"

#ifndef MAIN_H
#define MAIN_H
class Main
{
private:
	const float FPS = 60;
	bool redraw = true;
	Player player;
	const float fric_const = 0.015;
	const float move_speed = 0.25;

	void register_events()
	{
		al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
		al_register_event_source(event_queue, al_get_mouse_event_source());
		al_register_event_source(event_queue, al_get_keyboard_event_source());
	}

	void init_devices()
	{
		/*
		al_init();
		al_install_mouse();
		al_install_keyboard();
		timer = al_create_timer(1.0 / FPS);
		display = al_create_display(disp_mode.width, disp_mode.height);
		event_queue = al_create_event_queue();
		*/
		if (!al_init()) {
			ErrorMessage("Failed to initialize allegro.");
			return;
		}

		timer = al_create_timer(1.0 / FPS);
		if (!timer) {
			ErrorMessage("Failed to initialize timer.");
			return;
		}

		if (!al_install_mouse()) {
			ErrorMessage("Failed to initialize mouse.");
			return;
		}

		if (!al_install_keyboard()) {
			ErrorMessage("Failed to initialize the keyboard.");
			return;
		}
		display = al_create_display(disp_mode.width, disp_mode.height);
		if (!display) {
			ErrorMessage("Failed to initialize display.");
			return;
		}

		event_queue = al_create_event_queue();
		if (!event_queue) {
			ErrorMessage("Failed to initialize event queue.");
			return;
		}
	}

public:
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_mode;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT ev;

	enum Keys
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KLENGTH
	};
	bool key[KLENGTH];

	enum arg
	{
		FULLSCREEN,
		CONSOLE,
		ALENGTH
	};
	bool args[ALENGTH];

	void init()
	{
		if ((args[CONSOLE]))
		{
			FreeConsole();
		}
		if (args[FULLSCREEN])
		{
			al_init_image_addon();
			al_init_primitives_addon();
			al_get_display_mode(al_get_num_display_modes() - 1, &disp_mode);
			al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		}
		else
		{
			disp_mode.width = 640;
			disp_mode.height = 480;
		}
		al_init_image_addon();
		init_devices();
		init_bitmaps();
		register_events();

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_flip_display();
		al_start_timer(timer);
		return;
	}
	void ErrorMessage(std::string output)
	{
		al_show_native_message_box(
			display, 
			"Error", 
			"Error", 
			(char*)output.c_str(),
			NULL, 
			ALLEGRO_MESSAGEBOX_ERROR);
	}
	bool exec_loop()
	{
		al_wait_for_event(event_queue, &ev);
		switch (ev.type)
		{
			case(ALLEGRO_EVENT_TIMER) :
			{
				player.fix_angle();
				std::cout << player.traits.y_vec << std::endl;
				std::cout << player.traits.x_vec << std::endl;
				if (key[KEY_UP]/* && abs(player.traits.y_vec) < 5 && abs(player.traits.x_vec) < 5*/)
				{
					player.traits.y_vec += (sin(((360 - player.traits.act_angle) + 90) * (M_PI / 180)) * move_speed);
					player.traits.x_vec += (cos(((360 - player.traits.act_angle) + 90) * (M_PI / 180)) * move_speed);
				}
				if (key[KEY_LEFT] && player.traits.x_pos >= 4.0)
				{
					player.traits.act_angle = (player.traits.act_angle - 4) % 360;
				}
				if (key[KEY_RIGHT] && player.traits.x_pos <= disp_mode.width - al_get_bitmap_width(player.player) - 4.0)
				{
					player.traits.act_angle = (player.traits.act_angle + 4) % 360;
				}
				if (player.traits.y_vec > 0)
				{
					player.traits.y_vec -= abs(player.traits.y_vec * fric_const);
				}
				else
				{
					if (player.traits.y_vec < 0)
					{
						player.traits.y_vec += abs(player.traits.y_vec * fric_const);
					}
				}
				if (player.traits.x_vec > 0)
				{
					player.traits.x_vec -= abs(player.traits.x_vec * fric_const);
				}
				else
				{
					if (player.traits.x_vec < 0)
					{
						player.traits.x_vec += abs(player.traits.x_vec * fric_const);
					}
				}
				if (abs(player.traits.x_vec * 1000) < 1)
				{
					player.traits.x_vec = 0;
				}
				if (abs(player.traits.y_vec * 1000) < 1)
				{
					player.traits.y_vec = 0;
				}
				player.traits.x_pos += player.traits.x_vec;
				player.traits.y_pos -= player.traits.y_vec;
				redraw = true;
				break;
			}
			case(ALLEGRO_EVENT_DISPLAY_CLOSE) :
			{
				return false;
				break;
			}
			case(ALLEGRO_EVENT_KEY_DOWN) :
			{
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[Keys::KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[Keys::KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[Keys::KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[Keys::KEY_RIGHT] = true;
					break;

				case ALLEGRO_KEY_ESCAPE:
					return false;
					break;
				case ALLEGRO_KEY_Q:
					std::cout << player.traits.x_pos << std::endl;
					std::cout << player.traits.y_pos << std::endl;
					std::cout << player.traits.ez_angle << std::endl;
					std::cout << player.traits.act_angle << std::endl;
					std::cout << player.traits.height << std::endl;
					std::cout << player.traits.width << std::endl;
					std::cout << player.traits.x_cen << std::endl;
					std::cout << player.traits.x_cen << std::endl;
					break;
				case ALLEGRO_KEY_R:
					player.traits.x_pos = 200;
					player.traits.y_pos = 200;
					player.traits.ez_angle = 0;
					player.traits.act_angle = 0;
					player.traits.x_vec = 0;
					player.traits.y_vec = 0;
					break;
				}
				break;
			}
			case(ALLEGRO_EVENT_KEY_UP) :
			{
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[Keys::KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[Keys::KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[Keys::KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[Keys::KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					return false;
					break;
				}
				break;
			}
			case(ALLEGRO_EVENT_MOUSE_AXES) :
			{
				break;
			}
			case(ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) :
			{
				break;
			}
			case(ALLEGRO_EVENT_MOUSE_BUTTON_UP) :
			{
				break;
			}
			default:
				break;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgba(0, 0, 0, 0));
			al_draw_rotated_bitmap(
				player.player, 
				player.traits.x_cen, 
				player.traits.y_cen, 
				player.traits.x_pos, 
				player.traits.y_pos, 
				(player.traits.act_angle * (M_PI/180)), 0);
			al_flip_display();
		}
		return true;
	}
	void init_bitmaps()
	{
		if (!player.player_init())
		{
			ErrorMessage("Failed to initialize bitmaps.");
		}
		return;
	}
	void destroy()
	{
		al_destroy_timer(timer);
		al_destroy_bitmap(player.player);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
	}
};
#endif