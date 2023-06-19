<?php

if (empty($_POST["username"])) {
	die("username is required");
}

if ( ! filter_var($_POST["email"], FILTER_VALIDATE_EMAIL)) {
	die("input valid email");
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

if (empty($_POST["id"])) {
	die("id is required");
}
	
if (empty($_POST["name"])) {
	die("name is required");
}
	
if (empty($_POST["gender"])) {
	die("gender is required");
}

if (empty($_POST["car"])) {
	die("car is required");
}

$password_hash = password_hash($_POST["password"], PASSWORD_DEFAULT);

$mysqli = require __DIR__ . "/database_signup.php";

$sql = "INSERT INTO table_rfid (username, email, password, id, name, gender, car) VALUES (?, ?, ?, ?, ?, ?, ?)";

$stmt = $mysqli->stmt_init();

if ( ! $stmt->prepare($sql)) {
	die("SQL error: " . $mysqli->error);
}

$stmt->bind_param("sssssss", $_POST["username"], 
						 $_POST["email"], 
						 $password_hash, $_POST["id"], $_POST["name"], $_POST["gender"], $_POST["car"]);

if ($stmt->execute()) {
	
	header("Location: login.php");
	exit;

} else{
	
	if ($mysqli>errno) {
		die("please fill in your personal data correctly");
	} else {
		die($mysqli->error . " " . $mysqli->errno);
	}
}