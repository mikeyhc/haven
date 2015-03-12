/* main.c
 * entry point for the application, parses the commandline arguments, reads the
 * configuration files and then starts the application with the give
 * configuration.
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <stdio.h>
#include <game.h>
#include <gui.h>

int main(void)
{
	int ret;
	/* TODO: commandline arguments */
	/* TODO: configuration files */
	if(!initialize_gui()) {
		fprintf(stderr, "could not initialize GUI\nexiting\n");
		return 1;
	}

	ret = main_loop();
	quit_gui();

	return ret;
}
