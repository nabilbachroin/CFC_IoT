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
		
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
			}
			
		</style>
		
		<title>Balance : Smart Parking</title>
	</head>
	<body class="bg">
		<div>
		<h2 align="center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home1.php">Home</a></li>
			<li><a href="user data1.php">User Data</a></li>
			<li><a href="parking1.php">Status Tracking</a></li>
			<li><a class="active" href="balance.php">Top Up Balance</a></li>
			<li><a href="help1.php">Help</a></li>
		</ul>
		<br>
			<div class="center" style="margin: 0 auto; width:495px; border-style: solid; border-color: #ffffff;">
				<div class="row">
					<h3 align="center">BALANCE</h3>
				</div>
				<br>
				<form class="form-horizontal" action="balancesum.php" method="post">
					<div class="control-group">
						<label class="control-label">Username</label>
						<div class="controls">
							<input id="div_refresh" name="username" type="text" placeholder="" required>
						</div>
					</div>
					
					<div class="control-group">
						<label class="control-label">Name</label>
						<div class="controls">
							<input id="div_refresh" name="name" type="text" placeholder="" required>
						</div>
					</div>

					<div class="control-group">
						<label class="control-label">Balance</label>
						<div class="controls">
							<input id="div_refresh" name="balance" type="text" placeholder="" required>
						</div>
					</div>
						
					<div class="form-actions">
						<button type="submit" class="btn btn-success">Save</button>
					</div>
				</form>
	
			</div>
		</div>
	</body>
</html>
