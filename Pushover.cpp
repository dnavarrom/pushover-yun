/*********************************************************************
  Pushover.net library for Arduino Yun
  
  Send pushover.net messages from the arduino yun board / shield

  Written by Diego Navarro M.

  Tested on: Arduino Uno / Mega 2560 + Ethernet Shield

  MIT license, all text above must be included in any redistribution

**********************************************************************/

#include "Pushover.h"


Pushover::Pushover(String user, String token) {
  _token = token;
  _user = user;
  _apiUrl =  "https://api.pushover.net/1/messages.json";
  _forceInsecureHttps = true;
}

void Pushover::setMessage(String message) {
  _message = message;
}

// your user's device name to send the message directly to that device, rather than all of the user's devices 
//(multiple devices may be separated by a comma)
void Pushover::setDevice(String device) {
  _device = device;
}

//your message's title, otherwise your app's name is used
void Pushover::setTitle(String title) {
  _title = title;
}

//a supplementary URL to show with your message
void Pushover::setUrl(String url) {
  _url = url;
}

// a title for your supplementary URL, otherwise just the URL is shown
void Pushover::setUrlTitle(String urlTitle) {
  _urlTitle = urlTitle;
}

// send as -2 to generate no notification/alert, 
//-1 to always send as a quiet notification, 
//1 to display as high-priority and bypass the user's quiet hours, 
//or 2 to also require confirmation from the user
void Pushover::setPriority(int8_t priority) {
  _priority = priority;
}

// a Unix timestamp of your message's date and time to display to the user, 
//rather than the time your message is received by our API
void Pushover::setTimestamp(uint32_t timestamp) {
  _timestamp = timestamp;
}

//timeout to wait curl process to finish. Default 5000 = 5 sec
void Pushover::setTimeOut(uint16_t timeout) {
  _timeout = timeout;
}

//The retry parameter specifies how often (in seconds) the Pushover servers 
//will send the same notification to the user. In a situation where your user 
//might be in a noisy environment or sleeping, retrying the notification 
//(with sound and vibration) will help get his or her attention. 
//This parameter must have a value of at least 30 seconds between retries.
void Pushover::setRetry(uint16_t retry) {
  _retry = retry;
}

//The expire parameter specifies how many seconds your notification will continue 
//to be retried for (every retry seconds). If the notification has not been 
//acknowledged in expire seconds,it will be marked as expired and will stop being 
//sent to the user.
//This parameter must have a maximum value of at most 10800 seconds (3 hours).
void Pushover::setExpire(uint16_t expire) {
  _expire = expire;
}

//the name of one of the sounds supported by device clients 
//to override the user's default sound choice
void Pushover::setSound(String sound) {
  _sound = sound;
}

//To enable insecure https calls. Default true.
void Pushover::forceInsecureHttps(bool insecureHttps) {
  _forceInsecureHttps = insecureHttps;
}

//send message in HTML format. Default false
void Pushover::isHtml(bool isHtml) {
  _isHtml = isHtml;
}


bool Pushover::sendMessage(void) {
  buildCurlCommand();
  process.run();
  wait();
  return result();
}


void Pushover::buildCurlCommand() {
  
  process.begin("curl");

  //Default true
  if (_forceInsecureHttps == true) {
    process.addParameter("-k");
  }

  //credentials
  process.addParameter("--form-string");
  process.addParameter("token="+String(_token));
  process.addParameter("--form-string");
  process.addParameter("user="+String(_user));

  //data
  process.addParameter("--form-string");
  process.addParameter("message="+String(_message));

  //url
  process.addParameter(_apiUrl);

  //optionals

  if (_title != "") {
    process.addParameter("--form-string");
    process.addParameter("title=" + String(_title));
  }

  if (_url != "") {
    process.addParameter("--form-string");
    process.addParameter("url=" + String(_url));
  }

  if (_urlTitle != "") {
    process.addParameter("--form-string");
    process.addParameter("url_title=" + String(_urlTitle));
  }

  if (_sound != "") {
    process.addParameter("--form-string");
    process.addParameter("sound=" + String(_sound));
  }

  if (_priority != 0 && (_priority == 1 || _priority == 2 || _priority == -1 || _priority == -2)) {
    process.addParameter("--form-string");
    process.addParameter("priority=" + String(_priority));
  }

  if (_timestamp != 0) {
    process.addParameter("--form-string");
    process.addParameter("timestamp=" + String(_timestamp));
  }

  if (_isHtml == true) {
    process.addParameter("--form-string");
    process.addParameter("html=1");
  }


  if (_retry != 0) {

    if (_retry < 30) {
      _retry = 30;
    }

    process.addParameter("--form-string");
    process.addParameter("retry=" + String(_retry));
  }

  if (_expire != 0) {
       
    if (_expire > 10800) {
      _expire = 10800;
    }
    
    process.addParameter("--form-string");
    process.addParameter("expire=" + String(_expire));
    
  }
 
}

void Pushover::wait()
{ 
  int t = millis() + _timeout;
  while( !process.available() && t - millis() < 0) 
  {
    delay( 100 );
  }
}

bool Pushover::result() {

  String resultString;
  String line;
  
  while (process.available()>0) {
    char c = process.read();
    resultString += c;
  }

  return resultString.indexOf("\"status\":1") != -1;

}

