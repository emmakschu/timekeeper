/*
 * database.h
 */

struct work_shift {
	int id;
	char *start_time;
	char *end_time;
	char *employee;
	int project_code;
	char *phase;
	char *work_done;
	char *comments;
};

struct project {
	int id;
	char *name;
	char *start_date;
	char *end_date;
	char *comments;
};

void exit_with_error (MYSQL *conn);
char* remove_newline (char *input);
struct work_shift find_curr_shift (MYSQL *conn);
struct project find_curr_project (MYSQL *conn,
								  int proj_id);
void start_shift (MYSQL *conn);
void end_shift (MYSQL *conn,
				int id);

