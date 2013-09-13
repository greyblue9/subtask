<?php

require_once('common.inc.php');

class HTML
{
	const HTMLRendering = 'HTMLRendering';
	const AllowCompleted = true;
	const NeverShowCompleted = false;

	static $IsEven;
	static $IndentOn;
	
	static function renderJobTableForEmployee($EmployeeID, $RenderMode = self::HTMLRendering, $AllowCompletedTasks = self::AllowCompleted)
	{

		$PrefWhereAdditions = '';
		
		if ($AllowCompletedTasks)
		{
			$HideCompleted = getPref('HideCompleted', $EmployeeID);
			if ($HideCompleted)
			{
				$PrefWhereAdditions = ' and (JobCompleted = 0 or (JobCompleted = 1 and JobAccomplishesJobID is not null)) ';
			}
		}
		else
		{	
			$PrefWhereAdditions = ' and JobCompleted = 0 ';
		}
		

		$Jobs = DB::query("select * from " . TABLE_JOB . " where JobEmployeeID = $EmployeeID $PrefWhereAdditions order by JobCompleted asc, (NOW() - JobDue) desc, JobPriority desc", JOB_ID);

		foreach ($Jobs as &$Job)
		{
			// convert job rows to Job objects
			$Job = new Job($Job, $Jobs);
		}
		foreach ($Jobs as &$Job)
		{
			$Job->updateParentTasks();
		}

		$Output = '';
		foreach ($Jobs as &$Job)
		{
			if (! $Job->isSubtask())
			{
				if ($RenderMode == JSON::JSONRendering && $Output != '')
				{
					$Output .= ', ';
				}
				
				$Output .= $Job->render(0, $RenderMode);
			}
		}
		
		return $Output;
	}
	
	static function renderHTMLHeader()
	{
		return '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
		<html>
		<head>
			<title>Priority Manager</title>
			<link rel="stylesheet" type="text/css" href="src/main.css" />
			<link rel="stylesheet" type="text/css" href="src/jquery_ui_custom_theme_for_calendar.css" />
			<link REL="SHORTCUT ICON" HREF="favicon.ico">
		</head>
		<body>
		';
	}
	
	static function sIfPlural($Count)
	{
		if ($Count) return 's';
		return '';
	}
	
	static function getBlock($pBlockClass = "")
	{
		return '<div class="Block ' . $pBlockClass . '">&nbsp;</div>';
	}
	
	static function getJobRow($Job, $pIndentLevel = 0)
	{
		if (is_null(self::$IndentOn))
		{
			self::$IndentOn = array();
		}
		if (! array_key_exists($pIndentLevel, self::$IndentOn))
		{
			self::$IndentOn[] = false;
		}
			
		
		$MainHTML = '';
		
		for ($IndentLevelI=1; $IndentLevelI<=$pIndentLevel; $IndentLevelI++)
		{
			// IndentOn?
			if (array_key_exists($IndentLevelI, self::$IndentOn) && self::$IndentOn[$IndentLevelI] == true)
			{
				// IndentLevelI is TaskIndentLevel?
				if ($IndentLevelI == $pIndentLevel)
				{	
					$ParentTask = Job::$Jobs[$Job->AccomplishesJobID];
					// Parent's last subtask?
					if ($ParentTask->SubtaskIDs[ count($ParentTask->SubtaskIDs) - 1 ] == $Job->ID)
					{
						$MainHTML .= self::getBlock("RedIndent");
						self::$IndentOn[$IndentLevelI] = false;
					}
					else
					{
						$MainHTML .= self::getBlock("OrangeIndent");
					}
				}
				else
				{
					$MainHTML .= self::getBlock("YellowIndent");
				}
			}
			else
			{
				$MainHTML .= self::getBlock();
			}
		}
		
		if (count($Job->SubtaskIDs))
		{
			if (! $Job->Collapsed)
			{
				$MainHTML .= self::getBlock("CollapsableEC");
			}
			else
			{
				$MainHTML .= self::getBlock("ExpandableEC");
			}
			
			if (! array_key_exists($pIndentLevel + 1, self::$IndentOn))
			{
				self::$IndentOn[] = false;
			}
			self::$IndentOn[$pIndentLevel + 1] = true;
		}
		else
		{
			if ($pIndentLevel != 0)
			{
				$MainHTML .= self::getBlock("EmptyEC");
			}
			else
			{
				$MainHTML .= self::getBlock();
			}
		}
		
		$MainHTML .= self::getBlock("JobDone");
		


		$Red = null; // byref
		$JobTimeRemaining = self::getJobTimeRemaining($Job, $Red);
		$JobDueStr = self::getJobDueStr($Job); // due day/time

		$TitleHTML = '<div class="JobTitle ' . (($Red)? 'Red': '') . '">' . $Job->Title . (($Job->Description)? ' <img src="/img/more.gif" />' : '') . '</div>';
		$DueDatetime = strtotime($Job->Due);
		
		return '
		<div class="Job ' . (($Job->Completed)? 'Completed': '') . '"
		jobid="' . $Job->ID . '"
		mytitle="' . $Job->Title . '"
		depends="' . $Job->FollowsJobID . '"
		accomplishes="' . $Job->AccomplishesJobID . '"
		duedate="' . (($Job->DueType != 'None')? date("Y-m-d", $DueDatetime): '0') . '"
		duetime="' . (($Job->DueType == 'Time')? date("g:i A", $DueDatetime): '0') . '"
		duetype="' . $Job->DueType . '"
		completed="' . $Job->Completed . '"
		priority="' . $Job->Priority . '"
		prioritysource="' . $Job->PrioritySource . '"
		collaped="' . $Job->Collapsed . '"
		>
			<div class="JobPriority Priority' . $Job->Priority . '">' . $Job->Priority . (($Job->PriorityWasFromSubtask)?'&raquo;':'') . '</div>
			<div class="JobDue">' . $JobDueStr . '</div>
			<div class="JobTimeRemaining">' . $JobTimeRemaining . '</div>
			<div class="JobMain">
				' . $MainHTML . $TitleHTML . '
				<div class="Clear"></div>
				<div class="JobDescription">' . nl2br($Job->Description) . '</div>
			</div>
			<div class="Clear"></div>
		</div>';
	}
	
	static function renderJobHeader()
	{
		return '
		<div class="Header">
			<div class="JobPriority">Pri.</div>
			<div class="JobDue">Due</div>
			<div class="JobTimeRemaining">Time left</div>
			<div class="JobMain">Job title/status</div>
			<div class="Clear"></div>
		</div>';
	}
	
	static function getRawTimeRemaining($Job, &$oWeeks = null, &$oDays = null, &$oHours = null, &$oMinutes = null, &$oOverdue = null)
	{
		if (!is_null($Job->Due) && !$Job->Completed)
		{
			$Seconds = strtotime($Job->Due) - time();
			
			if ($Seconds < 0) 
			{	
				$Seconds = 0 - $Seconds;
				$Overdue = true;
			}
			else
			{
				$Overdue = false;
			}
			
			$Weeks = floor($Seconds / 604800);
			$Seconds -= $Weeks * 604800;
			
			$Days = floor($Seconds / 86400);
			$Seconds -= $Days * 86400;
			
			if ($Job->DueType == 'Time')
			{
				$Hours = floor($Seconds / 3600);
				$Seconds -= $Hours * 3600;
				
				$Minutes = floor($Seconds / 60);
				$Seconds -= $Minutes * 60;
			}
			else
			{
				$Hours = 0;
				$Minutes = 0;
				$Seconds = 0;
			}
			
			$Str = '';
			if ($Weeks) $Str .= $Weeks . 'w ';
			if ($Days) $Str .= $Days . 'd ';
			if ($Hours) $Str .= $Hours . 'h ';
			if ($Minutes) $Str .= $Minutes . 'm ';
			
			if ($oWeeks !== null) $oWeeks = $Weeks;
			if ($oDays !== null) $oDays = $Days;
			if ($oHours !== null) $oHours = $Hours;
			if ($oMinutes !== null) $oMinutes = $Minutes;
			if ($oOverdue !== null) $oOverdue = $Overdue;
		}
		else
		{
			$Str = '';
		}
		
		return $Str;
	}
	
	static function getJobTimeRemaining($Job, &$Red)
	{
		if (!is_null($Job->Due) && !$Job->Completed)
		{
			// set up by-reference variables
			$Weeks = 0;
			$Days = 0;
			$Hours = 0;
			$Minutes = 0;
			$Overdue = false;
			
			$Str = self::getRawTimeRemaining($Job, $Weeks, $Days, $Hours, $Minutes, $Overdue);
			
			if ($Weeks == 0 && $Days == 0 && $Hours == 0 && $Minutes == 0) 
			{
				$JobTimeRemaining = '<span class="Red">Due now</span>';
				$Red = true;
			}
			else if ($Overdue == true)
			{
				$JobTimeRemaining = '<span class="Red">' . $Str . ' overdue</span>';
				$Red = true;
			}
			else if ($Weeks = 0 && $Days < 1)
			{
				$JobTimeRemaining = '<span class="Red">' . $Str . '</span>';
				$Red = true;
			}
			else
			{
				$JobTimeRemaining = $Str;
			}
		}
		else
		{
			$JobTimeRemaining = '&nbsp;';
		}
		
		return $JobTimeRemaining;
	}
	
	static function getJobDueStr($Job)
	{
		if ($Job->Completed) return '&nbsp;';
		$Timestamp = strtotime($Job->Due);
		
		if ($Timestamp - time() < 0)
		{
			$Overdue = true;
		} else $Overdue = false;
		
		
		
		
		if (abs(strtotime($Job->Due) - time()) < 518400)
		{
			$DateStr = date("l", $Timestamp);
		}
		else if (abs(strtotime($Job->Due) - time()) < 31536000)
		{
			$DateStr = date("D n/d", $Timestamp);
		}
		else
		{
			$DateStr = date("n/d/y", $Timestamp);
		}
		
		
		
		switch ($Job->DueType)
		{
			case 'None':
				$JobDueStr = '&nbsp;';
				break;
			case 'Date':
				$JobDueStr = (($Overdue)?"Last ":"") . $DateStr;
				break;
			case 'Time':
				$JobDueStr = (($Overdue)?"Last ":"") . $DateStr . date(", g:i A", $Timestamp);
				break;
				
			default: // NULL
				$JobDueStr = '&nbsp;';
		}
		
		return $JobDueStr;
	}
	
}