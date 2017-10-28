/*
 * database.c
 */

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void exit_with_error (MYSQL *conn)
{
	fprintf (stderr, "%s\n", mysql_error (conn));
	mysql_close (conn);
	exit (1);
}

char* remove_newline (char *input)
{
	size_t ln = strlen (input) - 1;
	
	if (input[ln] == '\n')
	{
		input[ln] = '\0';
	}

	return (input);
}

void start_shift (MYSQL *conn)
{
    char start_time[80];
	char employee[32];
	int project;
	char phase[32];

	char buff[4096] = { };

	time_t rawtime;
	struct tm *curr_time;

	rawtime = time (NULL);
	curr_time = localtime (&rawtime);
	strftime (start_time, 79, "%Y-%m-%d %T", curr_time);
	printf ("Start time: %s\n", start_time);
	
	printf ("Employee:\t");
	fgets (employee, sizeof(employee), stdin);
	remove_newline (employee);
	printf ("Employee: %s\n", employee);

	printf ("Project code:\t");
	scanf ("%d", &project);
	getchar ();
	printf ("Project code: %d\n", project);

	printf ("Phase:\t");
	fgets (phase, sizeof(phase), stdin);
	remove_newline (phase);
	printf ("Project phase: %s\n", phase);

	snprintf (buff, 4095, "INSERT INTO work_shifts "
				  		  "(start_time, employee, "
						  "project, phase) VALUES ("
						  "'%s', '%s', %d, '%s');\n",
						  start_time,
						  employee,
						  project,
						  phase);

	if (mysql_query (conn, buff))
	{
		exit_with_error (conn);
	}
	else
	{
		printf ("Added to database\n");
	}
}

int main (void)
{
	MYSQL *conn;
	char *host;
	char *user;
	char *passwd;
	char *db;

	conn = mysql_init (NULL);
	if (conn == NULL)
	{
		printf ("ERROR: Could not create a DB connection\n");
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
							db,
							0,
							NULL,
							0)      == NULL)
	{
		printf ("ERROR: Could not connect to db\n");
		exit_with_error (conn);
	}

	while (1)
	{
		start_shift (conn);
	}

	return (0);
}
