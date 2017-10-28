/*
 * database.c
 */

#include <mysql/mysql.h>
#include <myglobal.h>
#include <string.h>

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

void prompt_for_data (MYSQL *conn)
{


