#include <Arduino.h>
#include <L298N.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const unsigned int IN1 = D0;
const unsigned int IN2 = D1;
const unsigned int IN3 = D2;
const unsigned int IN4 = D3;

const unsigned int EN1 = D4;
const unsigned int EN2 = D8;

L298N motor1(EN1, IN1, IN2);
L298N motor2(EN2, IN3, IN4);

String command;

const char* ssid = "Cars";
ESP8266WebServer server(80);

//Is means Send State for Http on IP_add is a text/html on web server So the Send Message to data and getdata for control Robot_cars
void HTTP_handleRoot(void) {

  if ( server.hasArg("State") ) {
    Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void setup() {
  Serial.begin(115200);

  motor1.setSpeed(255);
  motor2.setSpeed(255);

  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

 //Show myip is to IP_add the borad on SerialMonitor for Connecting Pass Appications !! 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();
}

void goAhead() {
  Serial.println("Go head");
  motor1.forward();
  motor2.forward();
}

void goBack() {
  Serial.println("Go back");
  motor1.backward();
  motor2.backward();
}

void goRight() {
  Serial.println("Turn right");
  motor2.forward();
}

void goLeft() {
  Serial.println("Turn left");
  motor1.forward();
}

void stopRobot() {
  Serial.println("Stop Robot");
  motor1.stop();
  motor2.stop();
}

void speedSTEP0() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}

void speedSTEP1() {
  motor1.setSpeed(25.5);
  motor2.setSpeed(25.5);
}

void speedSTEP2() {
  motor1.setSpeed(51);
  motor2.setSpeed(51);
}

void speedSTEP3() {
  motor1.setSpeed(102);
  motor2.setSpeed(102);
}

void speedSTEP4() {
  motor1.setSpeed(127.5);
  motor2.setSpeed(127.5);
}

void speedSTEP5() {
  motor1.setSpeed(153);
  motor2.setSpeed(153);
}

void speedSTEP6() {
  motor1.setSpeed(178.5);
  motor2.setSpeed(178.5);
}

void speedSTEP7() {
  motor1.setSpeed(204);
  motor2.setSpeed(204);
}

void speedSTEP8() {
  motor1.setSpeed(229.5);
  motor2.setSpeed(229.5);
}

void speedSTEP9() {
  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void loop() {
  server.handleClient();

//Command requst for http application requst control Robot cars.
  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "S") stopRobot();
  else if (command == "0") speedSTEP0();
  else if (command == "1") speedSTEP1();
  else if (command == "2") speedSTEP2();
  else if (command == "3") speedSTEP3();
  else if (command == "4") speedSTEP4();
  else if (command == "5") speedSTEP5();
  else if (command == "6") speedSTEP6();
  else if (command == "7") speedSTEP7();
  else if (command == "8") speedSTEP8();
  else if (command == "9") speedSTEP9();

}

// # Step 1 for Renew Coding !!
// # Recheck Code and you try control again!
//Not pass for coding is a Perfect for control don't smooth or control Robot_cars it's a mistake for the code and than you able to chang renew code now.