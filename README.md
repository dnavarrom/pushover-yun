# Pushover for Yun 

This library provides an API interface to https://pushover.net using Arduino Yun Bridge.


## Usage

```c 
Pushover pushover = Pushover("MyUser", "MyKey");

pushover.setMessage("Test Message");
bool result = pushover.sendMessage();

```


## Options

#### Device

Your user's device name to send the message directly to that device, rather than all of the user's devices (multiple devices may be separated by a comma)

``` c
pushover.setDevice("iphone-1");
```

#### Title

The title of the message, if not supplied it will end up being the app name.


``` c
pushover.setTitle("Title");
```

#### Priority

-2 : to generate no notification/alert

-1 : to always send as a quiet notification

0 : [Default] normal priority

1 : to display as high-priority and bypass the user's quiet hours 

2 : to also require confirmation from the user

To send an emergency-priority notification, the priority parameter must be set to 2 and the retry and expire parameters must be supplied.


``` c
pushover.setPriority(1);
``` 


#### Supplementary URL

Supplementary URL to show with your message


``` c
pushover.setUrl("https://www.google.cl");
```

#### Supplementary URL Title

A title for your supplementary URL, otherwise just the URL is shown


``` c
pushover.setUrlTitle("Link to Google");
```

#### TimeStamp

a Unix timestamp of your message's date and time to display to the user, rather than the time your message is received by our API

``` c
pushover.setTimestamp(1532876117);
```

#### Pushover Call Timeout

Timeout to wait curl process to finish. Default 5000 = 5 sec

``` c
pushover.setTimeOut(10000);
```

#### Retry

The retry parameter specifies how often (in seconds) the Pushover servers will send the same notification to the user. In a situation where your user might be in a noisy environment or sleeping, retrying the notification (with sound and vibration) will help get his or her attention. This parameter must have a value of at least 30 seconds between retries.

``` c
pushover.setRetry(60); //1 minute
```

#### Expire

The expire parameter specifies how many seconds your notification will continue to be retried for (every retry seconds). If the notification has not been acknowledged in expire seconds,it will be marked as expired and will stop being sent to the user. This parameter must have a maximum value of at most 10800 seconds (3 hours).

``` c
pushover.setExpire(10800); // 3 hours
```

#### Override Message Sound

The name of one of the sounds supported by device clients to override the user's default sound choice

``` c
pushover.setSound("incoming");
```

#### Force Insecure https

To enable insecure https calls. Default true.

``` c
pushover.forceInsecureHttps(false);
``` 

#### Send in HTML Format

Send message in HTML format. Default false

``` c
pushover.isHtml(true);
``` 

### List of all options

``` c
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

```