<?php

$host = 'localhost';
$dbname = 'team4';
$dbusername = 'root';
$dbpassword = '';

$mysqli = new mysqli(hostname: $host, username: $dbusername, password: $dbpassword, database: $dbname);

if ($mysqli->connect_errno) {
	die("Connection error: " . $mysqli->connect_error);
}

return $mysqli;
?>