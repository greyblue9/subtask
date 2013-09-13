<?php

// TaskList server API
// Retrieve TaskList json data by requesting to /api.php?employee_id={#}

date_default_timezone_set('America/New_York');

require_once('include/common.inc.php');


if (array_key_exists("employee_id", $_GET))
{
	$EmployeeID = intval($_GET["employee_id"]);
}
else
{
	// respond with error
	print("TaskList error: No employee_id parameter given");
	exit;
}



// process action
if (array_key_exists("action", $_GET))
{
	switch ($_GET["action"])
	{
		case "complete":
			if (array_key_exists("task", $_GET))
			{
				$TaskID = intval($_GET["task"]);
				DB::query(
					'update ' . TABLE_JOB . 
					' set ' . JOB_COMPLETED . ' = 1 ' . 
					' where ' . JOB_ID . ' = ' . $TaskID
				);
			}
			else
			{
				print("TaskList complete action error: No task parameter given");
				exit;
			}
			break;
			
		default:
			print("TaskList action error: Unknown action type '{$_GET["action"]}'");
			exit;
	}
}






$Res = DB::query('select EmployeeName from employee where EmployeeID = ' . $EmployeeID);
$EmployeeName = $Res[0]['EmployeeName'];


$JobsJSON = '[' . JSON::renderJobJSONForEmployee($EmployeeID) . ']';


print($JobsJSON);


exit;

