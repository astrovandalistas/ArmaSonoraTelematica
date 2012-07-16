<?php
//the arduino will store anything between '<' and '>'
//So if the output was <1kjhghk5> - the  arduino would read 1kjhghk5

//Just generates a random alphanumeric string
$what_the_arduino_reads = rand(0,2);

echo '<'.$what_the_arduino_reads.'>';
?>
