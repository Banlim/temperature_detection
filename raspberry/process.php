<?php
	$test_jsonlist=file_get_contents('/home/pi/gonggam/raspberry/test.json');
	$json=json_decode($test_jsonlist,true);
	
	$date = $json[date];
	$building = $json[building];
	$temperature=$json[temperature];

	($json[flag]==null) ? $flag=0:$flag=1;


 header("Content-Type:text/html;charset=UTF-8");
 
 $host='localhost';
 $user='gonggam';
 $pw='1234';
 $dbName='phpmyadmin';
 $mysqli=new mysqli($host, $user,$pw, $dbName);

         if($mysqli){
                 echo "MYSQL successfully connected! <br/>";
		 
		 $name=$_GET['name'];
		 $id=$_GET['id'];
                 $phone=$_GET['phone'];

                echo "<br/>date=$date<br/>";
                echo "<br/>name=$name<br/>";
                echo "<br/>id=$id<br/>";
                echo "<br/>phone=$phone<br/>";
                echo "<br/>building=$building<br/>";
                echo "<br/>temperature=$temperature<br/>";
                echo "<br/>flag=$flag<br/>";

                $query="INSERT INTO final_gonggam (date, name, id, phone, building, temperature, flag) VALUES ('$date', '$name', '$id', '$phone', '$building', '$temperature', '$flag')";
                if(mysqli_query($mysqli, $query))
                	echo "</br>success!!";
         }
         
          else{
                  echo "MYSQL could not be connected";
          }
          
  mysqli_close($mysqli);
?>

