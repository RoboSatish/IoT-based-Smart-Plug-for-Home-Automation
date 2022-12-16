
#include <ESP8266WiFi.h>

#include "./DNSServer.h"  

#include <ESP8266WebServer.h>


const byte        DNS_PORT = 53;          

IPAddress         apIP(10, 10, 10, 1);  

DNSServer         dnsServer;            

ESP8266WebServer  webServer(80);        



int GPIO_2 = 2; 




String style_detials = 

   "<style type=\"text/css\">"

   " body{"

    "  background-color: #a69695;"

    "}"

    "button{"

     " display: inline-block;"

    "}"

    "#buttons{"

     " text-align: center;"

    "}"


    ".controllButtons{"

     " margin-top: 15px;"

      "margin-left: 5px;"

      "background-color: white;"

      "padding: 10px;"

      "border:1px solid black;"

      "border-radius: 10px;"

      "cursor: pointer;"

      "font-size: 14px;"

    "}"


    ".controllButtons:hover{"

     " background-color: orange;"

      "padding: 10px;"

      "border:1px solid black;"

      "border-radius: 10px;"

      "cursor: pointer;"

      "font-size: 14px;"

    "}"


    "@media only screen and (max-width: 700px) {"

     " button{"

      "  display: block;"

      "}"

      "#buttons{"

       " margin-top: 10%;"

        "margin-left: 35%;"

      "}"

       " .controllButtons{"

        "  margin-top: 15px;"

        "margin-left: 5px;"

        "background-color: white;"

        "padding: 15px;"

        "border:1px solid black;"

        "border-radius: 10px;"

        "cursor: pointer;"

        "font-size: 16px;"

      "}"


      ".controllButtons:hover{"

       " background-color: orange;"

        "padding: 15px;"

        "border:1px solid black;"

        "border-radius: 10px;"

        "cursor: pointer;"

        "font-size: 16px;"

      "}"

    "}"


  "</style>";


String Home_Screen = "" 

                      "<!DOCTYPE html><html>"

                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"

                      + style_detials +

                      "<div id=\"buttons\">"

                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"

                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"

                      "</div>"

                      "<body><h1>Welcome - CircuitDigest</h1>"

                      "</body></html>";


String ON_Screen = "" //Page 2 - If device is turned ON

                      "<!DOCTYPE html><html>"

                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"

                      + style_detials +

                      "<div id=\"buttons\">"

                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"

                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"

                      "</div>"

                      "<body><h1>Smart Plug - Turned ON</h1>"

                      "</body></html>";


String OFF_Screen = "" //Page 3 - If device is turned OFF

                      "<!DOCTYPE html><html>"

                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"

                      + style_detials +

                      "<div id=\"buttons\">"

                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"

                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"

                      "</div>"

                      "<body><h1>Smart Plug - Turned OFF</h1>"

                      "</body></html>";

                      

/*END OF HMTL CODE*/                    

                      



void setup() {

  pinMode(LED_BUILTIN, OUTPUT); 

  pinMode(GPIO_2, OUTPUT); 

    

  WiFi.mode(WIFI_AP); 

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP("ESP_Smart_Plug"); 


  dnsServer.start(DNS_PORT, "*", apIP);


  webServer.onNotFound([]() {

    webServer.sendHeader("Location", String("http://www.circuitdigest-automation.com/home.html"), true);

    webServer.send ( 302, "text/plain", "");

  });

  

  webServer.on("/home.html", []() {

    webServer.send(200, "text/html", Home_Screen);

  });


  webServer.on("/relay_ON", [](){ 

       digitalWrite(LED_BUILTIN, LOW); 

       digitalWrite(GPIO_2, HIGH);  

       webServer.send(200, "text/html", ON_Screen); 

  });





  webServer.on("/relay_OFF", [](){ 

       digitalWrite(LED_BUILTIN, HIGH); 

       digitalWrite(GPIO_2, LOW); 

       webServer.send(200, "text/html", OFF_Screen); 

  });


  

  

  webServer.begin();

}


void loop() {

  dnsServer.processNextRequest();

  webServer.handleClient();

}

