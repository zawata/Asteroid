#include "stdafx.h"
#include "Headers\main.h"
#include "Headers\resource.h"

int main(int argc, char **argv)
{
	Main main;
	Player player;
	if (argc > 1)
	{
		for (int i = 0; i <= argc; i++)
		{
			if (argv[i] == "-f")
				main.args[Main::FULLSCREEN] = true;
			if (argv[i] == "-c")
				main.args[Main::CONSOLE] = true;
		}
	}
	main.init();
	if (main.display == NULL)
		return -1;
	while (main.exec_loop()) {}
	main.destroy();
	return 0;
}
//https://www.allegro.cc/forums/thread/604040/865263#target