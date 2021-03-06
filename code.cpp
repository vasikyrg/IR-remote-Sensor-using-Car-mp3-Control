#include <LiquidCrystal.h>
#include <math.h>
#include <IRremote.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Digital Pin Connection to your IR Receiver
IRrecv irrecv(10);
decode_results results;
unsigned long key_value = 0;
String
number1 = "0",
number2 = "0",
optr = "=",
sixteenString = " ";
void setup() {
Serial.begin(9600);
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
irrecv.enableIRIn();// Start the receiver
}
void loop() {
if (irrecv.decode(&results)) {
unsigned int result = results.value;
String val = String(result);
translateIR(val.toInt());
irrecv.resume(); // Receive the next value
}
lcd.setCursor(0,0);
lcd.print(optr + " " + sixteenString.substring(number1.length() + 3) + number1);
lcd.setCursor(0,1);
lcd.print(sixteenString.substring(number2.length()) + number2);
}
void calculate(String op) {
double no1 = number1.toDouble();
double no2 = number2.toDouble();
double calcVal = 0.0;
if(optr == "+")
calcVal = (no1 + no2);
else if(optr == "-")
calcVal = (no1 - no2);
else if(optr == "x")
calcVal = (no1 * no2);
else if(optr == "/")
calcVal = (no1 / no2);
number1 = toString(calcVal);
number2 = "0";
optr = op;
}
String toString(double num) {
return String(num);
}
void function(String e) {
if(number1 != "0" && number2 != "0") {
calculate(e);
}
else if(number1 == "0") {
number1 = number2;
number2 = "0";
}
optr = e;
}
void concatNumbers(String num) {
if(optr == "=")
number1 = "0";
if(num != "."){
if(number2.length() == 1 && number2 == "0")
number2 = num;
else
number2 += num;
}
else {
if(number2.charAt(number2.length()-1) != '.' && number2.indexOf('.') == -1)
number2 += num;
}
}
void backSpace() {
number2 = number2.substring(0, number2.length() - 1);
if(number2 == "")
number2 = "0";
}
void translateIR(int character) {// takes action based on IR code received describing Car MP3 IR codes
if (irrecv.decode(&results)){
if (character == 0XFFFFFFFF)
character = key_value;
switch(character){
case 0x511DBB:
Serial.println("You have pressed the Button CH");
concatNumbers(".");
break;
case 0x52A3D41F:
Serial.println("You have pressed the Button |<<");
function("x");
break;
case 0xD7E84B1B:
Serial.println("You have pressed the Button >>|");
function("/");
break ;
case 0x20FE4DBB:
Serial.println("You have pressed the Button >|");
if(optr != "=")
calculate("=");
break ;
case 0xF076C13B:
Serial.println("You have pressed the Button -");
function("-");
break ;
case 0xA3C8EDDB:
Serial.println("You have pressed the Button +");
function("+");
break ;
case 0xE5CFBD7F:
Serial.println("You have pressed the Button =");
number1 = "0";
number2 = "0";
optr = "=";
break ;
case 0xC101E57B:
Serial.println("You have pressed the Button 0");
concatNumbers("0");
break ;
case 0x97483BFB:
Serial.println("You have pressed the Button 100+");
backSpace();
break ;
case 0x9716BE3F:
Serial.println("You have pressed the Button 1");
concatNumbers("1");
break ;
case 0x3D9AE3F7:
Serial.println("You have pressed the Button 2");
concatNumbers("2");
break ;
case 0x6182021B:
Serial.println("You have pressed the Button 3");
concatNumbers("3");
break ;
case 0x8C22657B:
Serial.println("You have pressed the Button 4");
concatNumbers("4");
break ;
case 0x488F3CBB:
Serial.println("You have pressed the Button 5");
concatNumbers("5");
break ;
case 0x449E79F:
Serial.println("You have pressed the Button 6");
concatNumbers("6");
break ;
case 0x32C6FDF7:
Serial.println("You have pressed the Button 7");
concatNumbers("7");
break ;
case 0x1BC0157B:
Serial.println("You have pressed the Button 8");
concatNumbers("8");
break ;
case 0x3EC3FC1B:
Serial.println("You have pressed the Button 9");
concatNumbers("9");
break ;
}
key_value = character;
irrecv.resume();
}
}
