#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int IN1 = D1;
int IN2 = D2;
int IN3 = D3;
int IN4 = D4;
char command = 'S';
 
ESP8266WebServer server(80);

void setup(){
  Serial.begin(115200);
  Serial.println();
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  Stop(); 

  String ssid = "device_name";
  String pass = "password";
// Change your id and password accordingly

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("");

  Serial.println("*WiFi-AP-Mode*");
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  delay(3000);
  server.begin();  
}

void loop() {
      server.handleClient();
      String command = server.arg("State");
      Serial.println(command);
      if      (command == "F") Forward();
      else if (command == "B") Backward();
      else if (command == "R") TurnRight();
      else if (command == "L") TurnLeft();
      else Stop();
      delay(10);
} 

void Forward(){
  digitalWrite(IN1, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN4, 0);
}

void Backward(){
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN4, 1);
}
 
void Stop(){
  digitalWrite(IN2, 0);
  digitalWrite(IN4, 0);
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);
}

void TurnRight(){
  digitalWrite(IN1, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN4, 1);
}

  void TurnLeft(){
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN2, 1);
  digitalWrite(IN4, 0);
  }