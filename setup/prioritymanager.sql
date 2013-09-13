# HeidiSQL Dump 
#
# --------------------------------------------------------
# Host:                         127.0.0.1
# Database:                     prioritymanager
# Server version:               5.1.30-community-log
# Server OS:                    Win32
# Target compatibility:         ANSI SQL
# HeidiSQL version:             4.0
# Date/time:                    2009-09-06 01:56:14
# --------------------------------------------------------



#
# Table structure for table 'employee'
#

/*CREATE TABLE "employee" (
  "EmployeeID" int(11) unsigned NOT NULL AUTO_INCREMENT,
  "EmployeeName" varchar(64) DEFAULT NULL,
  "EmployeeRoleID" tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY ("EmployeeID")
) AUTO_INCREMENT=3;
*/


#
# Dumping data for table 'employee'
#

LOCK TABLES "employee" WRITE;
INSERT INTO "employee" ("EmployeeID", "EmployeeName", "EmployeeRoleID") VALUES
	('1','David Reilly',1);
INSERT INTO "employee" ("EmployeeID", "EmployeeName", "EmployeeRoleID") VALUES
	('2','Chase Flynn',NULL);
UNLOCK TABLES;


#
# Table structure for table 'job'
#

CREATE TABLE "job" (
  "JobID" int(11) unsigned NOT NULL AUTO_INCREMENT,
  "JobEmployeeID" int(11) unsigned DEFAULT NULL,
  "JobTitle" varchar(255) DEFAULT NULL,
  "JobDescription" text,
  "JobFollowsJobID" int(11) unsigned DEFAULT NULL,
  "JobAccomplishesJobID" int(11) unsigned DEFAULT NULL,
  "JobPriority" int(10) unsigned DEFAULT '5',
  "JobDue" datetime DEFAULT NULL,
  "JobDueType" enum('None','Date','Time') DEFAULT 'None',
  "JobCompleted" tinyint(1) unsigned DEFAULT '0',
  PRIMARY KEY ("JobID")
) AUTO_INCREMENT=43;



#
# Dumping data for table 'job'
#

LOCK TABLES "job" WRITE;
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('32','1','Schedule a meeting with embedded TA','',NULL,NULL,'5','2009-09-06 19:00:00','Date',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('35','1','Call james',NULL,NULL,NULL,'6','2009-09-04 19:00:00','Date',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('2','1','Test/debug discussion board',NULL,NULL,'1','2',NULL,'None',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('36','1','Koofers stuff',NULL,NULL,NULL,'8','2009-09-06 19:00:00','Date',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('6','1','Implement instructor pages',NULL,NULL,'5','1','2009-09-09 19:00:00','Date',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('25','1','Install Xilinx on Laptop','',NULL,NULL,'5','2009-09-05 14:30:00','Time',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('8','1','Implement upload/rate page',NULL,NULL,'5','6',NULL,'None',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('37','1','Finish LiteGraffiti app',NULL,NULL,NULL,'7','2009-09-18 19:00:00','Date',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('31','1','Take the car to powhatan',NULL,NULL,NULL,'5','2009-09-11 19:00:00','Date',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('24','1','Embedded group TA meeting',NULL,NULL,NULL,'5','2009-09-05 14:30:00','Time',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('26','1','AI read ch. 2',NULL,NULL,NULL,'5','2009-09-08 11:00:00','Time',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('27','1','AI HW 1',NULL,NULL,NULL,'5','2009-09-08 11:00:00','Time',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('28','1','Network App HW',NULL,NULL,NULL,'5','2009-09-09 23:59:00','Time',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('34','1','Write background report',NULL,NULL,NULL,'5','2009-09-03 19:00:00','Date',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('30','1','Install Xilinx on laptop','',NULL,NULL,'5','2009-09-05 19:00:00','Date',1);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('38','1','Get rent, etc. straightened out',NULL,NULL,NULL,'3',NULL,'None',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('39','1','Write letter to grandma',NULL,NULL,NULL,'6',NULL,'None',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('40','1','Work on pinball machine',NULL,NULL,NULL,'1',NULL,'None',0);
INSERT INTO "job" ("JobID", "JobEmployeeID", "JobTitle", "JobDescription", "JobFollowsJobID", "JobAccomplishesJobID", "JobPriority", "JobDue", "JobDueType", "JobCompleted") VALUES
	('41','1','Go job-hunting',NULL,NULL,NULL,'3',NULL,'None',0);
UNLOCK TABLES;


#
# Table structure for table 'jobrequest'
#

CREATE TABLE "jobrequest" (
  "JobRequestID" int(11) unsigned DEFAULT NULL,
  "JobRequestRequestingEmployeeID" int(11) unsigned DEFAULT NULL,
  "JobRequestAssignedEmployeeID" int(11) unsigned DEFAULT NULL,
  "JobRequestJobID" int(11) unsigned DEFAULT NULL
);



#
# Dumping data for table 'jobrequest'
#

# No data found.



#
# Table structure for table 'role'
#

CREATE TABLE "role" (
  "RoleID" int(11) unsigned NOT NULL AUTO_INCREMENT,
  "RoleName" varchar(50) DEFAULT NULL,
  "RoleDescription" varchar(255) DEFAULT NULL,
  PRIMARY KEY ("RoleID")
) AUTO_INCREMENT=3;



#
# Dumping data for table 'role'
#

LOCK TABLES "role" WRITE;
INSERT INTO "role" ("RoleID", "RoleName", "RoleDescription") VALUES
	('1','Site developer','Writes the code for the web site itself');
INSERT INTO "role" ("RoleID", "RoleName", "RoleDescription") VALUES
	('2','Data developer','Writes algorithms and programs to manage, create, and organize site data');
UNLOCK TABLES;
