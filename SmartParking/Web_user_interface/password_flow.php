<?php
// Initialize session
	session_start();

if (!isset($_SESSION['loggedin']) && $_SESSION['loggedin'] !== false) {
		header('location: login.php');
		exit;
	}

if (strlen($_POST["password"]) < 8) {
	die("password must be at least 8 characters");
}

if ( ! preg_match("/[a-z]/i", $_POST["password"])) {
	die("password must contain at least 1 letter");
}

if ( ! preg_match("/[0-9]/i", $_POST["password"])) {
	die("password must contain at least 1 number");
}
	
if ($_POST["password"] !== $_POST["password_confirmation"]) {
	die("Password must match");
}

$password_hash = password_hash($_POST["password"], PASSWORD_DEFAULT);

$mysqli = require __DIR__ . "/database_signup.php";

$sql = "UPDATE table_rfid set password = ? where username = '{$_SESSION[ "username" ]}'";

$stmt = $mysqli->stmt_init();

if ( ! $stmt->prepare($sql)) {
	die("SQL error: " . $mysqli->error);
}

$stmt->bind_param("s", $password_hash);

if ($stmt->execute()) {
	
	header("Location: logout.php");
	exit;

} else{
	
	if ($mysqli0>errno === 1062) {
		die("username already taken");
	} else {
		die($mysqli->error . " " . $mysqli->errno);
	}
}