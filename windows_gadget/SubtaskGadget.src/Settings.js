
System.Gadget.onSettingsClosing = SettingsClosing;


var employeeID;
var gadgetHeight;
var showScrollbar;
var updateInterval;

$(document).ready(function() {

    loadSettings();

});


function loadSettings() {
    employeeID = Number(System.Gadget.Settings.readString("EmployeeID"));
    gadgetHeight = Number(System.Gadget.Settings.readString("GadgetHeight"));
    showScrollbar = Number(System.Gadget.Settings.readString("ShowScrollbar"));
    updateInterval = Number(System.Gadget.Settings.readString("UpdateInterval"));

    // defaults if no settings saved
    if (employeeID == 0) employeeID = 1;
    if (gadgetHeight == 0) gadgetHeight = 240;
    if (updateInterval == 0) updateInterval = 30;

    $("#SettingEmployeeID").val(employeeID);
    $("#SettingGadgetHeight").val(gadgetHeight);
    $("#SettingGadgetScrollbar").attr("checked", (showScrollbar) ? true: false);
    $("#SettingUpdateInterval").val(updateInterval);

    saveSettings();
}


function saveSettings() {

    employeeID = $("#SettingEmployeeID").val();
    gadgetHeight = $("#SettingGadgetHeight").val();
    showScrollbar = ($("#SettingGadgetScrollbar").attr("checked") == true)? 1:0;
    updateInterval = $("#SettingUpdateInterval").val();
    
    System.Gadget.Settings.writeString("EmployeeID", employeeID);
    System.Gadget.Settings.writeString("GadgetHeight", gadgetHeight);
    System.Gadget.Settings.writeString("ShowScrollbar", showScrollbar);
    System.Gadget.Settings.writeString("UpdateInterval", updateInterval);
    
}


function SettingsClosing(event)
{
    // Save the settings if the user clicked OK.
    if (event.closeAction == event.Action.commit)
    {
        saveSettings();
    }
    // Allow the Settings dialog to close.
    event.cancel = false;
}