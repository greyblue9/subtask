

var unsavedChanges = false;
var titlesByID = {};


function getTitleByID(pID)
{
    return titlesByID[pID];
}


$(document).ready(function() {

	$("#Delete").click(function() {
		var response = confirm("Are you sure you want to delete this task?\n\nAny current subtasks will no longer be shown.");
		if (!response) return;
		
		x_deleteTask($currentJob.attr("jobid"), ajaxChangesDone);
		showNote("Deleting task...");
		$("#Cancel").click();
	});
	
	$("#Cancel").click(function() {
		$("#EditArea").hide();
		unsavedChanges = false;
		$currentJob = null;
		
		highlight(0);
	});
	
	$("#EditArea").click(function() {
	    $("#datepicker").hide();
	});
	
	
	activateJobTable();

	$("#datepicker").hide().datepicker({
		altFormat: 'yy-mm-dd',
		onSelect: pickDate
	});
	
	$("#DueTime").blur(function() {
	    updateDueTime();
	});
	
	$("#PickPriority span").click(function() {
	    changePriorityTo($(this).attr("priority"));
	});
	
	$("#AddTask").click(function() {
	    addNewTask();
	});
	
	$("#AddSubTask").click(function() {
	    addNewSubTask();
	});
	
	$("#TaskTitle").blur(updateTaskTitle);
	
	$("#TaskDescription").blur(updateTaskDescription);
	
	$("#HideCompleted").click(updateHideCompleted);

});



function activateJobTable()
{
	$(".Job").click(function() {
		jobClicked($(this));
	});
	
	$(".JobTitle").hover(function() {
	    $JD = $(this).parent().find("div.JobDescription");
	    if ($JD.html().length > 3)
	    {
	        $JD.show();
	    }
	}, function() {
	    $JD = $(this).parent().find("div.JobDescription");
	    $JD.hide();
	})
	
	$(".JobDone").click(function(event) {
	    event.stopImmediatePropagation();
	    $Job = $(this).parent().parent();
	    
	    showNote("Saving and re-ordering...");
	    
	    if ($Job.attr("completed") == "1")
	    {
	        $Job.attr("completed", "0");
	        $Job.removeClass("Completed");
	        x_setCompletion($Job.attr("jobid"), 0, ajaxChangesDone);
	    }
	    else
	    {
	        $Job.attr("completed", "1");
	        $Job.addClass("Completed");
	        x_setCompletion($Job.attr("jobid"), 1, ajaxChangesDone);
	    }
	    
	    nextHighlightJob = $Job.attr("jobid");
	});
	
	$(".CollapsableEC").click(function(event) {
	    event.stopImmediatePropagation();
	    $Job = $(this).parent().parent();
	    
	    showNote("Collapsing...");
	    x_setCollapsed($Job.attr("jobid"), 1, ajaxChangesDone);
	    nextHighlightJob = $Job.attr("jobid");
	});
	
	$(".ExpandableEC").click(function(event) {
	    event.stopImmediatePropagation();
	    $Job = $(this).parent().parent();
	    
	    showNote("Expanding...");
	    x_setCollapsed($Job.attr("jobid"), 0, ajaxChangesDone);
	    nextHighlightJob = $Job.attr("jobid");
	});
	
	titlesByID = {};
	$(".Job").each(function(i) {
	    $Job = $(this);
	
	    $Job.removeClass("Even");
	    if (i % 2) {
	        $Job.addClass("Even");
	    }
	    
	    titlesByID[$Job.attr("jobid")] = $Job.attr("mytitle");
	});
}







function editJob($Job)
{
    var ID = Number($Job.attr("jobid"));
    
    var myTitle = $Job.attr("mytitle");
	$("#TaskTitle").val(myTitle);
	$("#TaskName").html(myTitle);
	
	$("#TaskDescription").val($Job.find(".JobDescription").html());
	
    $("#PickPriority span").removeClass("Active");
    $("#PickPriority span.Priority" + $Job.attr("priority")).addClass("Active");
    
    $("#Completed").html(   ($Job.attr("completed") == "1")? "Yes" : "No"    );
	
	// Due date
	if ($Job.attr("duetype") != "None")
	{
		$("#DueDate").html($Job.attr("duedate"));
		$("#DueDateChange").attr("href", "javascript:changeDate(" + ID + ")").show();
		$("#DueDateRemove").attr("href", "javascript:removeDate(" + ID + ")").show();
		$("#DueDateAdd").hide();
	}
	else
	{
		$("#DueDate").html('');
		$("#DueDateChange").hide();
		$("#DueDateRemove").hide();
		$("#DueDateAdd").attr("href", "javascript:addDate(" + ID + ")").show();
	}
	
	// Due time
	if ($Job.attr("duetype") == "Time")
	{
		$("#DueTime").val($Job.attr("duetime")).show();
		$("#DueTimeRemove").attr("href", "javascript:removeTime(" + ID + ")").show();
		$("#DueTimeAdd").hide();
	}
	else
	{
		$("#DueTime").hide();
		$("#DueTimeRemove").hide();
		$("#DueTimeAdd").attr("href", "javascript:addTime(" + ID + ")").show();
	}
	
	// Depends on task
	var DependsID = Number($Job.attr("depends"));
	var $DependsLink = $("#DependsLink");
	if (DependsID)
	{
		$DependsLink.html(getTitleByID(DependsID));
		$DependsLink.attr("href", "javascript:highlight(" + DependsID + ")").show();
		$("#DependsChange").attr("href", "javascript:changeDependencyFor(" + ID + ")").show();
		$("#DependsRemove").attr("href", "javascript:removeDependencyFor(" + ID + ")").show();
		$("#DependsAdd").hide();
	}
	else
	{
		$DependsLink.hide();
		$("#DependsChange").hide();
		$("#DependsRemove").hide();
		$("#DependsAdd").attr("href", "javascript:addDependencyFor(" + ID + ")").show();
	}
	
	// Task accomplished (parent task)
	var AccomplishesID = Number($Job.attr("accomplishes"));
	var $AccomplishesLink = $("#AccomplishesLink");
	if (AccomplishesID)
	{
		$AccomplishesLink.html(getTitleByID(AccomplishesID));
		$AccomplishesLink.attr("href", "javascript:highlight(" + AccomplishesID + ")").show();
		$("#AccomplishesChange").attr("href", "javascript:changeAccomplishesFor(" + ID + ")").show();
		$("#AccomplishesRemove").attr("href", "javascript:removeAccomplishesFor(" + ID + ")").show();
		$("#AccomplishesAdd").hide();
	}
	else
	{
		$AccomplishesLink.hide();
		$("#AccomplishesChange").hide();
		$("#AccomplishesRemove").hide();
		$("#AccomplishesAdd").attr("href", "javascript:addAccomplishesFor(" + ID + ")").show();
	}
	
	// Priority source (if priority inherited from subtask)
	var PrioritySourceID = Number($Job.attr("prioritysource"));
	if (PrioritySourceID)
	{
	    var $PrioritySourceLink = $("#PrioritySourceLink");
	    $PrioritySourceLink.html("task #" + PrioritySourceID);
	    $PrioritySourceLink.attr("href", "javascript:highlight(" + PrioritySourceID + ")");
	    $("#PriorityNote").show();
	}
	else
	{
	    $("#PriorityNote").hide();
	}
	
	$("#EditArea").show();
	
	$currentJob = $Job;
	highlight(ID);
}


String.prototype.trim = function () {
    return this.replace(/^\s*/, "").replace(/\s*$/, "");
}




var $currentJob = null;

var NO_ACTION = 0;
var ACTION_CHANGE_DEPENDENCY = 1;
var ACTION_ADD_DEPENDENCY = 2;
var ACTION_CHANGE_ACCOMPLISHES = 3;
var ACTION_ADD_ACCOMPLISHES = 4;

var currentAction = NO_ACTION;


var nextHighlightJob = 0;




function changePriorityTo(newPriority)
{
	$currentJob.attr("priority", newPriority);
	editJob($currentJob);
	
	x_setPriorityFor($currentJob.attr("jobid"), newPriority, ajaxChangesDone);
	showNote("Adjusting priority...");
	nextHighlightJob = $currentJob.attr("jobid");
}




function addDate()
{
    $("#datepicker").datepicker('setDate', null).show();
}

function changeDate()
{
	$("#datepicker").datepicker('setDate', $.datepicker.parseDate('yy-mm-dd', $currentJob.attr("duedate"))).show();
}

function removeDate()
{
	$currentJob.attr("duedate", "");
	$currentJob.attr("duetype", "None");
	editJob($currentJob);
	
	x_removeDueDateFor($currentJob.attr("jobid"), ajaxChangesDone);
	showNote("Removing due date...");
	nextHighlightJob = $currentJob.attr("jobid");
}

function pickDate(pDateText, pInst)
{

    var mmDdYyyy = pDateText;
    var exp = mmDdYyyy.split('/');
    var month = exp[0];
    var day = exp[1];
    var year = exp[2];
    
    var newDate = year + '-' + month + '-' + day;
    $currentJob.attr("duedate", newDate);
   
    if ($currentJob.attr("duetype") != "Time")
    {
        $currentJob.attr("duetype", "Date");
    }
    
	$("#datepicker").hide();
	editJob($currentJob);
	
	x_changeDueDateFor($currentJob.attr("jobid"), newDate, ajaxChangesDone);
	showNote("Saving due date...");
	nextHighlightJob = $currentJob.attr("jobid");
}



function addTime()
{
    if ($currentJob.attr("duetype") == "None")
    {
        showNote("Specify the date due first.", 1000);
        addDate();
        return;
    }
    
	$currentJob.attr("duetime", "12:00 am");
	$currentJob.attr("duetype", "Time");
	editJob($currentJob);
}

function removeTime()
{
	$currentJob.attr("duetime", "");
	$currentJob.attr("duetype", "Date");
	editJob($currentJob);
		
	x_removeTimeFor($currentJob.attr("jobid"), ajaxChangesDone);
	showNote("Removing due time...");
	nextHighlightJob = $currentJob.attr("jobid");
}



function updateDueTime()
{
    var Time = $("#DueTime").val();
    
    var exp = Time.split(':');
    var hr = exp[0];
    
    if (exp.length != 2)
    {
        unknownTime();
        return;
    }
    
    var loc = exp[1].search(/[apAP]/);
    if (loc != -1)
    {
        var ap = exp[1].substr(loc, 1).toLowerCase();
        if (ap == 'a') var ampm = 'AM';
        else var ampm = 'PM';
    }
    else
    {
        unknownTime();
        return;
    }
    
    var min = jQuery.trim(exp[1].substr(0, loc));
    
    var TimeStr = hr + ':' + min + ' ' + ampm;
    
	x_changeDueTimeFor($currentJob.attr("jobid"), TimeStr, ajaxChangesDone);
	showNote("Updating...");
	nextHighlightJob = $currentJob.attr("jobid");
}

function unknownTime()
{
    showNote("Unknown time format. Example: <b>3:45 PM</b>", 1000);
}



function updateTaskTitle()
{
    var Title = $("#TaskTitle").val();
    
    $currentJob.attr("mytitle", Title);
	x_changeTitleFor($currentJob.attr("jobid"), Title, ajaxChangesDone);
	showNote("Saving title...");
	nextHighlightJob = $currentJob.attr("jobid");
}

function updateTaskDescription()
{
    var Desc = $("#TaskDescription").val();
    
    $currentJob.find(".JobDescription").html(Desc);
	x_changeDescFor($currentJob.attr("jobid"), Desc, ajaxChangesDone);
	showNote("Saving description...");
	nextHighlightJob = $currentJob.attr("jobid");
}

function updateHideCompleted()
{
	var val = $("#HideCompleted").attr("checked")? 1: 0;
	
	x_changePreference("HideCompleted", val, ajaxChangesDone);
	showNote("Saving task visibility preferences...");
}









function changeDependencyFor(pJobID)
{
	var $Job = $(".Job[jobid=" + pJobID + "]");
	var Label = "Click on the task that '<b>" + $Job.attr("mytitle") + "</b>' depends on.";
	Label += getCancelLink();
	
	showNote(Label);
	currentAction = ACTION_CHANGE_DEPENDENCY;
}

function removeDependencyFor(pJobID)
{
	var response = confirm("Are you sure you want to remove this dependency?");
	if (!response) return;
	
	x_removeDependencyFor(pJobID, ajaxChangesDone);
	nextHighlightJob = pJobID;
	showNote("Updating...");
}

function addDependencyFor(pJobID)
{
	changeDependencyFor(pJobID);
}

function changeAccomplishesFor(pJobID)
{
	var $Job = $(".Job[jobid=" + pJobID + "]");
	var Label = "Click on the task that '<b>" + $Job.attr("mytitle") + "</b>' accomplishes.";
	Label += getCancelLink();
	
	showNote(Label);
	currentAction = ACTION_CHANGE_ACCOMPLISHES;
}

function removeAccomplishesFor(pJobID)
{
	var response = confirm("Are you sure you want to make this task independent?\n\nOnce you do this, it will no longer be listed as a subtask.");
	if (!response) return;
	
	x_removeAccomplishesFor(pJobID, ajaxChangesDone);
	nextHighlightJob = pJobID;
	showNote("Updating...");
}

function addAccomplishesFor(pJobID)
{
	changeAccomplishesFor(pJobID);
}

function jobClicked($Job)
{
	if (currentAction == NO_ACTION) {
	
	    if ($currentJob && $currentJob.attr("jobid") == $Job.attr("jobid"))
	    {
	        $("#Cancel").click();
	        return;
	    }
	    
	    editJob($Job);
	    return;
	}
	
	var CurrentJobID = $currentJob.attr("jobid");
	var ClickedJobID = $Job.attr("jobid");

	if (currentAction == ACTION_CHANGE_DEPENDENCY)
	{
	    if (ClickedJobID == CurrentJobID)
	    {
	        showNote("A task cannot depend on itself.", 1000);
	        return;
	    }
	    
		$currentJob.attr("depends", ClickedJobID);
		editJob($currentJob);
		
		x_changeDependencyFor(CurrentJobID, ClickedJobID, ajaxChangesDone);
		nextHighlightJob = CurrentJobID;
		showNote("Updating...");
	}
	else if (currentAction == ACTION_CHANGE_ACCOMPLISHES)
	{
	    if (ClickedJobID == CurrentJobID)
	    {
	        showNote("A task cannot accomplish itself. Or can it?", 1000);
	        return;
	    }
	    
		$currentJob.attr("accomplishes", ClickedJobID);
		editJob($currentJob);
		
		x_changeAccomplishesFor(CurrentJobID, ClickedJobID, ajaxChangesDone);
		nextHighlightJob = CurrentJobID;
		showNote("Updating...");
	}
	
	currentAction = NO_ACTION;
}










function addNewTask()
{
    var $highlightedJob = $(".Job.Highlight");
    var JobID = $highlightedJob.attr("jobid");
    if (!JobID)
    {
        x_addNewTask(EmployeeID, addTask_Done);
    }
    else
    {
        if (Number($highlightedJob.attr("accomplishes")))
        {
            x_addNewTask(EmployeeID, Number($highlightedJob.attr("accomplishes")), addTask_Done);
        }
        else
        {
            x_addNewTask(EmployeeID, addTask_Done);
        }
    }

    showNote("Creating new task...");
}

function addNewSubTask()
{
    var JobID = $(".Job.Highlight").attr("jobid");
    if (!JobID)
    {
        showNote("Select a parent task first.");
        return;
    }

    x_addNewTask(EmployeeID, JobID, addTask_Done);
    showNote("Creating new subtask...");
}

function addTask_Done(pResponse)
{
	hideNote();
	
	$("#JobTable").html(pResponse.Table);
	activateJobTable();
	
	editJob(  $(".Job[jobid=" + pResponse.NewJob + "]")  );
	
	highlight(pResponse.NewJob);
	nextHighlightJob = 0;
}




























function highlight(pJobID)
{
	$(".Highlight").removeClass("Highlight");
	
	$(".Job[jobid=" + pJobID + "]").addClass("Highlight");
}

function getCancelLink()
{
	return ' &nbsp; <a href="javascript:cancelAction()" style="color: white">Cancel</a>';
}

function cancelAction()
{
	currentAction = NO_ACTION;
	hideNote();
}

function showNote(pText, pDuration)
{
	$Note = $("#Note");
	$Note.html(pText);
	
	
	if (!pDuration)
	{
		$Note.show();
	}
	else
	{
		$Note.show();
		setTimeout(function(){$Note.fadeOut()}, pDuration);
	}
}

function hideNote()
{
	$Note.fadeOut(500);
}


function ajaxChangesDone(pResponse)
{
	hideNote();
	
	$("#JobTable").html(pResponse);
	activateJobTable();
	
	if (nextHighlightJob != 0)
	{
		highlight(nextHighlightJob);
		nextHighlightJob = 0;
	}
}

