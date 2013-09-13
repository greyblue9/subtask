<?php

$inifile = '../main.ini';
$inidata = parse_ini_file($inifile);

if (!isset($inidata['database_class_relative_path')) {
	print(
		'Sorry, Subtask cannot run. It needs a main.ini file specifying '.
		'the location of your database class file, which should be put safely '.
		'outside of your public web_root (unless this is a local installation)'
	);
	exit();
}

function get_ini_data($keyname) {
	if (isset($inidata[$keyname])) {
		return $inidata[$keyname];
	} else {
		print(
			'Subtask had to stop running. Your main.ini file appears to be '.
			'missing the entry "'.$keyname.'".'
		);
		exit();
	}
}

// Normal classes
require_once('HTML.class.inc');
require_once('JSON.class.inc');
require_once('Job.class.inc');

// Require the DB class (sensitive, should be outside webroot)
require_once(
	dirname(__FILE__). // start here in the include folder
	'/../'. // up one level to the webroot
	get_ini_data('database_class_relative_path') // path is assumed relative to webroot
);

