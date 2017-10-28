/*
 * main.c
 *
 */

#include <ncurses.h>
#include <mysql/mysql.h>

int main (void)
{
	initscr ();

	start_color ();
	init_pair (1, COLOR_WHITE, COLOR_BLUE);

	bkgd (COLOR_PAIR (1));

	addstr ("Timekeeper\n");
	refresh ();

	getch ();
	endwin ();
	return (0);
}
