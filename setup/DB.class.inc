<?php

// Put your database connection information in here. The function is
// called DB::connect().

class DB
{
	static $DB = null;
	
	protected $Connection;
	
	const LOCALHOST = '127.0.0.1';
	const D6R_ORG = 'd6r.org';
	
	function __construct()
	{
		$this->connect();
	}

	static function get()
	{
		if (self::$DB == null)
		{
			self::$DB = new DB();
		}
		
		return self::$DB;
	}
	
	protected function connect()
	{

		if( strpos($_SERVER['SERVER_NAME'], '127.0.0.1') !== false )
		{
			// Local development webserver (default with WAMP)
			
			$mysql_server = 'localhost';
			$mysql_username = 'root';
			$mysql_password = '';
			$mysql_db = 'prioritymanager';
		}
		else
		{
			// Online webserver settings
			// TODO: If you deploy this app online, fill in your MySQL
			// DB connection parameters here. But I think you keep
			// "localhost" as the server.
			
			$mysql_server = 'localhost';
			$mysql_username = '';
			$mysql_password = '';
			$mysql_db = '';
		}

		$this->Connection = mysql_connect($mysql_server, $mysql_username, $mysql_password, true);
		mysql_select_db($mysql_db, $this->Connection) or die(mysql_error());
	}

	static function query($pQuery, $pPrimaryID = null)
	{
		$DB = self::get();
		
		if (strpos(strtolower($pQuery), 'select') !== false)
		{
			return self::resultToArray(mysql_query($pQuery, $DB->Connection), $pPrimaryID);
		}
		else
		{
			return mysql_query($pQuery, $DB->Connection);
		}
	}
	
	protected static function resultToArray($pResult, $pPrimaryID = null)
	{
		if ($pResult == false) die(mysql_error(self::get()->Connection));
		$Array = array();

		while ($Row = mysql_fetch_assoc($pResult))
		{
			if ($pPrimaryID == null)
			{
				$Array[] = $Row;
			}
			else
			{
				$Array[intval($Row[$pPrimaryID])] = $Row;
			}
		}
		
		return $Array;
	}
	
	static function getInsertID()
	{
		$DB = self::get();
		
		return mysql_insert_id($DB->Connection);
	}
}

