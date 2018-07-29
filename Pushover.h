/*********************************************************************
  Pushover.net library for Arduino Yun
  
  Send pushover.net messages from the arduino yun board / shield

  Written by Diego Navarro M.

  Repository : https://github.com/dnavarrom/pushover-yun

  Tested on: Arduino Uno / Mega 2560 + Ethernet Shield

  MIT license, all text above must be included in any redistribution

**********************************************************************/

#include <Process.h>


class Pushover {

  private:

    String _token;
    String _user;
    String _message;
    String _apiUrl;
    String _device;
    String _title;
    String _url;
    String _urlTitle;
    int8_t _priority = 0;
    uint32_t _timestamp = 0;
    uint16_t _timeout = 5000;
    uint16_t _retry = 0;
    uint16_t _expire = 0;
    String _sound;
    bool _forceInsecureHttps = true;
    bool _isHtml = false;


    void buildCurlCommand();
    void wait();
    bool result();

  Process process;
    

  public:

    Pushover(String,String);

    void setDevice(String);
    void setMessage(String);
    void setTitle(String);
    void setUrl(String);
    void setUrlTitle(String);
    void setPriority(int8_t);
    void setTimestamp(uint32_t);
    void setTimeOut(uint16_t);
    void setRetry(uint16_t);
    void setExpire(uint16_t);
    void setSound(String);
    void forceInsecureHttps(bool);
    void isHtml(bool);
    bool sendMessage(void);
    
};
