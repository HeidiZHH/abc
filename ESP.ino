#include <SoftwareSerial.h>//library for esp8266
#define RX 10
#define TX 11
String AP = "NETGEAR26";       // CHANGE ME
String PASS = "12345678"; // CHANGE ME
String PORT = "80";
SoftwareSerial esp8266(RX,TX); 


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 
   esp8266.begin(115200);
   //AT command
   sendCommand("AT",5,"OK");
   sendCommand("AT+CWMODE=1",5,"OK");
   sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");

}

void loop() {
  // put your main code here, to run repeatedly:
  String host="";//Change it
  String data="";//Change it
  sendto(host,data);
  delay(5000);
}

void sendto(String host, String data){
  Serial.print("sending data:");
  Serial.println(data);
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ host +"\","+ PORT,15,"OK");
  sent=sendCommand("AT+CIPSEND=0," +String(data.length()+4),4,">");
  esp8266.println(data);
}

int sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  found = false;
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;      
      break;
    }
    countTimeCommand++;
  }
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
    return 1;
  } 
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
    return 0;
  }  
 }

