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
		html{
		}
		div.colom{
			height:150px;
			width:150px;
			border:5px solid #000000;
			float:left;
			margin:20px;
		}
		</style>
<head>
<title> Hey</title>
</head>
<body>
<div class="colom">Test</div>
<div class="colom">Test</div>
<div class="colom">Test</div>
<div class="colom">Test</div>
</html>
</html>