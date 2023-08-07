<?php
	require 'database.php';
	require 'CardDataContainer.php'; 
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
		<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
		<script src="js/bootstrap.min.js"></script>
		<script src="jquery.min.js"></script>
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
		
		body {
				background-image: url(bg.png);
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
		
		table, th, td {
			border: 1px solid black;
		}
		
		ul.topnav li a:hover:not(.active) {background-color: #ddd;}
		
		ul.topnav li a.active {background-color: #4CAF50}
		
		ul.topnav li.right {float: right;}
		
		.outline {
			outline: 5px solid white;
			margin: auto;
			margin-top: 20px;
			width: 99%;
			height: 270px;
		}
		
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
			}
			
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
		}
		
		.fa {
			padding: 10px;
			font-size: 15px;
			width: 50px;
			text-align: center;
			text-decoration: none;
			margin: 5px 1px;
		}

		.fa:hover {
			opacity: 0.7;
		}

		.fa-facebook {
			background: #3B5998;
			color: white;
		}

		.fa-twitter {
			background: #55ACEE;
			color: white;
		}

		.fa-google {
			background: #dd4b39;
			color: white;
		}

		.fa-linkedin {
			background: #007bb5;
			color: white;
		}

		.fa-youtube {
			background: #bb0000;
			color: white;
		}

		.fa-instagram {
			background: #125688;
			color: white;
		}

		.fa-pinterest {
			background: #cb2027;
			color: white;
		}
		</style>
		
		<title>Help : Smart Parking</title>
	</head>
	<body class="bg">
		<div>
		<h2 style="text-align:center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home.php">Home</a></li>
			<li><a href="user data.php">User Data</a></li>
			<li><a class="active" href="help.php">Help</a></li>
		</ul>
		<br>
		<div>
			<div style="position: absolute; top: 100px; left: 10px; width: 1000px;">
				<br>
				<h3>ANNOUNCEMENT</h3>
			</div>
			<br>
			<br>
			<div class="outline">
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			<br>
			<a style="font-size:25px;">&nbsp;&#9673; THERE IS NO ANNOUNCEMENT YET</a>
			</div>
			<div style="position: absolute; bottom: 0px; left: 10px; width: 1000px;">
				<h3>Contact Us</h3>
				<p>Tel	&nbsp;: +886954022477</p>
			</div>
			<div style="position: absolute; bottom: 0px; right: 0px; width: 400px;">
			<h3>Our Social Media</h3>
			<a href="#" class="fa fa-facebook"></a>
			<a href="#" class="fa fa-twitter"></a>
			<a href="#" class="fa fa-google"></a>
			<a href="#" class="fa fa-linkedin"></a>
			<a href="#" class="fa fa-youtube"></a>
			<a href="#" class="fa fa-instagram"></a>
			<a href="#" class="fa fa-pinterest"></a>
			</div>
		</div>
	</body>
</html>
