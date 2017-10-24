/*
 * main.c
 *
 */

#include <ncurses.h>
#include <mysql/mysql.h>

int main (void)
{
	initscr ();
	addstr ("Timekeeper\n");
	refresh ();

	getch ();
	endwin ();
	return (0);
}
