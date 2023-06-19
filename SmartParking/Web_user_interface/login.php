<?php
	$Write="<?php $" . "UIDresult=''; " . "echo $" . "UIDresult;" . " ?>";
	file_put_contents('UIDContainer.php',$Write); 

 // Initialize sessions
  session_start();

  // Check if the user is already logged in, if yes then redirect him to home page
  if(isset($_SESSION["loggedin"]) && $_SESSION["loggedin"] === true){
    header("location: home.php");
    exit;
  }

  // Include config file
  require_once "config/config.php";

  // Define variables and initialize with empty values
  $username = $password = '';
  $username_err = $password_err = '';

  // Process submitted form data
  if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // Check if username is empty
    if(empty(trim($_POST['username']))){
      $username_err = 'Please enter username.';
    } else{
      $username = trim($_POST['username']);
    }

    // Check if password is empty
    if(empty(trim($_POST['password']))){
      $password_err = 'Please enter your password.';
    } else{
      $password = trim($_POST['password']);
    }

    // Validate credentials
    if (empty($username_err) && empty($password_err)) {
      // Prepare a select statement
      $sql = 'SELECT id_session, username, password, usertype FROM table_rfid WHERE username = ?';

      if ($stmt = $mysql_db->prepare($sql)) {

        // Set parmater
        $param_username = $username;

        // Bind param to statement
        $stmt->bind_param('s', $param_username);

        // Attempt to execute
        if ($stmt->execute()) {

          // Store result
          $stmt->store_result();

          // Check if username exists. Verify user exists then verify
          if ($stmt->num_rows == 1) {
            // Bind result into variables
            $stmt->bind_result($id_session, $username, $hashed_password, $usertype);

            if ($stmt->fetch()) {
              if (password_verify($password, $hashed_password)) {
				if ($usertype == "user") {
					// Start a new session
					session_start();

					// Store data in sessions
					$_SESSION['loggedin'] = true;
					$_SESSION['id_session'] = $id_session;
					$_SESSION['username'] = $username;

					// Redirect to user to page
					header('location: home.php');
				} else {
					// Start a new session
					session_start();

					// Store data in sessions
					$_SESSION['loggedin'] = true;
					$_SESSION['id_session'] = $id_session;
					$_SESSION['username'] = $username;

					// Redirect to user to page
					header('location: home1.php');
					}
              } else {
                // Display an error for passord mismatch
                $password_err = 'Invalid password';
              }
            }
          } else {
            $username_err = "Username does not exists.";
          }
        } else {
          echo "Oops! Something went wrong please try again";
        }
        // Close statement
        $stmt->close();
      }

      // Close connection
      $mysql_db->close();
    }
  }
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Sign in</title>
  <link href="css/bootstrap.min.css" rel="stylesheet">
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
    .wrapper{ 
		width: 500px; 
		padding: 20px; 
    }
    .wrapper h2 {text-align: center}
    .wrapper form .form-group span {color: red;}
	
  </style>
</head>
<body>
<div class="bg">
  <main>
    <section class="container wrapper">
      <h2 class="display-4 pt-3">Login</h2>
          <p class="text-center">Please fill this form to enter the website.</p>
          <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" method="POST">
            <div class="form-group <?php (!empty($username_err))?'has_error':'';?>">
              <label for="username">Username</label>
              <input type="text" name="username" id="username" class="form-control" value="<?php echo $username ?>">
              <span class="help-block"><?php echo $username_err;?></span>
            </div>

            <div class="form-group <?php (!empty($password_err))?'has_error':'';?>">
              <label for="password">Password</label>
              <input type="password" name="password" id="password" class="form-control" value="<?php echo $password ?>">
              <span class="help-block"><?php echo $password_err;?></span>
            </div>

            <div class="form-group">
			<br>
              <input type="submit" class="btn btn-block btn-outline-primary" value="login">
            </div>
            <p>Don't have an account? <a href="register.php">Sign up</a>.</p>
          </form>
    </section>
  </main>
</div>
</body>
</html>