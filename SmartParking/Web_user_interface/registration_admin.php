<?php
	require 'database.php';
	$id = null;
	if ( !empty($_GET['id'])) {
		$id = $_REQUEST['id'];
	}
	
	// Initialize session
	session_start();

	if (!isset($_SESSION['loggedin']) && $_SESSION['loggedin'] !== false) {
		header('location: login.php');
		exit;
	}
	
	$pdo = Database::connect();
	$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$sql = "SELECT * FROM table_rfid where id = ?";
	$q = $pdo->prepare($sql);
	$q->execute(array($id));
	$data = $q->fetch(PDO::FETCH_ASSOC);
	Database::disconnect();
?>

<!DOCTYPE html>
<html lang="en">
<html>
	<head>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta charset="utf-8">
		<link href="css/bootstrap.min.css" rel="stylesheet">
		<script src="js/bootstrap.min.js"></script>
		<script src="jquery.min.js"></script>
		<script>
			$(document).ready(function(){
				$("#postData").load("UIDContainer.php");
				setInterval(function()	{
					$("#postData").load("UIDContainer.php");
				}, 500);
			});
		</script>
		<style>
		body, html {
		  height: 100%;
		  margin: 0;
		}

		.bg {
		  /* The image used */
		  background-image: url("schema12.png");

		  /* Full height */
		  height: 100%; 

		  /* Center and scale the image nicely */
		  background-position: center;
		  background-repeat: no-repeat;
		  background-size: cover;
		}
		{
			font-family: Arial;
			display: inline-block;
			margin: 0px auto;
			
		}
		
		textarea {
			resize: none;
		}
		
		ul.topnav li {float: left;}
		
		ul.topnav {
			list-style-type: none;
			margin: auto;
			padding: 0;
			overflow: hidden;
			background-color: #333;
			width: 100%;
		}
		ul.topnav li {float: left;}
		
		ul.topnav li a {
			display: block;
			color: white;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
		}
		
		ul.topnav li a:hover:not(.active) {background-color: #ddd;}
		
		ul.topnav li a.active {background-color: #4CAF50}
		
		ul.topnav li.right {float: right;}
		
		div.group-form {
			margin-left: 20px;
		
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
			}
			
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
		}
		</style>
		
		<title>Home : Smart Parking</title>
	</head>
	<body class="bg">
		<div>
		<h2 align="center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home1.php">Home</a></li>
			<li><a href="user data1.php">User Data</a></li>
			<li><a class="active" href="registration_admin.php">Registration</a></li>
			<li><a href="parking1.php">Status Tracking</a></li>
			<li><a href="balance.php">Top Up Balance</a></li>
		</ul>
		
		<div class="container">
			<br>
			<div class="center" style="margin: 0 auto; width:495px; border-style: solid; border-color: #ffffff;">
				<div class="row">
					<h3 align="center">Registration Form</h3>
				</div>
				<br>
				<form class="form-horizontal" action="insertDB.php" method="post" >
					<div class="group-form">
					<div class="control-group">
						<label class="control-label">Username</label>
						<div class="controls">
							<input id="div_refresh" name="username" type="text" placeholder="" required>
						</div>
					</div>
					<div class="control-group">
						<label class="control-label">ID</label>
						<div class="controls">
							<textarea name="id" id="getUID" placeholder="Please Tag your Card" type="text" required></textarea>
						</div>
					</div>
						
					<div class="control-group">
						<label class="control-label">Name</label>
						<div class="controls">
							<input id="div_refresh" name="name" type="text" placeholder="" required>
						</div>
					</div>
						
					<div class="control-group">
						<label class="control-label">Gender</label>
						<div class="controls">
							<select name="gender">
								<option value="Male">Male</option>
								<option value="Female">Female</option>
							</select>
						</div>
					</div>
					
					<div class="control-group">
						<label class="control-label">Email</label>
						<div class="controls">
							<input name="email" type="text" placeholder="" required>
						</div>
					</div>
						
					<div class="control-group">
						<label class="control-label">Car</label>
						<div class="controls">
							<input name="car" type="text" placeholder="" required>
						</div>
					</div>
						
					<div class="form-actions">
						<button type="submit" class="btn btn-success">Save</button>
					</div>
					</div>
				</form>
	
			</div>
		</div> <!== /container ==>
		</div>
	</body>
</html>
