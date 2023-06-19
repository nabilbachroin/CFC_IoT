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
		
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
			}
			
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
		}
		</style>
		
		<title>Status Tracking : Smart Parking</title>
	</head>
	<body class="bg">
		<div>
		<h2 style="text-align:center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home1.php">Home</a></li>
			<li><a href="user data1.php">User Data</a></li>
			<li><a class="active" href="parking1.php">Status Tracking</a></li>
			<li><a href="balance.php">Top Up Balance</a></li>
			<li><a href="help1.php">Help</a></li>
		</ul>
		<br>
		<div class="container">
			<div class="row">
				<h3>Status Tracking</h3>
			</div>
			<div class="row">
				<table class="table table-striped">
					<thead>
						<tr bgcolor="$10a0c5" color="$FFFFFF">
							<th>ID</th>
							<th>Name</th>
							<th>Status</th>
							<th>Balance</th>
						</tr>
					</thead>
					<tbody>
					<?php
					  // Include the database connection file

					  if (isset($cardData) && (is_array($cardData) || is_object($cardData)))
					  {
						foreach ($cardData as $card) {
						   echo "<tr>";
						   echo "<td>" . $card["UID"] . "</td>";
						   echo "<td>" . $card["name"] . "</td>";
						   echo "<td>" . $card["status"] . "</td>";
						   echo "<td>" . $card["balance"] . "</td>";
						   echo "</tr>";
						   
						} 
					  }
					?>

					</tbody>
				</table>
				<br>
			</div>
		</div> <!== /container ==>
		</div>
	</body>
</html>
