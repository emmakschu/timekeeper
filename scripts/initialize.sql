/* Create and initialize tables */

CREATE TABLE IF NOT EXISTS `work_shifts` (
	`id` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
	`start_time` DATETIME,
	`end_time` DATETIME,
	`employee` VARCHAR(32),
	`project` INTEGER NOT NULL,
	`phase` VARCHAR(32),
	`work_done` VARCHAR(256),
	`comments` VARCHAR(256)
);

CREATE TABLE IF NOT EXISTS `projects` (
	`id` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(128),
	`start_date` DATETIME,
	`end_date` DATETIME,
	`comments` VARCHAR(256)
);

INSERT INTO `work_shifts` VALUES (
	1,
	"2017-10-28 05:56:55",
	"",
	"Michael",
	1,
	"drafting",
	"create SQL database",
	""
);

INSERT INTO `projects` VALUES (
	1,
	"Timekeeper",
	"2017-10-28 05:56:55",
	"",
	"an ncurses app to keep track of work time"
);
