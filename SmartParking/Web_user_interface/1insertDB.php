<?php

	require 'database.php';
	
	if ( !empty($_POST)) {
		// keep track post values
		$name = $_POST['name'];
		$id = $_POST['id'];
		$gender = $_POST['gender'];
		$email = $_POST['email'];
		$car = $_POST['car'];
		
		// insert data
		$pdo = Database::connect();
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$sql = "INSERT INTO table_rfid (name,id,gender,email,car) values(?, ?, ?, ?, ?)";
		$q = $pdo->prepare($sql);
		$q->execute(array($name,$id,$gender,$email,$car));
		Database::disconnect();
		header("Location: user data.php");
	}
?>