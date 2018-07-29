#include "Pushover.h"
#include <Bridge.h>
#include <Console.h>

const String PUSHOVER_USERKEY = "abcde";
const String PUSHOVER_TOKEN ="abcde";
Pushover api = Pushover(PUSHOVER_USERKEY, PUSHOVER_TOKEN);

void setup() {
  
  Bridge.begin();  
  Console.begin();
  while (!Console);

  Console.println("Basic");
  testBasic();

  //Console.println("Sound");
  //testSound();

  //Console.println("URL");
  //testUrl();

  //Console.println("HTML");
  //testHtml();
  
  //Console.println("Priority 1");
  //testPriority1();

  //Console.println("Priority 2");
  //testPriority2();

  //Console.println("Priority -1");
  //testPriorityminus1();

  //Console.println("Priority -2");
  //testPriorityminus2();
  
}

void testBasic() {
  api.setMessage("Test From Library 2");
  api.setTitle("Titulo de prueba 2");
  Console.println(api.sendMessage());
}

void testSound() {
  api.setMessage("Test From Library with sound");  
  api.setSound("mechanical");
  Console.println(api.sendMessage());
}

void testUrl() {
  api.setUrl("https://www.google.cl");
  api.setUrlTitle("go to google");
  Console.println(api.sendMessage());
}

void testHtml() {
  api.setMessage("<b> bold message </b>, <i> Italic </i> , Display a tapeable <a href=\"https://www.google.cl\">link</a>");
  api.isHtml(true);
  Console.println(api.sendMessage());
}

void testPriority1() {
  api.setMessage("Test Priority 1");
  api.setPriority(1);
  Console.println(api.sendMessage());
}

void testPriorityminus1() {
  api.setMessage("Test Priority -1");
  api.setPriority(-1);
  Console.println(api.sendMessage());
}

void testPriorityminus2() {
  api.setMessage("Test Priority -2");
  api.setPriority(-2);
  Console.println(api.sendMessage());
}

void testPriority2() {
  api.setMessage("Test Priority 2");
  api.setRetry(60);
  api.setExpire(180);
  api.setPriority(2);
  Console.println(api.sendMessage());
}

void loop() {
  // put your main code here, to run repeatedly:

}
