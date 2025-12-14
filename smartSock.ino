#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define RELAY1 D1
#define RELAY2 D2
#define PUSH D3
bool r1state=LOW;
bool r2state=HIGH;

ESP8266WebServer server(80);
const char* authUser="s1pro";
const char* authPass="99@#699gr";

bool isAuthenticated(){
  if(!server.authenticate(authUser, authPass)){
    server.requestAuthentication();
    return false;
  }
  return true;
}
void handleRoot(){
  if(!isAuthenticated()) return;
  String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>My Socket Controls</title><style>";
  html += "body{display:flex;justify-content:center;align-items:center;height:100vh;background:linear-gradient(to right,#e4a5f4,#691069);} .cont1{justify-content:center;align-items:center;border:solid black 1px;padding:20px;background:linear-gradient(to left,#f8f9f6c3,#5c5d57);border-radius:7px;box-shadow:7px 5px 15px #bb6363;margin:20px;} .d1{display:flex;} button{text-align:center;font-size:20px;border-radius:7px;padding:8px;background-color:aqua;} button:hover{background-color:rgb(217,217,240);color:rgb(22,19,19);border-radius:10px;} button:active{transform:scale(1.1);background:linear-gradient(to right,#a992f3,#b3b0be);} </style></head><body>";
 
  html += "<div class='cont1'><div class='cont1 d1'>";
  
  // Relay 1 button
  html += "<h2>S1 :</h2>";
  if(r1state == LOW) {
    html += "<button id='btnS1' onclick=\"toggleSocket('s1')\">Turn Off</button>";
  } else {
    html += "<button id='btnS1' onclick=\"toggleSocket('s1')\">Turn On</button>";
  }

  // Relay 2 button
  html += "<h2>S2 :</h2>";
  if(r2state == LOW) {
    html += "<button id='btnS2' onclick=\"toggleSocket('s2')\">Turn Off</button>";
  } else {
    html += "<button id='btnS2' onclick=\"toggleSocket('s2')\">Turn On</button>";
  }

  html += "</div><div class='cont1'><p id='msg'></p></div></div>";

  
  html += "<script>function toggleSocket(socket){const btn=document.getElementById(`btn${socket.toUpperCase()}`);const isOn=btn.textContent.includes('On');const endpoint=isOn?`${socket}on`:`${socket}off`;fetch(`/${endpoint}`).then(r=>r.text()).then(data=>{document.getElementById('msg').textContent=data;btn.textContent=isOn?'Turn Off':'Turn On';}).catch(err=>{document.getElementById('msg').textContent='Error: '+err;});}</script>";

  html += "</body></html>";

  server.send(200,"text/html",html);
}

// void handleRoot(){
//   String html=R"rawliteral(
//     <!DOCTYPE html>
// <html lang="en">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>My Socket Controls</title>
//     <style>
//       * {
//   margin: 0;
//   padding: 0;
//   box-sizing: border-box;
// }
//       body{      
//           display: flex;
//           justify-content: center;
//           align-items: center;
//           height: 100vh;
//           background: linear-gradient(to right, #e4a5f4, #691069);
//       }
//         .cont1{
//           justify-content: center;
//           align-items: center;
//           border:solid black 1px;
//           padding: 20px;
//           background:linear-gradient(to left, #f8f9f6c3,#5c5d57);
//           border-radius: 7px;
//           box-shadow: 7px 5px 15px #bb6363;
//           margin: 20px;
//           }
//           .d1{
//             display: flex;
//           }
//         div:hover{
//           transform: scale(1.01);
//         }  
//         button {
//             text-align: center;
//             font-size: 20px;
//             border-radius: 7px;
//             padding: 8px;
//             background-color: aqua;
//             }
//         button:hover{
//           background-color: rgb(217, 217, 240);
//           color:rgb(22, 19, 19);
//           border-radius: 10px;
//         }    
//         button:active{
//           transform: scale(1.1);
//           background: linear-gradient(to right, #a992f3,#b3b0be);
//         }
//     </style>
// </head>
// <body>
//  <div class="cont1"> 
//       <div class="cont1 d1">
//         <h2><pre> S1 : </pre></h2>
//         <button id="btnS1" onclick="toggleSocket('s1')"><pre>Turn On</pre></button>
//         <h2><pre> S2 : </pre></h2>
//         <button id="btnS2" onclick="toggleSocket('s2')"><pre>Turn On</pre></button>
//       </div>
//       <div class="cont1">
//           <p id="msg"></p>
//       </div>
//   </div>
// </body>
//  <script>
  //   function toggleSocket(socket) {
  //     const btn = document.getElementById(`btn${socket.toUpperCase()}`);
  //     const isOn = btn.textContent.includes("On"); // check current state

  //     // Decide endpoint based on current state
  //     const endpoint = isOn ? `${socket}on` : `${socket}off`;

  //     fetch(`/${endpoint}`)
  //       .then(response => response.text())
  //       .then(data => {
  //         document.getElementById('msg').textContent = data;
  //         // Toggle button text
  //         btn.textContent = isOn ? "Turn Off" : "Turn On";
  //       })
  //       .catch(error => {
  //         document.getElementById('msg').textContent = "Error: " + error;
  //       });
  //   }
  // </script>

// </html>
//   )rawliteral";
//   server.send(200,"text/html",html);
// }

void R1_On(){
  if(!isAuthenticated()) return;
  if(r1state==LOW){
    server.send(200,"text/plain","Relay 1 is already ON");
    return;
  }else{
    digitalWrite(RELAY1,LOW);
  // rELAY1 = true;
    server.send(200,"text/plain","RELAY 1 Turned ON");
    r1state=LOW;
  }
}
void R1_Off(){
  if(!isAuthenticated()) return;
  if(r1state==HIGH){
    server.send(200,"text/plain","Relay 1 is already OFF");
    return;
  }else{
    digitalWrite(RELAY1,HIGH);
  // rELAY1 = false;
     server.send(200,"text/plain","RELAY 1 Turned OFF");
     r1state=HIGH;
  }
}
void R2_On(){
  if(!isAuthenticated()) return;
  if(r2state==LOW){
    server.send(200,"text/plain","Relay 2 is already ON");
    return;
  }else{
    digitalWrite(RELAY2,LOW);
  // rELAY2 = true; 
  server.send(200,"text/plain","RELAY 2 Turned ON");
    r2state=LOW;
  }  
}
void R2_Off(){
  if(!isAuthenticated()) return;
   if(r2state==HIGH){
    server.send(200,"text/plain","Relay 2 is already OFF");
    return;
  }else{
    digitalWrite(RELAY2,HIGH);
  // rELAY2 = true; 
    server.send(200,"text/plain","RELAY 2 is Turned OFF");
    r2state=HIGH;
  } 
}
void notFound(){
  if(!isAuthenticated()) return;
  server.send(404,"text/plain","Handle Not Found/Invalid Url");
}
WiFiManager wm;
void setup(){
  
  pinMode(PUSH,INPUT_PULLUP);
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  digitalWrite(RELAY1,LOW);
  digitalWrite(RELAY2,HIGH);
  Serial.begin(9600);
  bool status=wm.autoConnect("MyAP");
  if(status==HIGH){
    Serial.print("Connected to ");
    Serial.println(wm.getWiFiSSID());

  }else{
    Serial.println("Connect to WiFi using the MyAP showing on your WiFi");
  }

  if(WiFi.status()==WL_CONNECTED){
    if(MDNS.begin("smartSocket")){
      Serial.print("mDNS responder started: http://");
      Serial.print("smartSocket");
      Serial.println(".local");
    }else{
      Serial.println("Error in starting MDNS");
    }
  }


  server.on("/s1on",HTTP_GET,R1_On);
  server.on("/s1off",HTTP_GET,R1_Off);
  server.on("/s2on",HTTP_GET,R2_On);
  server.on("/s2off",HTTP_GET,R2_Off);
  server.on("/",HTTP_GET,handleRoot);
  server.onNotFound(notFound);

  server.begin();
}
void loop(){
  MDNS.update();
  server.handleClient();
  bool push = digitalRead(PUSH);
  if(push==LOW){
    wm.resetSettings();
    ESP.restart();
  }
}
