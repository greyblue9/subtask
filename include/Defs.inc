<?php

// DBR 2013-09-12: I would never code this way again. Ugh.


define('TABLE_JOB' , 'job');
define('TABLE_PREF', 'pref');


define('JOB_ID', 'JobID');
define('JOB_EMPLOYEE_ID', 'JobEmployeeID');
define('JOB_TITLE', 'JobTitle');
define('JOB_DESCRIPTION', 'JobDescription');
define('JOB_FOLLOWS_JOB_ID', 'JobFollowsJobID');
define('JOB_ACCOMPLISHES_JOB_ID', 'JobAccomplishesJobID');
define('JOB_PRIORITY', 'JobPriority');
define('JOB_DUE', 'JobDue');
define('JOB_DUE_TYPE', 'JobDueType');
define('JOB_COMPLETED', 'JobCompleted');
define('JOB_COLLAPSED', 'JobCollapsed');


define('PREF_ID', 'PrefID');
define('PREF_EMPLOYEE_ID', 'PrefEmployeeID');
define('PREF_NAME', 'PrefName');
define('PREF_VALUE', 'PrefValue');


define('TIME_REMAINING', 'TimeRemaining');


define('EMPLOYEE_ID', 'EmployeeID');



$DefaultPrefs = array(
	'HideCompleted' => 0
);