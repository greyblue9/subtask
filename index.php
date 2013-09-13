<?php

// I wonder if this is an issue: ...
date_default_timezone_set('America/New_York');

session_start();


require_once('include/common.inc.php');
sajax_init();

require_once('backend.inc'); // contains server-side AJAX calls
sajax_handle_client_request(); // an AJAX call would be handled here if it were actually happening


if (array_key_exists("employee_id", $_GET))
{
	$EmployeeID = intval($_GET["employee_id"]);
}
else
{
	$EmployeeID = 1;
}

$Res = DB::query('select EmployeeName from employee where EmployeeID = ' . $EmployeeID);
$EmployeeName = $Res[0]['EmployeeName'];

$_SESSION['EmployeeID'] = $EmployeeID;


$JobsHTML = HTML::renderJobTableForEmployee($EmployeeID);

$CheckedHTML = getPref("HideCompleted")? 'checked="true"': '';


?><?= HTML::renderHTMLHeader(); ?>

<div class="Wrapper">

	<div style="height: 109px; overflow: hidden;">
		<img src="/img/logo_sm.png" width="259" height="108" style="float: left; margin-right: 15px;" />
		<div class="Heading" style="float: left; padding: 55px 0px 0px 10px; ">
			<?= $EmployeeName ?>'s tasks
		</div>
		<div style="float: right; padding: 50px 10px 0px 10px;">
			<input type="checkbox" <?= $CheckedHTML ?> id="HideCompleted" />Hide completed root tasks
			<span style="background: #ff4433; color: white; font-size: 10px; font-weight: bold; padding: 2px">NEW!</span>
			<div style="margin-top: 5px;">
				<button id="AddSubTask">New subtask</button>
				<button id="AddTask">New task</button>
			</div>
		</div>
		<div class="Clear"></div>
	</div>
	
	<div type="text" id="datepicker" style="position: absolute;"></div>
	
	<div id="EditArea" class="Pad">
		<table>
			<tr>
				<td class="Subheading"><b>Editing task</b>:</td>
				<td>
					<input type="text" id="TaskTitle" style="width: 500px; font-size: 13pt;">
				</td>
			</tr>
			<tr>
				<td>Due date:</td>
				<td>
					<span id="DueDate"></span>
					<a href="#" id="DueDateChange" class="TaskTool">Change</a>
					<a href="#" id="DueDateRemove" class="TaskTool">Remove</a>
					<a href="#" id="DueDateAdd" class="TaskTool">Specify</a>
				</td>
			</tr>
			<tr>
				<td>Due time:</td>
				<td>
					<input type="text" value="12:00 PM" style="width: 100px;" id="DueTime"></input>
					<a href="#" id="DueTimeRemove" class="TaskTool">Remove</a>
					<a href="#" id="DueTimeAdd" class="TaskTool">Specify</a>
				</td>
			</tr>
			<tr>
				<td>Description:</td>
				<td>
					<textarea id="TaskDescription" style="display: block; width: 400px; height: 100px;"></textarea>
				</td>
			</tr>
			<tr>
				<td>Accomplishes:</td>
				<td>
					<a href="#" id="AccomplishesLink" class="TaskLink">Task #?</a>
					<a href="#" id="AccomplishesChange" class="TaskTool">Change</a>
					<a href="#" id="AccomplishesRemove" class="TaskTool">Make independent</a>
					<a href="#" id="AccomplishesAdd" class="TaskTool">Specify</a>
				</td>
			</tr>
			<tr>
				<td>Depends on:</td>
				<td>
					<a href="#" id="DependsLink" class="TaskLink">Task #?</a>
					<a href="#" id="DependsChange" class="TaskTool">Change</a>
					<a href="#" id="DependsRemove" class="TaskTool">Remove</a>
					<a href="#" id="DependsAdd" class="TaskTool">Specify</a>
				</td>
			</tr>
			<tr>
				<td>
					Priority:
					<span id="PriorityNote">
						(from <a href="#" id="PrioritySourceLink">task #4</a>)
					</span>
				</td>
				<td>
					<div id="PickPriority">
						<span class="Priority1" priority="1">&nbsp; 1 (lowest) &nbsp;</span>
						<span class="Priority2" priority="2">&nbsp; 2 &nbsp;</span>
						<span class="Priority3" priority="3">&nbsp; 3 &nbsp;</span>
						<span class="Priority4" priority="4">&nbsp; 4 &nbsp;</span>
						<span class="Priority5" priority="5">&nbsp; 5 &nbsp;</span>
						<span class="Priority6" priority="6">&nbsp; 6 &nbsp;</span>
						<span class="Priority7" priority="7">&nbsp; 7 &nbsp;</span>
						<span class="Priority8" priority="8">&nbsp; 8 &nbsp;</span>
						<span class="Priority9" priority="9">&nbsp; 9 &nbsp;</span>
						<span class="Priority10" priority="10">&nbsp; 10 (highest) &nbsp;</span>
					</div>
				</td>
			</tr>

			<tr>
				<td>Completed:</td>
				<td>
					<div id="Completed"></div>
				</td>
			</tr>
		</table>
	
		<div style="text-align: right;">
			<button id="Delete">Delete this task</button>
			<button id="Cancel">OK</button>
		</div>
	</div>
	
	<div class="Line">&nbsp;</div>
	<?= HTML::renderJobHeader() ?>
	<div id="JobTable">
		<?= $JobsHTML ?>
	</div>
	<div class="Line">&nbsp;</div>
</div>


<div id="Note">
</div>


</body>
<!-- DBR 2013-09-12 -->
<!-- included versions of jquery & jquery UI are now quite out of date -->
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js"></script>
<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/jquery-ui.min.js"></script>

<script type="text/javascript" src="src/main.js"></script>
<script type="text/javascript">

	// DBR 2013-09-12: I can't believe how old of an AJAX technique this site uses.
	// Good old SAJAX days, before we had $.get(). Wait a minute, didn't we have
	// it back then?
	
	<?php sajax_show_javascript(); ?>
	
	var EmployeeID = <?= $EmployeeID ?>;

</script>