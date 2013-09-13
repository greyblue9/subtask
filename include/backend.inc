<?php

require_once('common.inc.php');

function changeDependencyFor($JobID, $NewDependsJobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_FOLLOWS_JOB_ID . ' = ' . intval($NewDependsJobID) . ' where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeDependencyFor");


function changeAccomplishesFor($JobID, $NewAccomplishesJobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_ACCOMPLISHES_JOB_ID . ' = ' . intval($NewAccomplishesJobID) . ' where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeAccomplishesFor");


function removeDependencyFor($JobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_FOLLOWS_JOB_ID . ' = NULL where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("removeDependencyFor");


function removeAccomplishesFor($JobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_ACCOMPLISHES_JOB_ID . ' = NULL where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("removeAccomplishesFor");


function changeDueDateFor($JobID, $NewDate)
{
	// date comes in format: YYYY-MM-DD
	
	$Res = DB::query('select * from ' . TABLE_JOB . ' where ' . JOB_ID . ' = ' . intval($JobID));
	$DueDatetime = strtotime($Res[0][JOB_DUE]);
	$TimeStr = date("H:i:s", $DueDatetime);
	
	$FullDateTime = $NewDate . ' ' . $TimeStr;
	
	if ($Res[0][JOB_DUE_TYPE] == "None")
	{
		DB::query('update ' . TABLE_JOB . ' set ' . JOB_DUE_TYPE . ' = "Date" where ' . JOB_ID . ' = ' . intval($JobID));
	}

	DB::query('update ' . TABLE_JOB . ' set ' . JOB_DUE . ' = "' . mysql_real_escape_string($FullDateTime) . '" where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeDueDateFor");


function changeDueTimeFor($JobID, $NewTime)
{
	// time comes in format: HH:MM AM
	
	$Res = DB::query('select ' . JOB_DUE . ', ' . JOB_EMPLOYEE_ID . ' from ' . TABLE_JOB . ' where ' . JOB_ID . ' = ' . intval($JobID));
	$DueDatetime = strtotime($Res[0][JOB_DUE]);
	$DateStr = date("Y-m-d", $DueDatetime);
	
	$Exp = explode(":", $NewTime);
	$Hour = intval($Exp[0]);
	$Exp2 = explode(" ", $Exp[1]);
	$Min = intval($Exp2[0]);
	$AMPM = $Exp2[1];
	
	if ($AMPM == 'PM' && $Hour != 12) $Hour += 12;
	else if ($AMPM == 'AM' && $Hour == 12) $Hour -= 12;
	$TimeStr = $Hour . ':' . $Min . ':00';
	
	$FullDateTime = $DateStr . ' ' . $TimeStr;

	DB::query('update ' . TABLE_JOB . ' set ' . JOB_DUE . ' = "' . mysql_real_escape_string($FullDateTime) . '", ' . JOB_DUE_TYPE . ' = "Time" where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeDueTimeFor");



function removeTimeFor($JobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_DUE_TYPE . ' = "Date" where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("removeTimeFor");



function removeDueDateFor($JobID)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_DUE_TYPE . ' = "None", ' . JOB_DUE . ' = NULL where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("removeDueDateFor");


function setCompletion($JobID, $CompletionState)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_COMPLETED . ' = ' . intval($CompletionState) . ' where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("setCompletion");


function setPriorityFor($JobID, $Priority)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_PRIORITY . ' = ' . intval($Priority) . ' where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("setPriorityFor");


function addNewTask($EmployeeID, $pParentTaskID = null)
{
	if (is_null($pParentTaskID))
	{
		DB::query('insert into ' . TABLE_JOB . ' (' . JOB_EMPLOYEE_ID . ', ' . JOB_TITLE . ') VALUES (' . intval($EmployeeID) . ', "New Task")');
	}
	else
	{
		DB::query('insert into ' . TABLE_JOB . ' (' . JOB_EMPLOYEE_ID . ', ' . JOB_TITLE . ', ' . JOB_ACCOMPLISHES_JOB_ID
			. ') VALUES (' . intval($EmployeeID) . ', "New Subtask", ' . intval($pParentTaskID) . ')');
	}

	return array(
		'NewJob' => DB::getInsertID(),
		'Table' => HTML::renderJobTableForEmployee($EmployeeID)
	);
}

sajax_export("addNewTask");


function changeTitleFor($JobID, $Title)
{
	DB::get();
	
	$Title = str_replace('"', '', $Title);
	$Title = str_replace('\'', '', $Title);
	
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_TITLE . ' = "' . mysql_real_escape_string($Title) . '" where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeTitleFor");


function changeDescFor($JobID, $Desc)
{
	DB::get();
	
	$Desc = str_replace('"', '', $Desc);
	$Desc = str_replace('\'', '', $Desc);
	
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_DESCRIPTION . ' = "' . mysql_real_escape_string($Desc) . '" where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("changeDescFor");



function deleteTask($JobID)
{
	DB::query('delete from ' . TABLE_JOB . ' where ' . JOB_ID . ' = ' . intval($JobID));
	
	return getUserJobTable();
}

sajax_export("deleteTask");



function setCollapsed($JobID, $CollapsedState)
{
	DB::query('update ' . TABLE_JOB . ' set ' . JOB_COLLAPSED . ' = ' . intval($CollapsedState) . ' where ' . JOB_ID . ' = ' . intval($JobID));

	return getUserJobTable();
}

sajax_export("setCollapsed");


function changePreference($PrefName, $Value)
{
	global $DefaultPrefs;
	
	if (! array_key_exists($PrefName, $DefaultPrefs))
	{
		// unknown pref name
		return;
	}
	
	setPref($PrefName, $Value);
	return getUserJobTable();
}

sajax_export("changePreference");



function getUserJobTable()
{
	return HTML::renderJobTableForEmployee( $_SESSION[EMPLOYEE_ID] );
}








function getPref($PrefName, $EmployeeID = 0)
{
	if ($EmployeeID == 0)
	{
		// default -- get pref for current employee.
		$EmployeeID = $_SESSION[EMPLOYEE_ID];
	}
	
	global $DefaultPrefs;
	
	$Res = DB::query('select * from ' . TABLE_PREF . ' where ' . PREF_EMPLOYEE_ID . ' = ' . $_SESSION[EMPLOYEE_ID] . ' AND ' . PREF_NAME . ' = "' . $PrefName . '"');
	
	if (count($Res))
	{
		return $Res[0][PREF_VALUE];
	}
	else
	{
		return $DefaultPrefs[$PrefName];
	}
	exit;
}


function setPref($PrefName, $Value)
{
	global $DefaultPrefs;
	
	clearPref($PrefName);
	
	if ($Value == $DefaultPrefs[$PrefName])
	{
		return;
	}
	
	$Res = DB::query(
		'insert into ' . TABLE_PREF
		. '(' . PREF_EMPLOYEE_ID . ', '
		. PREF_NAME . ', '
		. PREF_VALUE
		. ') VALUES('
		. $_SESSION[EMPLOYEE_ID] . ', '
		. '"' . $PrefName . '", '
		. $Value . ')'
	);
}

function clearPref($PrefName)
{
	DB::query('delete from ' . TABLE_PREF . ' where ' . PREF_EMPLOYEE_ID . ' = ' . $_SESSION[EMPLOYEE_ID] . ' AND ' . PREF_NAME . ' = "' . $PrefName . '"');
}












