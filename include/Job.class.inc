<?php

require_once('common.inc.php');

class Job
{
	protected $Fields;
	
	public $ID;
	public $EmployeeID;
	public $Title;
	public $Description;
	public $FollowsJobID;
	public $AccomplishesJobID;
	public $Priority;
	public $Due;
	public $DueType;
	public $Completed;
	public $Collapsed;
	
	public $PriorityWasFromSubtask = false;
	public $PrioritySource = 0;
	
	public $SubtaskIDs = array(); // array of job IDs which help accomplish this job
	
	static $Jobs; // copy of master jobs array, indexed by JobID
	/* array(
			1 => [Job object],
			3 => [Job object]
	)
	*/
	
	function __construct($pFields, &$pJobs = null)
	{
		$this->ID = intval($pFields[JOB_ID]);
		$this->EmployeeID = intval($pFields[JOB_EMPLOYEE_ID]);
		$this->Title = $pFields[JOB_TITLE];
		$this->Description = $pFields[JOB_DESCRIPTION];
		$this->FollowsJobID = intval($pFields[JOB_FOLLOWS_JOB_ID]);
		$this->AccomplishesJobID = intval($pFields[JOB_ACCOMPLISHES_JOB_ID]);
		$this->Priority = intval($pFields[JOB_PRIORITY]);
		$this->Due = $pFields[JOB_DUE];
		$this->DueType = $pFields[JOB_DUE_TYPE];
		$this->Completed = intval($pFields[JOB_COMPLETED]);
		$this->Collapsed = intval($pFields[JOB_COLLAPSED]);
		
		if (self::$Jobs == null && $pJobs != null)
		{
			self::$Jobs = &$pJobs;
		}
		
		if (self::$Jobs == null)
		{
			print('First job object must be instantiated with a reference to the DB jobs array.');
			exit;
		}
	}
	
	function updateParentTasks()
	{
		if ($this->AccomplishesJobID)
		{
			// update parent task to reflect this subtask
			if (array_key_exists($this->AccomplishesJobID, self::$Jobs))
			{
				$ParentTask = self::$Jobs[ $this->AccomplishesJobID ];
				if (array_search($this->ID, $ParentTask->SubtaskIDs) === false)
				{
					$ParentTask->addSubtaskJobID($this->ID);
				}
				
				if ($this->Priority > $ParentTask->Priority && !$this->Completed)
				{
					$ParentTask->Priority = $this->Priority;
					$ParentTask->PriorityWasFromSubtask = true;
					$ParentTask->PrioritySource = $this->ID;
					
					$ParentTask->updateParentTasks();
				}
			}
		}
	}
	
	function addSubtaskJobID($pSubtaskJobID)
	{
		$this->SubtaskIDs[] = $pSubtaskJobID;
	}
	
	function isSubtask()
	{
		return ($this->AccomplishesJobID)? true: false;
	}
	
	function render($pIndentLevel = 0, $pRenderMode = HTML::HTMLRendering)
	{
		if ($pRenderMode == HTML::HTMLRendering)
		{
			$HTML = HTML::getJobRow($this, $pIndentLevel);
			
			if (! $this->Collapsed)
			{
				foreach ($this->SubtaskIDs as $SubtaskID)
				{
					$HTML .= self::$Jobs[$SubtaskID]->render($pIndentLevel + 1, $pRenderMode);
				}
			}
			
			return $HTML;
		}
		else if ($pRenderMode == JSON::JSONRendering)
		{
			$JSON = JSON::getJobJSON($this, $pIndentLevel);
			
			if (! $this->Collapsed)
			{
				foreach ($this->SubtaskIDs as $SubtaskID)
				{
					$JSON .= ', ' . self::$Jobs[$SubtaskID]->render($pIndentLevel + 1, $pRenderMode);
				}
			}
			
			return $JSON;
		}
	}
	
}