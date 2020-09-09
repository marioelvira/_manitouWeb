void _HttpSetup(void)
{
  // Http status
  httpStatus = HTTP_INIT;
}

void _HttpEnd(void)
{
  httpServer.stop();
}

///////////
// Pages //
///////////

void _serveCSS()
{
  httpServer.send (200, "text/css", cssSTYLE);
}

void _serveMAIN()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Status</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>MANITOU+ #Status<span>ESP8266 tech</span></h1>";

  html = html + "<h2>Temporizaciones:</h2><p id=\"TEMPSid\">...</p>";
  html = html + "<h2>Entradas Digitales:</h2><p id=\"INSid\">...</p>";
  html = html + "<h2>Salidas Digitales:</h2><p id=\"OUTSid\">...</p>";
  html = html + "<h2>Control:</h2><p>";
  html = html + "  <input type=\"button\" value=\"Cambiar Modo\" onclick=\"sendOUT(0)\">";
  html = html + "  <input type=\"button\" value=\"Reset Contadores\" onclick=\"sendOUT(1)\">";
  html = html + "</p><p>";
  html = html + "  <input type=\"button\" value=\"Rele\" onclick=\"sendOUT(10)\">";
  html = html + "  <input type=\"button\" value=\"Alarma\" onclick=\"sendOUT(11)\">";
  //html = html + "  <a href=\"settings.htm\"><input type=\"button\" value=\"Settings\"></a>";
  html = html + "  <a href=\"timeSettings.htm\"><input type=\"button\" value=\"Configuracion\"></a>";
  html = html + "</p>";
  html = html + "</div>";

  html = html + "<script>";
  
  html = html + "function sendOUT(out) {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  //html = html + "  xhttp.onreadystatechange = function() {";
  //html = html + "   if (this.readyState == 4 && this.status == 200) {";
  //html = html + "     document.getElementById(\"OUTNumber\").innerHTML = this.responseText;";
  //html = html + "   }";
  //html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"setOUTS?OUTNumber=\"+out, true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "setInterval(function() {";
  html = html + "  getOUTS();";
  html = html + "  getINS();";
  html = html + "  getTEMPS();";
  html = html + "}, 1000);";
  
  html = html + "function getOUTS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"OUTSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readOUTS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "function getINS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"INSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readINS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";

  html = html + "function getTEMPS() {";
  html = html + "  var xhttp = new XMLHttpRequest();";
  html = html + "  xhttp.onreadystatechange = function() {";
  html = html + "    if (this.readyState == 4 && this.status == 200) {";
  html = html + "      document.getElementById(\"TEMPSid\").innerHTML = this.responseText;";
  html = html + "   }";
  html = html + "  };";
  html = html + "  xhttp.open(\"GET\", \"readTEMPS\", true);";
  html = html + "  xhttp.send();";
  html = html + "}";
  
  html = html + "</script>";

  html = html + "</form>";
  html = html + "</div>";
  
  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _serveTimeSETTINGS()
{
  String html = "";
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>MANUTOU+ #Settings<span>ESP8266 tech</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='setTimeSettings'>";

  // Temporizaciones
  html = html + "<div class=\"section\"><span>1</span>Temporizaciones</div>";
  html = html + "<div class=\"inner-wrap\">";
  
  html = html + "<label>Tiempo In0 (secs): <input type=\"text\"  maxlength=\"16\" value=\"" + String(inTimeoutSec[0]) + "\" name=\"time0\"/></label>";
  html = html + "<label>Tiempo In1 (secs): <input type=\"text\"  maxlength=\"16\" value=\"" + String(inTimeoutSec[1]) + "\" name=\"time1\"/></label>";
  html = html + "<label>Tiempo In2 (secs): <input type=\"text\"  maxlength=\"16\" value=\"" + String(inTimeoutSec[2]) + "\" name=\"time2\"/></label>";
  html = html + "<label>Tiempo In3 (secs): <input type=\"text\"  maxlength=\"16\" value=\"" + String(inTimeoutSec[3]) + "\" name=\"time3\"/></label>";
  
  html = html + "</div>";
  // End
  
  html = html + "<div class=\"button-section\">";
  html = html + "  <input type=\"submit\" value=\"Save\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";
  
  html = html + "</div>";
  html = html + "</div>";
  html = html + "</form>";
  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

void _setTimeSETTINGS()
{
  String html = "";
  
  String rtime0 = httpServer.arg("time0");
  String rtime1 = httpServer.arg("time1");
  String rtime2 = httpServer.arg("time2");
  String rtime3 = httpServer.arg("time3");

  int error = 0;

  if ((rtime0.length() == 0) ||
      (rtime1.length() == 0) ||
      (rtime2.length() == 0) ||
      (rtime3.length() == 0))
  {
    error = 1;  // falta un campo...
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.println("Error... parametro vacío.");
    #endif
  }

  // Si no hay error...
  if (error == 0)
  {
    inTimeoutSec[0] = rtime0.toInt();
    inTimeoutSec[1] = rtime1.toInt();
    inTimeoutSec[2] = rtime2.toInt();
    inTimeoutSec[3] = rtime3.toInt();
    
    #if (_HTTP_SERIAL_DEBUG_ == 1)
    Serial.print("Timeout0 (sec): "); Serial.println(inTimeoutSec[0]);
    Serial.print("Timeout1 (sec): "); Serial.println(inTimeoutSec[1]);
    Serial.print("Timeout2 (sec): "); Serial.println(inTimeoutSec[2]);
    Serial.print("Timeout3 (sec): "); Serial.println(inTimeoutSec[3]);
    #endif

    EEPROM.write(EEPROM_ADD_TIMEOUT_IN0, (byte)inTimeoutSec[0]);
    EEPROM.write(EEPROM_ADD_TIMEOUT_IN1, (byte)inTimeoutSec[1]);
    EEPROM.write(EEPROM_ADD_TIMEOUT_IN2, (byte)inTimeoutSec[2]);
    EEPROM.write(EEPROM_ADD_TIMEOUT_IN3, (byte)inTimeoutSec[3]);
  }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>MANUTOU+ #Settings<span>ESP8266 tech</span></h1>";
  
  if (error == 0)
    html += "<p>Settings OK: Saved</p>";
  else
    html += "<p>Settings Error: Not Saved</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Volver\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}

/*
void _serveSETTINGS()
{
  //int mobile = 0;
  String html = "";

  int n = WiFi.scanNetworks();
  
  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Network Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  //html = html + "<meta name='apple-mobile-web-app-capable' content='yes' />";
  //html = html + "<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />";
  html = html + "</head>";

  html = html + "<body>";
  html = html + "<div class=\"myform\">";
  html = html + "<h1>MANUTOU+ #Network settings<span>ESP8266 tech</span></h1>";
  //html = html + "<form method=\"post\">";
  html = html + "<form method='get' action='networSettings'>";

  // Wi-Fi
  html = html + "<div class=\"section\"><span>1</span>Wi-Fi Settings</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (wifiMode == STATION_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\"> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\" checked> Station</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"ap\" checked> Access Point</label>";
    html = html + "<label><input type=\"radio\" name=\"wifimode\" value=\"st\"> Station</label>";
  }
  
  //html = html + "<label>SSID">
  //html = html + "<select id='wifi' name='wifi'>";
  //html = html + " <option value=\"\" selected>Selet</option>";
  //for (int i = 0; i < n; ++i)
  //  html = html + " <option value=\"" + (String)(WiFi.SSID(i)) + "\">" + (String)(WiFi.SSID(i)) + "</option>";    
  //html = html + "</select></label>";

  html = html + "<label>SSID <input type=\"text\" maxlength=\"30\" value=\"" + String(ssid) + "\" name=\"ssid\"/></label>";
  html = html + "<label>Password <input type=\"text\" maxlength=\"30\" value=\"" + String(password) + "\" name=\"pass\"/></label>";

  html = html + "</div>";
  // End

  // Red
  html = html + "<div class=\"section\"><span>2</span>IP Settings</div>";
  html = html + "<div class=\"inner-wrap\">";

  if (ipMode == DHCP_MODE)
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\" checked> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\"> Fix IP</label>";
  }
  else
  {
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"dhcp\"> DHCP</label>";
    html = html + "<label><input type=\"radio\" name=\"ipmode\" value=\"ipfx\" checked> Fix IP</label>";
  }

  html = html + "<label>IP Address <input type=\"text\"  maxlength=\"16\" value=\"" + String(ipAddress.toString()) + "\" name=\"ipaddress\"/></label>";
  html = html + "<label>Mask <input type=\"text\" maxlength=\"16\" value=\"" + String(netMask.toString()) + "\" name=\"mask\"/></label>";
  html = html + "<label>Gateway <input type=\"text\" maxlength=\"16\" value=\"" + String(gateWay.toString()) + "\" name=\"gateway\"/></label>";

  html = html + "</div>";
  // End
                        
  html = html + "<div class=\"button-section\">";
  html = html + "  <input type=\"submit\" value=\"Save\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";
  
  html = html + "</div>";
  html = html + "</div>";
  html = html + "</form>";
  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);  
}

void _setSETTINGS()
{
  String rwmode = httpServer.arg("wifimode");
  String rssid = httpServer.arg("ssid");
  String rpass = httpServer.arg("pass");
  
  String ripmode = httpServer.arg("ipmode");
  String ripaddress = httpServer.arg("ipaddress");
  String rmask = httpServer.arg("mask");
  String rgate = httpServer.arg("gateway");
    
  String html = "";
  int i, j, k, m;
  int error = 0;
  char schar;
  char sbuf[4];
  byte val[4];

  IPAddress localip;
  IPAddress localmask;
  IPAddress localgate;

  // Wi-Fi and IP configuration
  if (rwmode.length() > 0)
  {
    // Wi-Fi on Station mode
    if (rwmode == "st")
    {
      // must have a value
      if (rssid.length() == 0)
        error = 1;

      if (ripmode.length() == 0)
        error = 1;

      // must have a value
      if (ripmode == "ipfx")
      {
        // Must be 
        if ((ripaddress.length() == 0) ||
            (rmask.length() == 0)      ||
            (rgate.length() == 0))
          error = 1;
      }
      // DHCP mode
      //else {}
      
    }
    // Wi-Fi Access Point mode
    //else {}
    
  }
  else
    error = 1;

  // If no error on data...
  if (error == 0)
  {
     /////////////////////////
     // Wi-Fi configuration //
     /////////////////////////
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Wi-Fi 2 eeprom:");
     #endif
     
     // AP mode
     if (rwmode == "ap")
       EEPROM.write(EEPROM_ADD_WIFI_MODE, ACCESSPOINT_MODE);
     else
     {
       // Station mode
       EEPROM.write(EEPROM_ADD_WIFI_MODE, STATION_MODE);
  
       // ssid
       for (i = 0; i < WIFI_SSID_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, 0);
       j = rssid.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_SSID + i, rssid[i]);
       // password
       for (i = 0; i < WIFI_PSWD_MAX; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, 0);
       j = rpass.length();
       for (i = 0; i < j; i++)
         EEPROM.write(EEPROM_ADD_WIFI_PSWD + i, rpass[i]);
       
       /////////////
       // IP Mpde //
       /////////////
       #if (_HTTP_SERIAL_DEBUG_ == 1)
       Serial.println("IP 2 eeprom:");
       #endif
       // mode
       if (ripmode == "dhcp")
         EEPROM.write(EEPROM_ADD_IP_MODE, DHCP_MODE);
       else
       {
         EEPROM.write(EEPROM_ADD_IP_MODE, FIXIP_MODE);
  
         // IP
         j = ripaddress.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = ripaddress[i];
           if (schar == '.')
           {        
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localip = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_IP1, val[0]);
         EEPROM.write(EEPROM_ADD_IP2, val[1]);
         EEPROM.write(EEPROM_ADD_IP3, val[2]);
         EEPROM.write(EEPROM_ADD_IP4, val[3]);
         
         // Mask
         j = rmask.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rmask[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localmask = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_MASK1, val[0]);
         EEPROM.write(EEPROM_ADD_MASK2, val[1]);
         EEPROM.write(EEPROM_ADD_MASK3, val[2]);
         EEPROM.write(EEPROM_ADD_MASK4, val[3]);
    
         // Gateway
         j = rgate.length();
         k = 0;
         m = 0;
         for (i = 0; i < j; i++)
         {
           schar = rgate[i];
           if (schar == '.')
           {
             sbuf[k] = 0;  // end of buffer
             val[m] = (byte)(atoi(sbuf)); // change to int
             k = 0;
             m++;
           }
           else
           {
             sbuf[k] = schar;
             k++;
           }
         }
         // last IP value
         sbuf[k] = 0;  // end of buffer
         val[m] = (byte)(atoi(sbuf)); // change to int
         localgate = IPAddress(val[0], val[1], val[2], val[3]);
    
         EEPROM.write(EEPROM_ADD_GATE1, val[0]);
         EEPROM.write(EEPROM_ADD_GATE2, val[1]);
         EEPROM.write(EEPROM_ADD_GATE3, val[2]);
         EEPROM.write(EEPROM_ADD_GATE4, val[3]);
       }

     }
     
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     // Wi-Fi configuration
     Serial.print("---->Wi-Fi mode: ");
     Serial.println(rwmode);
     Serial.print("---->Wi-Fi SSID: ");
     Serial.println(rssid);
     Serial.print("---->Wi-Fi Password: ");
     Serial.println(rpass);
     Serial.println("");

     // IP configuration
     Serial.print("---->Local IP: ");
     Serial.println(localip);
     Serial.print("---->Local mask: ");
     Serial.println(localmask);
     Serial.print("---->Local gateway: ");
     Serial.println(localgate);
     #endif
     
     EEPROM.commit();

     #if (_READ_EEPROM_ == 1)
     _ReadEEPROM();
     delay(1000);
     #endif
    
     // Read config from EEPROM
     _readCONFIG();

     // OK
     i = 200;
   }
   else
   {
     #if (_HTTP_SERIAL_DEBUG_ == 1)
     Serial.println("Sending 404");
     #endif

     // Error
     i = 404;
   }

  html = "<!DOCTYPE HTML><html>";
  html = html + "<title>Network Settings</title>";
  html = html + "<head>";
  html = html + "<link rel=\"icon\" href=\"data:,\">";
  html = html + "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />";
  //html = html + "<meta name='apple-mobile-web-app-capable' content='yes' />";
  //html = html + "<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />";
  html = html + "</head>";

  html = html + "<body>";

  html = html + "<div class=\"myform\">";
  html = html + "<h1>MANUTOU+ #Network settings<span>ESP8266 tech</span></h1>";
  
  if (i == 200)
    html += "<p>Settings OK: Saved</p>";
  else
    html += "<p>Settings Error: Not Saved</p>";

  html = html + "<div class=\"button-section\">";
  html = html + "  <a href=\"index.htm\"><input type=\"button\" value=\"Back\"></a>";
  html = html + "</div>";

  html = html + "</div>";

  html = html + "</body> ";
  html = html + "</html>";

  httpServer.send (200, "text/html", html);
}
*/

/////////////
// Actions //
/////////////
void _readINS()
{ 
  String html = "";

  if (manitouControlMode == MODE_AUTO)
   html = "<div>Mode: Auto</div>";
  else
   html = "<div>Mode: Test</div>";

  if (inValue[INDEX_MOTOR] == IN_ON)
   html = html + "<div>Motor: ON</div>";
  else
   html = html + "<div>Motor: OFF</div>";

  if (inValue[INDEX_AGUA] == IN_ON)
   html = html + "<div>Alarma Agua: ON</div>";
  else
   html = html + "<div>Alarma Agua: OFF</div>";

  if (inValue[INDEX_ACEITE] == IN_ON)
   html = html + "<div>Alarma Aceite: ON</div>";
  else
   html = html + "<div>Alarma Aceite: OFF</div>";

  if (inValue[INDEX_AUX1] == IN_ON)
   html = html + "<div>Alarma Aux1: ON</div>";
  else
   html = html + "<div>Alarma Aux1: OFF</div>";

  if (inValue[INDEX_AUX2] == IN_ON)
   html = html + "<div>Alarma Aux2: ON</div>";
  else
   html = html + "<div>Alarma Aux2: OFF</div>";

  httpServer.send(200, "text/plane", html);
}

void _readOUTS()
{
  String html = "";
  
  if (outReleCorte == OUT_ON)
   html = "<div>Rele Corte: ON</div>";
  else
   html = "<div>Rele Corte: OFF</div>";

  if (outAlarma == OUT_ON)
   html = html + "<div>Aviso Alarma: ON</div>";
  else
   html = html + "<div>Aviso Alarma: OFF</div>";

  httpServer.send(200, "text/plane", html);
}
 
void _setOUTS()
{
  String out_number = httpServer.arg("OUTNumber");
  String html = "";
 
  #if (_HTTP_SERIAL_DEBUG_ == 1)
  Serial.print("Change stats out: ");
  Serial.println(out_number);
  #endif

  // Cambiar Modo
  if(out_number == "0")
  {
    if (manitouControlMode == MODE_TEST)
    {
      manitouControlMode = MODE_AUTO;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Modo Auto");
      #endif
      html = "Modo Auto";
    }
    else
    {
      manitouControlMode = MODE_TEST;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Modo Test");
      #endif
      html = "Mode Test";
    }
  }

  // Reset contadores
  if(out_number == "1")
  {
    // Manitou Data
    EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_LO, EEPROM_VAL_NUMBEROF_HOURS_LO);
    EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_HI, EEPROM_VAL_NUMBEROF_HOURS_HI);

    EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_LO,   EEPROM_VAL_NUMBEROF_ONS_LO);
    EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_HI,   EEPROM_VAL_NUMBEROF_ONS_HI);
    
    EEPROM.commit();    //Store data to EEPROM

    manitouNumberOfHours = 0;
    manitouNumberOfOns = 0;
  }

  // Relé corte
  if(out_number == "10")
  {
    if (outReleCorte == OUT_ON)
    {
      outReleCorte = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Rele OFF");
      #endif
      html = "Rele OFF";
    }
    else
    {
      outReleCorte = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Rele ON");
      #endif
      html = "Rele ON";
    }
  }
 
  // Alarma
  if(out_number == "11")
  {
    if (outAlarma == OUT_ON)
    {
      outAlarma = OUT_OFF;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Alarma OFF");
      #endif
      html = "Alarma OFF";
    }
    else
    {
      outAlarma = OUT_ON;
      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.println("Alarma ON");
      #endif
      html = "Alarma ON";
    }
 }
  
  httpServer.send(200, "text/plane", html);
}

void _readTEMPS()
{ 
  String html = "";

  html = "<div>Tiempo ON: " + String(timeHour) + " : " + String(timeMin) + " : " + String(timeSec) + "</div>";
  html = html + "<div>Horas ON: " + String(manitouNumberOfHours) + "</div>";
  html = html + "<div>Arranques: " + String(manitouNumberOfOns) + "</div>";

  httpServer.send(200, "text/plane", html);
}

////////////////////////
// Http state machine //
////////////////////////
void _HttpLoop()
{
  switch (httpStatus)
  {
    case HTTP_INIT:

      // css Style
      httpServer.on("/style.css",        _serveCSS);

      // html pages
      httpServer.on("/",                  _serveMAIN);
      httpServer.on("/index.htm",         _serveMAIN);
      //httpServer.on("/settings.htm",    _serveSETTINGS);
      httpServer.on("/timeSettings.htm",  _serveTimeSETTINGS);

      // acctions
      httpServer.on("/setOUTS",          _setOUTS);
      httpServer.on("/readOUTS",         _readOUTS);
      httpServer.on("/readINS",          _readINS);
      httpServer.on("/readTEMPS",        _readTEMPS);
      //httpServer.on("/networSettings", _setSETTINGS);
      httpServer.on("/setTimeSettings",  _setTimeSETTINGS);

      httpServer.begin();

      #if (_HTTP_SERIAL_DEBUG_ == 1)
      Serial.print("HTTP server started on ");
      Serial.print(HTTP_PORT);
      Serial.println(" port");      
      #endif
      httpStatus = HTTP_ONSERVE;
      break;
    
    case HTTP_ONSERVE:
      httpServer.handleClient();
      break;
  }
}
