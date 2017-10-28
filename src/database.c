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

int find_curr_shift (MYSQL *conn)
{
	int curr_shift;
	char buff[256];

	int i;
	MYSQL_RES *result;
	int num_fields;
	MYSQL_ROW row;

	snprintf (buff, 255, "SELECT id FROM work_shifts WHERE "
						 "end_time = NULL ORDER BY id DESC "
						 "LIMIT 1;");

	if (mysql_query (conn, buff))
	{
		exit_with_error (conn);
	}
	
	result = mysql_store_result (conn);

	if (result == NULL)
	{
		curr_shift = 0;
	}
	else
	{
		num_fields = mysql_num_fields (result);

		while (row = mysql_fetch_row (result))
		{
			for (i = 0; i < num_fields; i++)
			curr_shift = atoi (row[0]);
		}

		mysql_free_result (result);
	}

	return curr_shift;
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

void end_shift (MYSQL *conn,
				int id)
{
	char end_time[80];
	char work_done[256];
	char comments[256];

	char buff[4096] = { };
	
	time_t rawtime;
	struct tm *curr_time;

	printf ("Work done:\t");
	fgets (work_done, sizeof (work_done), stdin);
	remove_newline (work_done);
	printf ("Work done: %s\n", work_done);

	printf ("Comments:\t");
	fgets (comments, sizeof (comments), stdin);
	remove_newline (comments);
	printf ("Comments: %s\n", comments);
	
	rawtime = time (NULL);
	curr_time = localtime (&rawtime);
	strftime (end_time, 79, "%Y-%m-%d %T", curr_time);
	printf ("End time: %s\n", end_time);

	snprintf (buff, 4095, "UPDATE work_shifts SET "
					  	  "end_time = '%s', "
						  "work_done = '%s', "
						  "comments = '%s' "
						  "WHERE id = %d",
						  end_time,
						  work_done,
						  comments,
						  id);

	if (mysql_query (conn, buff))
	{
		exit_with_error (conn);
	}
	else
	{
		printf ("Database updated\n");
	}
}

int main (void)
{
	MYSQL *conn;
	char *host;
	char *user;
	char *passwd;
	char *db;

	int curr_shift;

	char input;

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

	curr_shift = find_curr_shift (conn);

	if (curr_shift == 0)
	{
		printf ("Not currently clocked in\n");
	}
	else
	{
		printf ("Currently clocked in\n");
	}

	printf ("Select and option:\n"
			"\tn - start new shift\n"
			"\te - end current shift\n"
			"\tq - quit");

	input = getchar ();

	if (input == 'n' || input == 'N')
	{
		start_shift (conn);
	}
	else if (input == 'e' || input == 'E')
	{
		if (curr_shift != 0)
		{
			end_shift (conn,
					   curr_shift);
		}
		else
		{
			printf ("ERROR: Not currently clocked in\n");
		}
	}

	mysql_close (conn);

	return (0);
}
