/*
 * main.c
 *
 */

#include <ncurses.h>
#include <mysql/mysql.h>
#include <"database.h">
#include <"ui-methods.c">

int main (void)
{
	MYSQL *conn;
	char *host;
	char *user;
	char *passwd;
	char *db;

	struct work_shift curr_shift;
	struct project curr_project;

	char menu[256];

	char input;
	char input_garbage;

	conn = mysql_init (NULL);	
	if (conn == NULL)
	{
		printf ("ERROR: could not create database connection\n");
		exit (1);
	}

	host = "localhost";
	user = "timekeeperApp";
	passwd = "securepasswd";
	db = "timekeeper";

	if (mysql_real_connect (conn, 
	  					    host,
						    user,
						    passwd,
						    db)     == NULL)
	{
		printf ("ERROR: could not connect to the database\n");
		exit (1);
	}

	curr_shift = find_curr_shift (conn);
	if (curr_shift.id == 0)
	{

	initscr ();

	if (!has_colors ())
	{
		endwin ();
		printf ("ERROR: Colors not available on this terminal\n");
		exit (1);
	}

	if (start_color () != OK)
	{
		endwin ();
		printf ("Error initiating terminal colors\n");
		exit (1);
	}
	init_pair (1, COLOR_WHITE, COLOR_BLUE);

	bkgd (COLOR_PAIR (1));

	print_title ();
	print_menu ();

	input = getch ();
	input_garbage = getch ();

	if (input == 'n' || input == 'N')
	{
		start_shift (conn);
	}
	else if (input == 'e' || input == 'E')
	{
		if (curr_shift.id != 0)
		{
			endshift (conn,
					  curr_shift.id);
		}
		else
		{
			print_menu ();
		}
	}
	else if (input == 'q' || input == 'Q')
	{
		endwin ();
		printf ("Exiting\n");
		return (0);
	}
	else
	{
		print_menu ();
	}


	mysql_close (conn);

	endwin ();
	return (0);
}
