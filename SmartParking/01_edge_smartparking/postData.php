<?php  $json = file_get_contents('php://input');  // convert json to array  $data = json_decode($json, true);  $cardData = $data["CardData"];  // write to file  $write = "<?php\n";  for ($i = 0; $i < count($cardData); $i++) {    $write .= "\$CardData" . $i . " = " . var_export($cardData[$i], true) . ";\n";    $write .= "echo \$CardData" . $i . ";\n";  }  $write .= "?>";  file_put_contents('CardDataContainer.php', $write);    // get data slot  $slotData = $data["SlotData"];    // write to file  $write = "<?php\n";  $write .= "\$SlotData = " . var_export($slotData, true) . ";\n";  $write .= "echo \$SlotData;\n";  $write .= "?>";  file_put_contents('SlotDataContainer.php', $write);?>