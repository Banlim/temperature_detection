<?php
	#$test_jsonlist=file_get_contents('/home/pi/gonggam/raspberry/test.json')
	@ini_set("allow_url_fopen","1");
	$test_jsonlist=file_get_contents('/home/pi/gonggam/raspberry/test.json');

	$array_data = json_decode($test_jsonlist,true);

	print_r($array_data);

	$date = $array_data[date];
	$building=$array_data[building];

	print_r($building);
	
	print_r($date);

	#if(json_decode('{"date":"2020-08-12 11:26", "building":3, "temperature":35.01, "flag":false}',true))
		#json_decode('{"date":"2020-08-12 11:26", "building":3, "temperature":35.01, "flag":false}',true)
		#var_dump(json_last_error());
		#var_dump(json_last_error_msg());


	#echo "<br/> $json <br/>"	

?>

