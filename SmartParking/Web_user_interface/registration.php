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
				$("#getUID").load("UIDContainer.php");
				setInterval(function()	{
					$("#getUID").load("UIDContainer.php");
				}, 500);
			});
		</script>
		<style>
		html {
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
			
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
		}
		</style>
		
		<title>Home : Smart Parking</title>
	</head>
	<body>
	
		<h2 align="center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home.php">Home</a></li>
			<li><a href="user data.php">User Data</a></li>
			<li><a class="active" href="registration.php">Registration</a></li>
			<li><a href="parking.php">Parking free</a></li>
		</ul>
		
		<div class="container">
			<br>
			<div class="center" style="margin: 0 auto; width:495px; border-style: solid; border-color: #f2f2f2;">
				<div class="row">
					<h3 align="center">Registration Form</h3>
				</div>
				<br>
				<form class="form-horizontal" action="insertDB.php" method="post" >
					<div class="control-group">
						<label class="control-label">username</label>
						<div class="controls">
							<input name="username" type="text" placeholder="" value="<?php echo($_SESSION['username']);?>" readonly>
						</div>
					</div>
					<div class="control-group">
						<label class="control-label">ID</label>
						<div class="controls">
							<textarea name="id" id="getUID" placeholder="Please Tag your Card" rows="1" cols="1" required></textarea>
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
				</form>
	
			</div>
		</div> <!== /container ==>
	</body>
	<body>
		<h2 style="text-align:center">Smart Parking</h2>
		<ul class="nav navbar-nav navbar-right user-nav">
			<li class="username"><span><?php echo($_SESSION['username']); ?></span></li>
			<li class="dropdown avatar-dropdowm">
		</ul>
	</body>
</html>
