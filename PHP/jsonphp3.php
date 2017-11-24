<?php
    //initialize a new curl resource
    $url = "http://search.twitter.com/search.json?rpp=1000&q=BangCampoMarte";
    $contents = file_get_contents($url);
    $results = json_decode($contents, true);

    if($results === FALSE) {
        //Content couldn't be retrieved... Do something
    } else {	
        $tweet = $results["results"][0];
        $time = strtotime($tweet["created_at"]);

        $nows_date = date("Y-m-d g:i a"); 
        $now = strtotime($nows_date); 
        $tweetdate=date('n/j/y g:i a',$time);

    	if( $now - $time < 30 ) {
		    echo "[{1}{".$tweet["text"]."}{".$tweet["from_user_name"]."}]";
	    } else {
		    echo "[{0}{".$tweet["text"]."}{".$tweet["from_user_name"]."}]";
	    }
        $id = $entry->id;
        echo $text; echo "  "; echo $author;
	}
?>
