#ifndef PAGE_DISPLAYSETTINGS_H_
#define PAGE_DISPLAYSETTINGS_H_

const char PAGE_DisplaySettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Display Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Solid colour</td><td><input id="solid-color" name="solid-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right"></td><td> </td></tr>
<tr><td align="right">Rainbow Effect:</td><td><input type="checkbox" id="effect" name="effect"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--grey" value="Save"></td></tr>
</table>
</form>
<script>
  
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/displayvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";

void send_display_settings_html()
{
	Serial.println("************************************");
	Serial.println(server.args());

	  if (server.args() > 0 )  // Save Settings
	  {
	    config.effect = 0;
	    for ( uint8_t i = 0; i < server.args(); i++ ) {
	      if (server.argName(i) == "solid-color") config.solidColor = server.arg(i);
	      if (server.argName(i) == "effect") config.effect =  1;
	    }
	    //Serial.println(config.effect);
	    //Serial.println(config.solidColor);
	    WriteConfig();
	  }
	  server.send_P ( 200, "text/html", PAGE_DisplaySettings );
	  Serial.println(__FUNCTION__);
}

void send_display_settings_values_html()
{

  String values ="";
  values += "solid-color|" + (String) config.solidColor + "|input\n";
  values += "effect|" +  (String) (config.effect ? "checked" : "") + "|chk\n";
  Serial.println(values);
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
}

#endif /* PAGE_DISPLAYSETTINGS_H_ */
