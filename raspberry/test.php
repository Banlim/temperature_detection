<?php

 header("Content-Type:text/html;charset=utf-8");
 
 $host='localhost';
 $user='gonggam';
 $pw='1234';
 $dbName='phpmyadmin';
 $mysqli=new mysqli($host, $user,$pw, $dbName);

         if($mysqli){
                 echo "MYSQL successfully connected! <br/>";
		 
		 //$date=$_GET['date'];
		 $name=$_GET['name'];
		 $id=$_GET['id'];
                 $phone=$_GET['phone'];
		 //$building=$_GET['building'];
                 //$temperature=$_GET['temperature'];
                 //$flag=$_GET['flag'];

                #echo "<br/>date=$date<br/>";
                echo "<br/>name=$name<br/>";
                echo "<br/>id=$id<br/>";
                echo "<br/>phone=$phone<br/>";
                #echo "<br/>building=$building<br/>";
                #echo "<br/>temperature=$temperature<br/>";
                #echo "<br/>flag=$flag<br/>";

                #$query="INSERT INTO final_gonggam (date, name, id, phone, building, temperature, flag) VALUES ('$date', '$name', '$id', '$phone', '$building', '$temperature', '$flag')";
               # mysqli_query($mysqli, $query);
 
                $query="INSERT INTO test_1 ( name, id, phone) VALUES ('$name', '$id', '$phone')";
                if(mysqli_query($mysqli, $query))
                 	echo "</br>success!!";
         }
         
          else{
                  echo "MYSQL could not be connected";
          }
          
  mysqli_close($mysqli);
  ?>

