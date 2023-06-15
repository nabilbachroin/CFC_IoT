<?php
include 'database.php';
	$pdo = Database::connect();
	$sql = "SELECT table_rfid.username, table_rfid.name, table_rfid.id, table_rfid.gender, table_rfid.email, table_rfid.car, temporary_register.id, temporary_register.status, temporary_register.balance FROM table_rfid INNER JOIN temporary_register ON table_rfid.id=temporary_register.id WHERE username = 'test1'";
	foreach ($pdo->query($sql) as $row){
		echo '<tr>';
								echo '<td>'. $row['name'] . '</td>';
								echo '<td>'. $row['id'] . '</td>';
								echo '<td>'. $row['gender'] . '</td>';
								echo '<td>'. $row['email'] . '</td>';
								echo '<td>'. $row['car'] . '</td>';
								echo '<td>'.$row['status'].'</td>';
								echo '<td>'.$row['balance'].'</td>';
								echo '</tr>';
	}

	Database::disconnect();
?>