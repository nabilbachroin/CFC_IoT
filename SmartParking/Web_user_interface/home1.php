<?php
	$Write="<?php $" . "UIDresult=''; " . "echo $" . "UIDresult;" . " ?>";
	file_put_contents('UIDContainer.php',$Write);
	
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
		<meta charset="UTF-8">
		<title>Welcome</title>
		<link href="css/bootstrap.min.css" rel="stylesheet">
		<style>
			.wrapper{ 
				width: 500px; 
				padding: 20px; 
			}
			.wrapper h2 {text-align: center}
			.wrapper form .form-group span {color: red;}
			
			body {
				background-image=: url(bg.png);
			}
			
			.btn{
				top:center%;
				left:200%;
			}
		</style>
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta charset="utf-8">
		<link href="css/bootstrap.min.css" rel="stylesheet">
		<script src="js/bootstrap.min.js"></script>
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
			text-align: center;
		}
		
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
			
		img {
			display: block;
			margin-left: auto;
			margin-right: auto;
		}
		</style>
		<title>Home : Smart Parking</title>
	</head>
	
	<body class="bg">
		<div>
		<h2 style="text-align:center">Smart Parking</h2>
		<ul class="topnav">
			<li><a class="username"><span>Username : <?php echo($_SESSION['username']); ?></span></a></li>
			<li><a class="active" href="home1.php">Home</a></li>
			<li><a href="user data1.php">User Data</a></li>
			<li><a href="parking1.php">Status Tracking</a></li>
			<li><a href="balance.php">Top Up Balance</a></li>
			<li><a href="help1.php">Help</a></li>
		</ul>
		<br>
		<h3 style="text-align:center">Welcome to Team 4 Project "Smart Parking"</h3>
		<main>
			<section class="container wrapper">
				<div class="page-header">
					<h2 class="display-5">Welcome <?php echo $_SESSION['username']; ?></h2>
					<h2><a href="password_reset1.php" class="btn btn-block btn-outline-primary">Change Password</a>
						<a href="logout.php" class="btn btn-block btn-outline-danger">Sign Out</a></h2>
				</div>
			</section>
		</main>
		</div>
	</body>
</html>