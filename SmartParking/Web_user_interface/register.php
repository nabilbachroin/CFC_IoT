<?php
	// Include config file
	require_once 'config/config.php';
?>

<!DOCTYPE html>
<html lang="en">
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

	<h1 align="center">Sign up</h1>
	
	<div class="center" style="margin: 0 auto; width:495px; border-style: solid; border-color: #f2f2f2;">
				<div class="row">
					<h3 align="center">Registration Form</h3>
				</div>
	
	<form action="signup_flow.php" method="post" id="signup" novalidate>
		<div class="control-group">
			<label for="username">Username</label>
			<div class="controls">
			<input type="text" id="username" name="username">
			</div>
		</div>
		
		<div class="control-group">
			<label for="email">email</label>
			<div class="controls">
			<input type="email" id="email" name="email">
			</div>
		</div>
		
		<div class="control-group">
			<label for="password">Password</label>
			<div class="controls">
			<input type="password" id="password" name="password">
			</div>
		</div>
		
		<div class="control-group">
			<label for="password_confirmation">Repeat Password</label>
			<div class="controls">
			<input type="password" id="password_confirmation" name="password_confirmation">
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
			<label class="control-label">Car</label>
				<div class="controls">
					<input name="car" type="text" placeholder="" required>
				</div>
		</div>
		
		<button>Sign up</button>
	</form>
	<p>Already have an account? <a href="login.php">Login here</a>.</p>
</body>
</html>
