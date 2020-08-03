#include "Wifi_Remote.h"

bool left_button_pressed;
bool right_button_pressed;
bool up_button_pressed;
bool down_button_pressed;

extern String wifi_name;
extern String wifi_password;
bool up_down_pressed = false;

WiFiServer myServer(80);
uint8_t oldCountClients = 0;
uint8_t countClients = 0;

void wifi_setup() {
	
	// Start WiFi and create a network with wifi_name as the network name
	// with wifi_password as the password.
	Serial.print("Starting AP... ");
	WiFi.beginNetwork((char *)wifi_name.c_str(), (char *)wifi_password.c_str());
	while (WiFi.localIP() == INADDR_NONE)
	{
		// print dots while we wait for the AP config to complete
		Serial.print('.');
		delay(300);
	}

	digitalWrite(RED_LED, HIGH);
	Serial.println("DONE");
	
	Serial.print("LAN name = ");
	Serial.println(wifi_name.c_str());
	Serial.print("WPA password = ");
	Serial.println(wifi_password.c_str());

	
	IPAddress ip = WiFi.localIP();
	Serial.print("Webserver IP address = ");
	Serial.println(ip);
	
	Serial.print("Web-server port = ");
	myServer.begin();                           // start the web server on port 80
	Serial.println("80");
	Serial.println();
}

void wifiLoop()
{

	// IPAddress ip = WiFi.localIP();
	// Serial.print("Webserver IP address = ");
	// Serial.println(ip);
	countClients = WiFi.getTotalDevices();
	
	// Did a client connect/disconnect since the last time we checked?
	if (countClients != oldCountClients)
	{
		if (countClients > oldCountClients)
		{  // Client connect
			//            digitalWrite(RED_LED, !digitalRead(RED_LED));
			Serial.println("Client connected to AP");
			for (uint8_t k = 0; k < countClients; k++)
			{
				Serial.print("Client #");
				Serial.print(k);
				Serial.print(" at IP address = ");
				Serial.print(WiFi.deviceIpAddress(k));
				Serial.print(", MAC = ");
				Serial.println(WiFi.deviceMacAddress(k));
				Serial.println("CC3200 in AP mode only accepts one client.");
			}
		}
		else
		{  // Client disconnect
			//            digitalWrite(RED_LED, !digitalRead(RED_LED));
			Serial.println("Client disconnected from AP.");
			Serial.println();
		}
		oldCountClients = countClients;
	}
	
	WiFiClient myClient = myServer.available();
	int val;// if you get a client,

	if (myClient)
	{          

		//Serial.println(". Client connected to server");           // print a message out the serial port
		char buffer[150] = {0};                 // make a buffer to hold incoming data
		int8_t i = 0;
		
		
		while (myClient.connected())
		{            // loop while the client's connected
		

			if (myClient.available())
			{             // if there's bytes to read from the client,
				char c = myClient.read();             // read a byte, then
				//Serial.write(c);                    // print it out the serial monitor
				if (c == '\n') {                    // if the byte is a newline character
					
					// if the current line is blank, you got two newline characters in a row.
					// that's the end of the client HTTP request, so send a response:
					
					
					if (strlen(buffer) == 0)
					{
						// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
						// and a content-type so the client knows what's coming, then a blank line:
						myClient.println("HTTP/1.1 200 OK");
						myClient.println("Content-type:text/html");
						myClient.println();
						myClient.print("<!DOCTYPE html><html><head>");
						myClient.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0\"> ");
						myClient.print(" <style>i{border: solid black; border-width: 0 3px 3px 0;");
						myClient.print("  display: inline-block; padding: 3px;}.right{transform: rotate(-45deg); -webkit-transform:");
						myClient.print("   rotate(-45deg); width: 100px; height:100px;}.left{transform: rotate(135deg);");
						myClient.print("    -webkit-transform: rotate(135deg); width: 100px; height:100px;}.up{transform: rotate(-135deg);");
						myClient.print("     -webkit-transform: rotate(-135deg); width: 100px; height:100px;}.down{transform: rotate(45deg);");
						myClient.print("      -webkit-transform: rotate(45deg); width: 100px; height:100px;}.noselect{-webkit-touch-callout:");
						myClient.print("       none; -webkit-user-select: none; -khtml-user-select: none; -moz-user-select: none;");
						myClient.print("        -ms-user-select: none; user-select: none;}</style></head><body><p id=\"demo\"></p><br><br><br><table style=\"padding-left:");
						myClient.print("         30px\" class=\"noselect\"><tr><td></td><td><p ontouchstart=\"as('up','/GOOD_S')\" ontouchend=\"as2('up','/GOOD_E')\" ontouchcancel=\"as2('up','/GOOD_E')\">");
						myClient.print("         <i class=\"up noselect\"></i></p></td><td></td><td></td></tr><tr><td><p ontouchstart=");
						myClient.print("         \"as('left','/LEFT_S')\" ontouchend=\"as2('left','/LEFT_E')\" ontouchcancel=\"as2('left','/LEFT_E')\"><i class=\"left noselect\"></i></p></td><td></td>");
						myClient.print("         <td></td><td><p ontouchstart=\"as('right','/RIGHT_S')\" ontouchend=\"as2('right','/RIGHT_E')\" ontouchcancel=\"as2('right','/RIGHT_E')\"><i class=\"right ");
						myClient.print("         noselect\"></i></p></td></tr><tr><td></td><td><p ontouchstart=\"as('down','/DOWN_S')\" ontouchend");
						myClient.print("         =\"as2('down','/DOWN_E')\" ontouchcancel=\"as2('down','/DOWN_E')\"><i class=\"down noselect\"></i></p></td><td></td><td></td></tr></table>");
						myClient.print("<script>function as(direction,two){document.getElementById(\"demo\").innerHTML=\"Touch Start \"");
						myClient.print("	+direction; sometime(\"Touch Start \"+direction,two);}function as2(direction,two)");
						myClient.print("		{document.getElementById(\"demo\").innerHTML=\"Touch End \"+direction; ");
						myClient.print("		sometime(\"Touch End \"+direction,two);}function sometime(thing,two)");
						myClient.print("		{fetch(two).catch(function(error){document.getElementById(\"demo\").innerHTML");
						myClient.print("			=\"Error \"+thing;});}</script></body></html>");
		   
						
						// The HTTP response ends with another blank line:
						myClient.println();
						// break out of the while loop:
						break;
					}
					else
					{      // if you got a newline, then clear the buffer:
						memset(buffer, 0, 150);
						i = 0;
					}
				}
				else if (c != '\r')
				{    // if you got anything else but a carriage return character,
					buffer[i++] = c;      // add it to the end of the currentLine
				}

				String text = buffer;
				//Serial.println(buffer);
				// Check to see if the client request was "GET /H" or "GET /L":
				if(text.indexOf("GET ")!= -1 && text.indexOf("HTTP/1.1") != -1) {

					
					if (text.startsWith("GET /LEFT_S "))
					{
						Serial.println("Left button pressed");
						left_button_pressed = true;
					}
					if (text.startsWith("GET /LEFT_E "))
					{
						left_button_pressed = false;
						Serial.println("Left button released");
					}
					
					
					if (text.startsWith("GET /RIGHT_S "))
					{
						right_button_pressed = true; 
						Serial.println("Right button pressed");
					}
					if (text.startsWith("GET /RIGHT_E "))
					{
						right_button_pressed = false; 
						Serial.println("Right button released");
					}              
					
					
					if (text.startsWith("GET /GOOD_S "))
					{
					   up_down_pressed = true;
					   up_button_pressed = true;
					   down_button_pressed = false;
					   Serial.println("Up button pressed");
	 
					}
					if (text.startsWith("GET /GOOD_E "))
					{
						up_down_pressed = false;  
						up_button_pressed = false;
						Serial.println("Up button released");
					}
					
					
					if (text.startsWith("GET /DOWN_S "))
					{
						up_down_pressed = true;   
						down_button_pressed = true;
						up_button_pressed = false;
						Serial.println("Down button pressed");
					}
					if (text.startsWith("GET /DOWN_E "))
					{
						up_down_pressed = false;    
						down_button_pressed = false;
						Serial.println("Down button released");
					}
				}
			}
		  
		}

		// close the connection:
		myClient.stop();
		Serial.println(". Client disconnected from server");
		//Serial.println();
	}
	custom_logic();
}