<?php
	$Write="<?php $" . "UIDresult=''; " . "echo $" . "UIDresult;" . " ?>";
	file_put_contents('UIDContainer.php',$Write);
?>

<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Parking</title>
  <style>
    body {
      font-family: Arial, sans-serif;
    }

    .container {
      max-width: 960px;
      margin: 0 auto;
      padding: 1rem;
    }

    form {
      display: flex;
      flex-direction: column;
    }

    input,
    button {
      margin: 0.5rem 0;
    }
  </style>
</head>

<body>
  <div class="container">
    <h1>Smart Parking</h1>
    <h2>Register RFID Card</h2>
    <form id="register-form">
      <label for="rfid">RFID:</label>
      <input type="text" id="rfid" name="rfid" required>
      <button type="submit">Register</button>
    </form>
    <h2>Check Parking Status</h2>
    <button id="check-parking-status">Check Status</button>
    <div id="parking-status"></div>
  </div>
  <script src="https://sdk.amazonaws.com/js/aws-sdk-2.813.0.min.js"></script>
  <script>
    // AWS Configuration
    AWS.config.region = 'your_aws_region';
    AWS.config.credentials = new AWS.CognitoIdentityCredentials({
      IdentityPoolId: 'your_cognito_identity_pool_id',
    });

    // AWS IoT client
    const iotData = new AWS.IotData({
      endpoint: 'your_aws_iot_endpoint',
    });

    // Register RFID Card
    const registerForm = document.getElementById('register-form');
    registerForm.addEventListener('submit', (e) => {
      e.preventDefault();
      const rfid = e.target.elements.rfid.value;

      const params = {
        topic: 'registerRFID',
        payload: JSON.stringify({ rfid }),
        qos: 0,
      };

      iotData.publish(params, (err, data) => {
        if (err) {
          console.error('Error:', err);
        } else {
          console.log('RFID card registered:', rfid);
          alert('RFID card registered successfully');
        }
      });
    });

    // Check Parking Status
    const checkParkingStatusButton = document.getElementById('check-parking-status');
    const parkingStatusElement = document.getElementById('parking-status');
    checkParkingStatusButton.addEventListener('click', () => {
      const params = {
        topic: 'checkParkingStatus',
        payload: '{}',
        qos: 0,
      };

      iotData.publish(params, (err, data) => {
        if (err) {
          console.error('Error:', err);
        } else {
          console.log('Request to check parking status sent');
        }
      });

      iotData.getThingShadow({ thingName: 'your_thing_name' }, (err, data) => {
        if (err) {
          console.error('Error:', err);
        } else {
          const payload = JSON.parse(data.payload);
          const parkingStatus = payload.state.reported.parkingStatus;
          parkingStatusElement.textContent = `Parking status: ${parkingStatus}`;
        }
      });
    });
  </script>

</body>

</html>