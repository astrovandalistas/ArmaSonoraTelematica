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
String location = "http://astrovandalistas.cc/ast/twitter3/jsonphp3.php";

// if need to change the MAC address (Very Rare)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
////////////////////////////////////////////////////////////////////////

EthernetClient client;




boolean bang;

char tweet[144];
char autor[144];
char ultimoTweet[144];
char ultimoAutor[144];



char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

int relay1 = 6;
int relay2 = 7;

IPAddress ip(192,168,2,33);
IPAddress adns(192,168,2,2);
IPAddress gateway(192,168,2,254);
IPAddress subnetmask(255,255,255,0);


void setup(){

  Ethernet.begin(mac, ip, adns, gateway, subnetmask);
  Serial.begin(9600);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  
  memset( &ultimoTweet, 0, 144 ); //clear inString memory
  memset( &ultimoAutor, 0, 144 ); //clear inString memory

}

void loop(){

  if(connectAndCheck()) {
    //Serial.print("doit");
    rutinaRelays();
  }

  delay(5000); //wait 5 seconds before connecting again

}


void rutinaRelays(){
  digitalWrite(relay1,HIGH);
  delay(600);
  digitalWrite(relay1,LOW);
  delay(800);
  digitalWrite(relay2,HIGH);
  delay(600);
  digitalWrite(relay2,LOW);
  delay(800);

  digitalWrite(relay1,HIGH);
  delay(600);
  digitalWrite(relay1,LOW);
  delay(800);
  digitalWrite(relay2,HIGH);
  delay(600);
  digitalWrite(relay2,LOW);
  delay(800);
  
  digitalWrite(relay1,HIGH);
  delay(600);
  digitalWrite(relay1,LOW);
  delay(800);
  digitalWrite(relay2,HIGH);
  delay(600);
  digitalWrite(relay2,LOW);
  
  
  delay(2500);

  digitalWrite(relay2,HIGH);
  delay(600);
  digitalWrite(relay2,LOW);
  delay(800);
  
  digitalWrite(relay1,HIGH);
  delay(600);
  digitalWrite(relay1,LOW);
  delay(800);
  
}


boolean connectAndCheck(){
  //connect to the server

//  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) {
//    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();

    //Connected - Read the page
    //return readPage(); //go and read the output
    if(checkBang()){
      return true;
    }
    else {
      return false;
    }
  }else{
    return false;
  }

}





boolean checkBang(){
  bang = false;
  //read the page, and capture & return everything between '<' and '>'
  int leerParametro=0;
  stringPos = 0;
  memset( &tweet, 0, 144 ); //clear inString memory
  memset( &autor, 0, 144 ); //clear inString memory

  while(true){

    if (client.available()) {
      char c = client.read();
Serial.print(c);
      if (c == '[' ) { //'<' is our begining character
        startRead = true; //Ready to start reading the part 
      }
      else if(startRead){

        if(c != ']'){ //'>' is our ending character
          if (c == '{' ) { 
            //Serial.println("oK");
            stringPos=0;
          }
          else if (c == '}' ) {
            leerParametro++;
            leerParametro%=3;
          }
          else {
            
            if(leerParametro==0){
              if(c=='1'){

                bang = true;
              //  Serial.println("nuevo");
              } else { bang = false; } //Serial.println("viejo"); }
            }
            if(leerParametro==1){              
              tweet[stringPos] = c;

            }
            if(leerParametro==2){
              autor[stringPos] = c;
            }
            stringPos++;
          }          
          
        }else{
          startRead = false;
          client.stop();
          client.flush();
         // Serial.println("disconnecting.");

          
          // SETTEAR BANG!
         // Serial.println(autor);
          //Serial.println(tweet);
          //Serial.println(strcmp(autor,ultimoAutor));
          //Serial.println(autor);
          //Serial.println(ultimoAutor);
          
          if(!strcmp(autor,ultimoAutor)){
          
            if(strcmp(tweet,ultimoTweet)){
             // Serial.println("bang");
              memcpy(ultimoAutor,autor,144);
              memcpy(ultimoTweet,tweet,144);
              return true;
            }
            else {
              return false;
            }
          
          }
          
          if(!strcmp(tweet,ultimoTweet)){
          
            if(strcmp(autor,ultimoAutor)){
              //Serial.println("bang");
              memcpy(ultimoAutor,autor,144);
              memcpy(ultimoTweet,tweet,144);
              return true;
            }
            else {
              return false;
            }
          
          }
          
          if(strcmp(autor,ultimoAutor)&&strcmp(tweet,ultimoTweet)&&bang) {
            //Serial.println("bang");
            memcpy(ultimoAutor,autor,144);
            memcpy(ultimoTweet,tweet,144);
            return true;
          } else {
            //Serial.println("dont bang");
            return false;
          }
          
          

        }

      }
    }

  }

}
