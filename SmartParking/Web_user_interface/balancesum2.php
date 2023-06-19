<?php
	
	$name = $_POST['name'];
	$balancetopup = (int)$_POST['balance'];
	
	include 'database.php';
	$pdo = Database::connect();
	$sql = "SELECT balance FROM temporary_register WHERE name = '$name'";
	foreach ($pdo->query($sql) as $row){}
	
	$balancesql = (int)$row['balance'];
	$balancesum = $balancesql + $balancetopup;

	Database::disconnect();
	echo $balancesum;
	Database::disconnect();
	
	$pdo = Database::connect();
	$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$sql = "UPDATE temporary_register set balance = ? Where name = ?";
	$q = $pdo->prepare($sql);
	$q->execute(array($balancesum,$name));
	Database::disconnect();
	header('location: balance.php');
?>