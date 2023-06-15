<?php
// Include database connection file
require 'database.php';

// Open connection
$pdo = Database::connect();

// Query to update 'no-name' in temporary_register from table_rfid
$sql_update = "UPDATE temporary_register 
               INNER JOIN table_rfid ON temporary_register.id = table_rfid.id 
               SET temporary_register.name = table_rfid.name 
               WHERE temporary_register.name = 'no-name'";
$sql_update1 = "UPDATE temporary_register 
               INNER JOIN table_rfid ON temporary_register.id = table_rfid.id 
               SET temporary_register.username = table_rfid.username";
$pdo->query($sql_update);
$pdo->query($sql_update1);

// Query to get latest data from table temporary_register
$sql_select = "SELECT * FROM temporary_register";
$result = $pdo->query($sql_select);

// Fetch all data
$data = $result->fetchAll(PDO::FETCH_ASSOC);

// Modifying keys in the array
foreach ($data as $key => $value) {
    $data[$key]['UID'] = $data[$key]['id'];
    unset($data[$key]['id']);
}

// Return as JSON
echo json_encode($data);
;

// Close connection
Database::disconnect();
?>
