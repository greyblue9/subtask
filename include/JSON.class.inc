<?php

require_once('common.inc.php');

class JSON
{
	const JSONRendering = 'JSONRendering';
	
	static function renderJobJSONForEmployee($EmployeeID)
	{
		return HTML::renderJobTableForEmployee($EmployeeID, self::JSONRendering, HTML::NeverShowCompleted);
	}
	
	static function getJobJSON($Job, $pIndentLevel = 0)
	{
		$JobObj = array(
			'indent_lvl' => $pIndentLevel,
			'id' => $Job->ID,
			'title' => $Job->Title,
			'description' => $Job->Description,
			'due' => strtotime($Job->Due),
			'due_str' => HTML::getJobDueStr($Job),
			'time_left' => HTML::getRawTimeRemaining($Job),
			'priority' => $Job->Priority,
			'collapsed' => $Job->Collapsed
		);
		
		return json_encode($JobObj);
	}
	
}