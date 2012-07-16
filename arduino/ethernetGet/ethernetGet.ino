
//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY
#include <Ethernet.h>
#include <SPI.h>

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte server[] = { 64,13,232,169 }; //ip Address of the server you will connect to

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is

String location = "http://astrovandalistas.cc/ast/arduino/test.php";
// if need to change the MAC address (Very Rare)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
////////////////////////////////////////////////////////////////////////

EthernetClient client;

char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

int pin = 8;

void setup(){

  Ethernet.begin(mac);
  Serial.begin(9600);

  pinMode(pin,OUTPUT);
  
}

void loop(){

  String pageValue = connectAndRead(); //connect to the server and read the output
  delay(2000);
  Serial.println(pageValue);
  delay(100);
  
  if(pageValue=="0") {
   digitalWrite(pin,HIGH);
   delay(100);
   digitalWrite(pin,LOW);
   Serial.println("relayoN");
  }
  else {
   digitalWrite(pin,LOW);
    Serial.println("relayoFF");  
  }
/*
  digitalWrite(pin, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(pin, LOW);    // set the LED off
  delay(1000);              // wait for a second
*/
}

String connectAndRead(){
  //connect to the server

  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();

    //Connected - Read the page
    return readPage(); //go and read the output

  }else{
    return "connection failed";
  }

}

String readPage(){
  //read the page, and capture & return everything between '<' and '>'

  stringPos = 0;
  memset( &inString, 0, 32 ); //clear inString memory

  while(true){

    if (client.available()) {
      char c = client.read();

      if (c == '<' ) { //'<' is our begining character
        startRead = true; //Ready to start reading the part 
      }else if(startRead){

        if(c != '>'){ //'>' is our ending character
          inString[stringPos] = c;
          stringPos ++;
        }else{
          //got what we need here! We can disconnect now
          startRead = false;
          client.stop();
          client.flush();
          Serial.println("disconnecting.");
          return inString;

        }

      }
    }

  }

}
