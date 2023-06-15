<?php
require 'database.php';
$json = file_get_contents('php://input');

// convert json to array
$data = json_decode($json, true);

if (!isset($data['CardData']) || !isset($data['SlotData'])) {
    echo 'Data tidak valid';
    exit;
}

$cardData = $data["CardData"];

// write to file
$write = "<?php\n";
$write .= "\$cardData = " . var_export($cardData, true) . ";\n";
$write .= "?>";
file_put_contents('CardDataContainer.php', $write);

// get data slot
$slotData = $data["SlotData"];
  
// write to file
$write = "<?php\n";
$write .= "\$slotData = " . var_export($slotData, true) . ";\n";
$write .= "?>";
file_put_contents('SlotDataContainer.php', $write);
  
$pdo = Database::connect();
$pdo->exec("TRUNCATE TABLE temporary_register");
// Prepare SQL statement to insert into the database
$stmt = $pdo->prepare("INSERT INTO temporary_register (id, name, status, balance) VALUES (?, ?, ?, ?)");

// Loop through each card and insert into the database
foreach ($cardData as $card) {
    // Insert into the database
    $stmt->execute([$card["UID"], $card["name"], $card["status"], $card["balance"]]);
}

Database::disconnect();
?>
