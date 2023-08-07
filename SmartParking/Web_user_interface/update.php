<?php
	require 'database.php';
	
	$id = null;
	if ( !empty($_GET['id'])) {
		$id = $_REQUEST['id'];
	}
	
	if ( !empty($_POST)) {
		// keep track post values
		$name = $_POST['name'];
		$id = $_POST['id'];
		$gender = $_POST['gender'];
		$email = $_POST['email'];
		$car = $_POST['car'];
		$username = $_POST['username'];
		
		$pdo = Database::connect();
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$sql = "UPDATE table_rfid set name = ?, gender = ?, email = ?, car = ?, id = ? Where id = ?";
		$q = $pdo->prepare($sql);
		$q->execute(array($name,$gender,$email,$car,$id,$username));
		Database::disconnect();
		header("Location: user data1.php");
	}
?>