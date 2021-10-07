
#include <SoftwareSerial.h> 
#include <SparkFunESP8266WiFi.h>
#include <ArduinoJson.h>

const int azul1 = 13;
const int verde1 = 12;
const int vermelho1 = 11;


const int azul2 = A5;
const int verde2 = A4;
const int vermelho2 = A3;

const int azul3 = 7;
const int verde3 = 6;
const int vermelho3 = 5;

const int azul4 = 4;
const int verde4 = 3;
const int vermelho4 = 2;

const char mySSID[] = "L&A Produções Artisticas2";
const char myPSK[] = "Le@0402Cultur@";

ESP8266Server server = ESP8266Server(80);

const char destServer[] = "example.com";
const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String httpRequest = "GET / HTTP/1.1\n"
                           "Host: example.com\n"
                           "Connection: close\n\n";

String colors[4][3];
String effect = "";
String token = "";

void setup() 
{
   pinMode(azul1, OUTPUT);
   pinMode(verde1, OUTPUT);
   pinMode(vermelho1, OUTPUT);
   pinMode(azul2, OUTPUT);
   pinMode(verde2, OUTPUT);
   pinMode(vermelho2, OUTPUT);
   pinMode(azul3, OUTPUT);
   pinMode(verde3, OUTPUT);
   pinMode(vermelho3, OUTPUT);
   pinMode(azul4, OUTPUT);
   pinMode(verde4, OUTPUT);
   pinMode(vermelho4, OUTPUT);
  // Serial Monitor is used to control the demo and view
  // debug information.
  Serial.begin(9600);
   pinMode(13, OUTPUT); 
//  serialTrigger(F("Press any key to begin."));

  // initializeESP8266() verifies communication with the WiFi
  // shield, and sets it up.
  initializeESP8266();

  // connectESP8266() connects to the defined WiFi network.
  connectESP8266();

  // displayConnectInfo prints the Shield's local IP
  // and the network it's connected to.
  //displayConnectInfo();
  
 // serialTrigger(F("Press any key to test server."));
  serverSetup();
}

void loop() 
{
  serverDemo();
  analogWrite(azul1,colors[0][0].toInt());
  analogWrite(verde1,colors[0][1].toInt());
  analogWrite(vermelho1, colors[0][2].toInt()); 
 analogWrite(azul2, colors[1][0].toInt());
  analogWrite(verde2,colors[1][1].toInt());
  analogWrite(vermelho2, colors[1][2].toInt());
  analogWrite(azul3, colors[2][0].toInt());
  analogWrite(verde3,colors[2][1].toInt());
  analogWrite(vermelho3, colors[2][2].toInt()); 
  analogWrite(azul4, colors[3][0].toInt());
  analogWrite(verde4,colors[3][1].toInt());
  analogWrite(vermelho4, colors[3][2].toInt());
}

void initializeESP8266()
{
  // esp8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  // true
  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266()
{
  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use esp8266.getMode() to check which mode it's in:
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  // esp8266.status() indicates the ESP8266's WiFi connect
  // status.
  // A return value of 1 indicates the device is already
  // connected. 0 indicates disconnected. (Negative values
  // equate to communication errors.)
  retVal = esp8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    // esp8266.connect([ssid], [psk]) connects the ESP8266
    // to a network.
    // On success the connect function returns a value >0
    // On fail, the function will either return:
    //  -1: TIMEOUT - The library has a set 30s timeout
    //  -3: FAIL - Couldn't connect to network.
    retVal = esp8266.connect(mySSID, myPSK);
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // esp8266.localIP returns an IPAddress variable with the
  // ESP8266's current local IP address.
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void serverSetup()
{
  // begin initializes a ESP8266Server object. It will
  // start a server on the port specified in the object's
  // constructor (in global area)
  server.begin();
  Serial.print(F("Server started! Go to "));
   analogWrite(azul1,0);
  analogWrite(verde1,255);
  analogWrite(vermelho1, 0); 
 analogWrite(azul2, 0);
  analogWrite(verde2,255);
  analogWrite(vermelho2, 0);
  analogWrite(azul3, 0);
  analogWrite(verde3,255);
  analogWrite(vermelho3, 0); 
  analogWrite(azul4, 0);
  analogWrite(verde4,255);
  analogWrite(vermelho4, 0);
  delay(2000);
  Serial.println(esp8266.localIP());
  Serial.println();
}

void serverDemo()
{ 
  // available() is an ESP8266Server function which will
  // return an ESP8266Client object for printing and reading.
  // available() has one parameter -- a timeout value. This
  // is the number of milliseconds the function waits,
  // checking for a connection.
  ESP8266Client client = server.available(500);
  String json = "";
  
 if (client) {
  // if you get a client,
   
    Serial.println("new client");           // print a message out the serial port
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {              // if there's bytes to read from the client,
        String request = client.readStringUntil("HTTP");
        Serial.println("leu aqui");
        Serial.println(request);
        
        
      /*int aux1 = request.indexOf('{');
      int aux2 = request.indexOf('}');
      json = request.substring(aux1,aux2+1);
      Serial.println("json");
      Serial.println(json);*/
      //delay(1000);
     // ---------Array de cores ---------
    //json.replace("{", "");
    //json.replace("}", "");
    
    String array = request.substring(request.indexOf("[[")+1,request.indexOf("]]") +1);
    int x = 0;
    int y = 0;
    Serial.println("array");
    Serial.println(array);

    for (int i = 0; i < 4 ; i++){
       for (int j = 0; j < 3; j++){
        colors[i][j]="";
      } 
    }
    
    for (int i = 0; i < array.length(); i++){
      
        if(array[i]!='[' && array[i]!=']' && array[i]!=','){
            colors[x][y] = colors[x][y] + array[i];
        }
        if(array[i] == ','){
            y=y+1;
        }
        if(i>0 & array[i]=='['){
            x=x+1;
            y=0;
        }
    }
    for (int i = 0; i < 4 ; i++){
    Serial.println("ARRAY:");
       for (int j = 0; j < 3; j++){
        Serial.println(colors[i][j]);
      } 
    }
  /**/
    //-------------Effect---------------
   /* 
    for(int i = json.indexOf("\"Effect\":\"")+10; i < json.length(); i++){
        if(json[i]!='"'){
            effect = effect + json[i];
        }else{
            break;
        }   
    }
    //-------------Token---------------
    for(int i = json.indexOf("\"Token\":\"")+9; i < json.length(); i++){
        if(json[i]!='"'){
            token = token + json[i];
        }else{
            break;
        }   
    }*/
      }
    
    }
    
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
  
}

// errorLoop prints an error code, then loops forever.
void errorLoop(int error)
{
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

// serialTrigger prints a message, then waits for something
// to come in from the serial port.
void serialTrigger(String message)
{
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}
