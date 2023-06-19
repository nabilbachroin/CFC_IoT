<?php
	
	if(empty(trim($_POST['username']))){
      $username_err = 'Please enter username.';
    } else{
      $username = trim($_POST['username']);
    }
	
	if(empty(trim($_POST['name']))){
      $username_err = 'Please enter name.';
    } else{
      $username = trim($_POST['name']);
    }
	
	if(empty(trim($_POST['balance']))){
      $username_err = 'Please enter balance.';
    } else{
      $username = trim($_POST['balance']);
    }
	
	$namee = $_POST['name'];
	$username = $_POST['username'];
	$balancetopup = (int)$_POST['balance'];
	
	include 'database.php';
	$pdo = Database::connect();
	$sql = "SELECT table_rfid.username, table_rfid.name, table_rfid.id, temporary_register.id, temporary_register.balance FROM table_rfid INNER JOIN temporary_register ON table_rfid.id=temporary_register.id WHERE username = '$username'";
	foreach ($pdo->query($sql) as $row){}
	$name = $row['name'];
	if($name == $namee){
      echo "Identity correct";
    } else{
      die("check your identity");
    }
	$balancesql = (int)$row['balance'];
	$balancesum = $balancesql + $balancetopup;

	Database::disconnect();
	echo $name;
	echo $namee;
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