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
		  width: 100%;
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
			margin-top: auto;
			margin-bottom: 20px;
			margin-left: auto;
			margin-right: auto;
			width: 90%;
		}
		
		table, th, td {
			border: 1px solid black;
		}
		
		thead {
			color: #FFFFFF
		}
		td {
			vertical-align: 50px;
			text-align: center;
		}
		
		.button2 {background-color: #008CBA;} /* Blue */
		
		.text {
			position: right;
			width: 450px;
			margin-top: auto;
			margin-bottom: 20px;
			margin-left: 47px;
			margin-right: auto;
		
		.text input{
			width: 100%;
			text-align: center;
			padding: 5px;
			border: 1px solid rgba(255, 255, 255, 0.25);
			background: #1d2b3a;
			border-radius: 5px;
			outline: none;
			color: #fff;
			font-size: 0.8cm;
		}
		
		.text-label {
			width: 200%;
			color: ##1d2b3a;
			font-size: 1cm;
		}
		</style>
		
		<title>User Data : Smart Parking</title>
	</head>
	
	<body class="bg">
		<div>
		<h2 style="text-align:center">Smart Parking</h2>
		<ul class="topnav">
			<li><a href="home.php">Home</a></li>
			<li><a class="active" href="user data.php">User Data</a></li>
			<li><a href="help.php">Help</a></li>
		</ul>
		<br>
		<div class="container">
			<div class="row">
				<h3 style="text-align:center">USER DATA TABLE</h3>
			</div>
			<div class="row">
				<table class="table table-striped">
					<thead>
						<tr bgcolor="$10a0c5" color="$FFFFFF" align="center">
							<th>Name</th>
							<th>ID</th>
							<th>Gender</th>
							<th>Email</th>
							<th>Car Type</th>
							<th>Status</th>
							<th>Balance ($)</th>
							<th>Action</th>
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
								echo '<td>'. $row['status'] .'</td>';
								echo '<td>'. $row['balance'] .'</td>';
								echo '<td><a class="btn btn-danger" href="user data edit page.php?id='.$row['id'].'">Edit</a>';'</td>';
								echo '</tr>';
					 }
					 Database::disconnect();
					?>
					</tbody>
				</table>
				<br>
				<?php
					require 'SlotDataContainer.php'; 
				?>
				<br>
				<div class="text">
						<div class="text">
							<input name="parkingslots" type="text" placeholder="" value="Parking Slots : <?php echo$slotData["parkingSlots"];?>" readonly>
						</div>
				</div>
				<div class="text">
						<div class="text">
							<input name="eparking" type="text" placeholder="" value="Electric Charging Slots : <?php echo$slotData["electricChargingSlots"];?>" readonly>
						</div>
				</div>
			</div>
				<style>
				html{
				}
				.center{
					width: 75%;
					heigh: 50%;
					margin-top: 1px;
					margin-bottom: 1px;
					margin-left: 290px;
					margin-right: auto;
				}
				.center1{
					margin: auto;
					width: 50%;;
				}
				.colom{
					background-color: #808080;
					height:100px;
					width:100px;
					border:5px solid #000000;
					float:left;
					margin:10px;
				}
				.test{
					margin-top: 20px;
					margin-left: 17px;
					height:50px;
					width:75px;
					vertical-align: middle;
					font-size: 0.5cm;
				}
				</style>
				<div class="center">
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["parkingSlots"] > 4){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 1</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 1</span>';
					}
				?>
				</div>
				</div>
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["parkingSlots"] > 3){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 2</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 2</span>';
					}
				?>
				</div>
				</div>
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["parkingSlots"] > 2){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 3</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 3</span>';
					}
				?>
				</div>
				</div>
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["parkingSlots"] > 1){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 4</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 4</span>';
					}
				?>
				</div>
				</div>
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["parkingSlots"] > 0){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 5</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 5</span>';
					}
				?>
				</div>
				</div>
				<div class="colom">
				<div class="test">
				<?php	
					if ($slotData["electricChargingSlots"] > 0){
						echo '<span style="color:#AFA;text-align:center;">Parking NO 6</span>';
					}
					else{
						echo '<span style="color:#FFFFFF;text-align:center;">Parking NO 6</span>';
					}
				?>
				</div>
				</div>
				</div>
		</div> <!== /container ==>
		</div>
		<div style="position: absolute; bottom: 0; left: 0; width: 1000px;">
		<a style="text-align:center">Green : Available | White : Not Available | Parking NO 6 : Electric Charging<a>
		</div>
	</body>
</html>