#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
float speed = 0;
String permittedSpeed = "3";

String homepage = R"=====(
<!DOCTYPE html><html lang="en"><head> <meta charset="UTF-8"> <meta http-equiv="X-UA-Compatible" content="IE=edge"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <link rel="preconnect" href="https://fonts.googleapis.com"> <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin> <link href="https://fonts.googleapis.com/css2?family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,200;1,300;1,400;1,500;1,600;1,700&family=Roboto+Mono:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;1,100;1,200;1,300;1,400;1,500;1,600;1,700&display=swap" rel="stylesheet"> <title>Speed Tracking System</title></head><style>body{background-color: rgba(8, 0, 14, 0.956);}.container{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; margin: auto; width: 40%; padding: 20px; justify-content: center; align-items: center;}.title{color: rgb(250, 64, 98); font-weight: 700; font-size: 40px; justify-content: center; margin-left: auto;}.screen{z-index: 100; border-width: 5px; border-radius: 10px; padding: 20px; margin-top: 10px; margin-bottom: 10px; border-color: rgb(251, 136, 174); background-color: rgba(223, 204, 247, 0.163);}.speed-value{color: rgb(217, 177, 184);}.buttons{display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; margin-top: 10px;}label, .screen, .sub-title{font-weight: 500; color: rgb(253, 123, 166); font-size: 20px; margin-top: 20px; margin-bottom: 5px;}input{outline: none; border: none; border-radius: 10px; padding: 10px 15px; margin: 15px 0px; font-size: 17px; color: rgb(247, 165, 193); width: 95%; background-color: rgba(223, 204, 247, 0.163);}button{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; font-weight: 500; border-radius: 15px; padding: 7px 15px; background-color: rgb(162, 78, 124); border-color: rgb(255, 184, 236); color: rgb(249, 218, 237);}button:hover{background-color: rgb(27, 2, 15); color: rgb(255, 86, 151); cursor: pointer; transition-duration: 0.3s;}</style><body> <div class="container"> <h3 class="title">Speed Tracking Systems</h3> <div class="sub-title">Displaying screen</div><div class="screen"><!-- <div class="speed-value-title">Your speed: <span class="speed-value">30km/h</span></div><div class="status">Normal Speed</div>--> </div><div class="sub-title">Control mode</div><div class="buttons"> <form action="/AUTO_CONTROL" method="post"> <button class="auto-control">Auto Control</button> </form> <form action="/MANUAL_CONTROL" method="post"> <button class="manual-control">Manual Control</button> </form> </div><form action="/PEMITTED_CONTROL" method="post"> <div class="permitted-speed"> <label class="sub-title" for="permitted-speed">Permitted speed (km/h)</label> <input type="number" name="permitted-speed" id="permitted-speed"> </div><div class="buttons"> <button type="submit" onclick="myfunction()">Save change</button> </div></form> </div></body><script>var myfunction=function(){if(document.getElementById("permitted-speed").value==""){alert("Please enter a permitted speed, Keep old speed");}else{alert("Permitted speed has been changed to " + document.getElementById("permitted-speed").value + "km/h");}};</script></html>
)=====";

String no_detect = R"=====(
<!DOCTYPE html><html lang="en"><head> <meta charset="UTF-8"> <meta http-equiv="X-UA-Compatible" content="IE=edge"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <meta http-equiv="refresh" content="4; url=http://192.168.4.1/DETECT_VEHICLE" > <link rel="preconnect" href="https://fonts.googleapis.com"> <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin> <link href="https://fonts.googleapis.com/css2?family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,200;1,300;1,400;1,500;1,600;1,700&family=Roboto+Mono:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;1,100;1,200;1,300;1,400;1,500;1,600;1,700&display=swap" rel="stylesheet"> <title>Speed Tracking System</title></head><style>body{background-color: rgba(8, 0, 14, 0.956);}.container{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; margin: auto; width: 40%; padding: 20px; justify-content: center; align-items: center;}.title{color: rgb(250, 64, 98); font-weight: 700; font-size: 40px; justify-content: center; margin-left: auto;}.screen{z-index: 100; border-width: 5px; border-radius: 10px; padding: 20px; margin-top: 10px; margin-bottom: 10px; border-color: rgb(251, 136, 174); background-color: rgba(223, 204, 247, 0.163);}.speed-value{color: rgb(217, 177, 184);}.buttons{display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; margin-top: 10px;}label, .screen, .sub-title{font-weight: 500; color: rgb(253, 123, 166); font-size: 20px; margin-top: 20px; margin-bottom: 5px;}input{outline: none; border: none; border-radius: 10px; padding: 10px 15px; margin: 15px 0px; font-size: 17px; color: rgb(247, 165, 193); width: 95%; background-color: rgba(223, 204, 247, 0.163);}button{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; font-weight: 500; border-radius: 15px; padding: 7px 15px; background-color: rgb(162, 78, 124); border-color: rgb(255, 184, 236); color: rgb(249, 218, 237);}button:hover{background-color: rgb(27, 2, 15); color: rgb(255, 86, 151); cursor: pointer; transition-duration: 0.3s;}</style><body> <div class="container"> <h3 class="title">Speed Tracking Systems</h3> <div class="sub-title">Displaying screen</div><div class="screen"> <div class="status">No car detected</div></div><div class="sub-title">Control mode</div><div class="buttons"> <form action="/AUTO_CONTROL" method="post"> <button class="auto-control">Auto Control</button> </form> <form action="/MANUAL_CONTROL" method="post"> <button class="manual-control">Manual Control</button> </form> </div><form action="/PEMITTED_CONTROL" method="post"> <div class="permitted-speed"> <label class="sub-title" for="permitted-speed">Permitted speed (km/h)</label> <input type="number" name="permitted-speed" id="permitted-speed"> </div><div class="buttons"> <button type="submit" onclick="myfunction()">Save change</button> </div></form> </div></body><script>var myfunction=function(){if(document.getElementById("permitted-speed").value==""){alert("Please enter a permitted speed, Keep old speed");}else{alert("Permitted speed has been changed to " + document.getElementById("permitted-speed").value + "km/h");}};</script></html>
)=====";

void AUTO_CONTROL()
{
  Serial.println("Auto control mode on ");
  Serial1.print("auto");
  server.send(200, "text/html", no_detect);
}

void MANUAL_CONTROL()
{
  Serial.println("Manual control");
  Serial1.print("manual");
  server.send(200, "text/html", homepage);
}

void DETECT_VEHICLE()
{
  Serial.println("Detecting vehicle");
  String action = Serial.readString();
  Serial.println(action);
  String state = "";
  if (speed >= atof(permittedSpeed.c_str()))
  {
    state = "Over speed";
  }
  else
  {
    state = "Normal speed";
  }
  String detect = R"=====(
    <!DOCTYPE html><html lang="en"><head> <meta charset="UTF-8"> <meta http-equiv="X-UA-Compatible" content="IE=edge"> <meta name="viewport" content="width=device-width, initial-scale=1.0"> <link rel="preconnect" href="https://fonts.googleapis.com"> <meta http-equiv="refresh" content="3; url=http://192.168.4.1/AUTO_CONTROL" > <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin> <link href="https://fonts.googleapis.com/css2?family=Nunito:ital,wght@0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,200;1,300;1,400;1,500;1,600;1,700&family=Roboto+Mono:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;1,100;1,200;1,300;1,400;1,500;1,600;1,700&display=swap" rel="stylesheet"> <title>Speed Tracking System</title></head><style>body{background-color: rgba(8, 0, 14, 0.956);}.container{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; margin: auto; width: 40%; padding: 20px; justify-content: center; align-items: center;}.title{color: rgb(250, 64, 98); font-weight: 700; font-size: 40px; justify-content: center; margin-left: auto;}.screen{z-index: 100; border-width: 5px; border-radius: 10px; padding: 20px; margin-top: 10px; margin-bottom: 10px; border-color: rgb(251, 136, 174); background-color: rgba(223, 204, 247, 0.163);}.speed-value{color: rgb(217, 177, 184);}.buttons{display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; margin-top: 10px;}label, .screen, .sub-title{font-weight: 500; color: rgb(253, 123, 166); font-size: 20px; margin-top: 20px; margin-bottom: 5px;}input{outline: none; border: none; border-radius: 10px; padding: 10px 15px; margin: 15px 0px; font-size: 17px; color: rgb(247, 165, 193); width: 95%; background-color: rgba(223, 204, 247, 0.163);}button{font-family: 'Nunito', sans-serif; font-family: 'Roboto Mono', monospace; font-weight: 500; border-radius: 15px; padding: 7px 15px; background-color: rgb(162, 78, 124); border-color: rgb(255, 184, 236); color: rgb(249, 218, 237);}button:hover{background-color: rgb(27, 2, 15); color: rgb(255, 86, 151); cursor: pointer; transition-duration: 0.3s;}</style><body> <div class="container"> <h3 class="title">Speed Tracking Systems</h3> <div class="sub-title">Displaying screen</div><div class="screen"> <div class="speed-value-title">Your speed: <span class="speed-value">
      )=====";
  detect += speed;
  detect += "km/h</span></div>";
  detect += "<div class=\"status\">";
  detect += state;
  detect += "</div>";
  detect += R"=====(
    </div><div class="sub-title">Control mode</div><div class="buttons"> <form action="/AUTO_CONTROL" method="post"> <button class="auto-control">Auto Control</button> </form> <form action="/MANUAL_CONTROL" method="post"> <button class="manual-control">Manual Control</button> </form> </div><form action="/PEMITTED_CONTROL" method="post"> <div class="permitted-speed"> <label class="sub-title" for="permitted-speed">Permitted speed (km/h)</label> <input type="number" name="permitted-speed" id="permitted-speed"> </div><div class="buttons"> <button type="submit" onclick="myfunction()">Save change</button> </div></form> </div></body><script>var myfunction=function(){if(document.getElementById("permitted-speed").value==""){alert("Please enter a permitted speed, Keep old speed");}else{alert("Permitted speed has been changed to " + document.getElementById("permitted-speed").value + "km/h");}};</script></html>
      )=====";
  server.send(200, "text/html", detect);
}
void PEMITTED_CONTROL()
{
  if (server.arg("permitted-speed") != "")
  {
    permittedSpeed = server.arg("permitted-speed");
    Serial.println("Permitted control: " + permittedSpeed);
    Serial1.print(permittedSpeed);
  }
  server.send(200, "text/html", homepage);
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  String ssid = "ESP8266-AP";
  String password = "12345678";
  WiFi.softAP(ssid, password);
  server.on("/", []()
            { server.send(200, "text/html", homepage); });
  server.on("/AUTO_CONTROL", AUTO_CONTROL);
  server.on("/DETECT_VEHICLE", DETECT_VEHICLE);
  server.on("/MANUAL_CONTROL", MANUAL_CONTROL);
  server.on("/PEMITTED_CONTROL", PEMITTED_CONTROL);
  server.begin();
}

void loop()
{
  server.handleClient();
  if (Serial.available() > 0)
  {
    String action = Serial.readString();
    Serial.println("Speed Detect from sensor: " + action);
    if (action != "search")
    {
      speed = action.toFloat();
    }
  }
}