#include "Headers\main.h"
#include <allegro5\allegro.h>

int main(int argc, char **argv)
{
	Main main;
	main.display = main.init();
	if (main.display == NULL)
	{
		return -1;
	}
	al_rest(3);
	al_destroy_display(main.display);
	return 0;
}