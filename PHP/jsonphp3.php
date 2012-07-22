<?php
	//initialize a new curl resource

$url = "http://search.twitter.com/search.json?rpp=1000&q=BangCampoMarte";

// $url becomes "http://twitter.com/status/user_timeline/steph_Rose.json?count=5&callback=?";   
        $contents = file_get_contents($url);
        $results = json_decode($contents, true);


	if($results === FALSE) {
	    //Content couldn't be retrieved... Do something
	} else {
	    //Content was retrieved do something with it.
		//$tweets = json_decode($results);

/*		
        echo "<pre>";
        print_r($results);
        echo "</pre>";
*/

		//foreach($results["results"] as $tweet) {
//var_dump($results);
//			echo '<ul>';



	
	$tweet = $results["results"][0];

	
	$time = strtotime($tweet["created_at"]);

	$nows_date = date("Y-m-d g:i a"); 
	$now = strtotime($nows_date); 


	$tweetdate=date('n/j/y g:i a',$time);
//	echo date('n/j/y g:i a',$now); echo "...";	
	if( $now - $time < 30 ) {
		echo "[{1}{".$tweet["text"]."}{".$tweet["from_user_name"]."}]";
	}

	else {
		echo "[{0}{".$tweet["text"]."}{".$tweet["from_user_name"]."}]";
	}
        $id = $entry->id;
        echo $text; echo "  "; echo $author;
//			echo '</ul>';
		}
	
	//}





	


?>
