// TaskList.js
var oSelectedTimeZone = System.Time.currentTimeZone;
var refreshInterval;
System.Gadget.settingsUI = "Settings.html";
System.Gadget.onSettingsClosed = applySettings;


var employeeID;
var gadgetHeight;
var showScrollbar;
var updateInterval;

function applySettings() {
    employeeID = Number(System.Gadget.Settings.readString("EmployeeID"));
    gadgetHeight = Number(System.Gadget.Settings.readString("GadgetHeight"));
    showScrollbar = Number(System.Gadget.Settings.readString("ShowScrollbar"));
    updateInterval = Number(System.Gadget.Settings.readString("UpdateInterval"));
    
    // defaults
    if (employeeID == 0) employeeID = 1;
    if (gadgetHeight == 0) gadgetHeight = 240;
    if (updateInterval == 0) updateInterval = 30;

    updateList();
    
    if (refreshInterval) clearInterval(refreshInterval);
    refreshInterval = setInterval(updateList, updateInterval * 1000);

    $(document.body).css("height", gadgetHeight + "px");
    $("#tasklist").css("overflow", (showScrollbar)? "scroll":"hidden");
}

applySettings();



function updateList()
{
	var rand = Math.random();
	
	$.ajax({
		type: "GET",
		url: "http://tasks.d6r.org/api.php",
		data: "employee_id=" + employeeID + "&rand=" + rand,
		success: function(response) {
			var list = eval(response);
			processList(list);
		}
	});
	
    // Retrieve the local time.
    var sTimeInfo = System.Time.getLocalTime(oSelectedTimeZone);
    if (sTimeInfo != "")
    {
        var dDateInfo = new Date(Date.parse(sTimeInfo));  
        var dateStr = dDateInfo.toDateString();
        var dateStrSplit = dateStr.split(" ");
         
        $("#current_date").html(dateStrSplit[1] + " " + dateStrSplit[2]);
    }
    else
    {
        // Display default text.
    }
}


/*gfdfd
<div class="task">
    <span class="taskpri10">&nbsp;10&nbsp;</span>
    &nbsp; AI homework 4 for some longer description
    <div class="taskinfo">
        Due Wednesday
    </div>
</div>
*/

//<a href="javascript:complete(' + list[i].id + ')">Mark done</a> | 

function processList(list)
{
	var TaskListHTML = '';
	
	for (var i=0; i<list.length; i++)
	{
		var padding = list[i].indent_lvl * 16;
	
		TaskHTML = ''
		+'<div class="task" style="padding-left: ' + padding + 'px" onclick="check(' + list[i].id + ')">'
		+'    <span class="Priority' + list[i].priority + '">&nbsp;' + list[i].priority + '&nbsp;</span>'
		+'    &nbsp;' + list[i].title;
		
		var DueStr = list[i].due_str.replace(/&nbsp;/, " ");
		DueStr = jQuery.trim(DueStr);
		
		if (DueStr.length)
		{
			TaskHTML += ''
			+'    <div class="taskinfo">'
			+'        Due ' + DueStr
			+'    </div>';
		}
 
		TaskHTML +=''
		+'</div>';
		
		TaskListHTML += TaskHTML;
	}
	
	$("#tasklist").html(TaskListHTML);

	$(".task").click(function() {

	});
}


function check(taskID) {
    var rand = Math.random();
    
    $.ajax({
        type: "GET",
        url: "http://tasks.d6r.org/api.php",
        data: "employee_id=" + employeeID + "&rand=" + rand + "&action=complete&task=" + taskID,
        success: function(response) {
            var list = eval(response);
            processList(list);
        }
    });
}



setTimeout(function() {
    $("#note").fadeOut();
}, 3000);