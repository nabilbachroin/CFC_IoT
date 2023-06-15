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
		  background-image: url("schema.png");

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
		
		ul.topnav li.right {float; right;}
		
		@media screen and (max-width: 600px) {
			ul.topnav li.right,
			ul.topnav li {float: none;}
		}
		
		.table {
			margin: auto;
			width: 90%;
		}
		
		thead {
			color: #FFFFFF
		}
		</style>
		
		<title>User Data : Smart Parking</title>
	</head>
	
	<body>
		<h2>Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home.php">Home</a></li>
			<li><a class="active" href="user data.php">User Data</a></li>
			<li><a href="registration.php">Registration</a></li>
			<li><a href="parking.php">Parking Free</a></li>
		</ul>
		<br>
		<div class="container">
			<div class="row">
				<h3>User Data Table</h3>
			</div>
			<div class="row">
				<table class="table table-striped table-bordered">
					<thead>
						<tr bgcolor="$10a0c5" color="$FFFFFF">
							<th>Name</th>
							<th>ID</th>
							<th>Gender</th>
							<th>Email</th>
							<th>Car Type</th>
							<th>Action</th>
							<th>Status</th>
							<th>Balance</th>
						</tr>
					</thead>
					<tbody>
					<?php
					 include 'database.php';
					 $pdo = Database::connect();
					 $sql = "SELECT table_rfid.username, table_rfid.name, table_rfid.id, table_rfid.gender, table_rfid.email, table_rfid.car, temporary_register.id, temporary_register.status, temporary_register.balance FROM table_rfid INNER JOIN temporary_register ON table_rfid.id=temporary_register.id WHERE username = '{$_SESSION[ "username" ]}'";
					 foreach ($pdo->query($sql) as $row) {
								echo '<tr>';
								echo '<td>'. $row['name'] . '</td>';
								echo '<td>'. $row['id'] . '</td>';
								echo '<td>'. $row['gender'] . '</td>';
								echo '<td>'. $row['email'] . '</td>';
								echo '<td>'. $row['car'] . '</td>';
								echo '<td><a class="btn btn-success" href="user data edit page.php?id='.$row['id'].'">Edit</a>';
								echo ' ';
								echo '<a class="btn btn-danger" href="user data delete page.php?id='.$row['id'].'">Delete</a>';
								echo '</td>';
								echo '<td>'. $row['status'] .'</td>';
								echo '<td>'. $row['balance'] .'</td>';
								echo '</tr>';
					 }
					 Database::disconnect();
					?>
					</tbody>
				</table>
			</div>
		</div> <!== /container ==>
	</body>
</html>