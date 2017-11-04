#include <ncurses.h>
#include <string.h>

void horiz_center_text (char *text,
						int line)
{
	int max_lines;
	int max_cols;
	int len;
	int indent;

	getmaxyx (stdscr, max_lines, max_cols);

	len = strlen (text);
	indent = (max_cols - len) / 2;

	mvaddstr (line, indent, text);
	refresh ();
}

void vert_center_text (char *text,
					   int col)
{
	int max_lines;
	int max_cols;
	int len;
	int line;

	getmaxyx (stdscr, max_lines, max_cols);

	len = strlen (text);
	line = max_lines / 2;

	mvaddstr (line, col, text);
	refresh ();
}

void print_title ()
{
	char *title = "Timekeeper";

	horiz_center_text (title, 1);
}

void print_menu ()
{
	char *menu;

	sprintf (menu, 255, "Select an option\n"
						"\tn - start new shift\n"
						"\te - end current shift\n"
						"\tq - quit\n");

	horiz_center_text (menu, 2);
}
