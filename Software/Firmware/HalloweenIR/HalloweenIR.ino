/* Project: HalloweenIR
 * Description: 
 * 
 * Attribution: IRremote libraries; Ken Shirriff, Kristian Lauszus, Matthias Neeracher
 * License: GNU Lesser General Public License v2.1
*/

#include <IRremote.h>
#include <Servo.h>

const uint16_t SERVO_PIN = 3;
const uint16_t LED1_PIN = 5;
const uint16_t LED2_PIN = 6;
const uint16_t IRRECV_PIN = 8;
const uint16_t MAGICWAND_SERIAL_NUM = 153312897; //153312897 is the decimal value of hex 0x9235E81

IRrecv irrecv(IRRECV_PIN);
decode_results results;

Servo pumpkinServo;
const uint16_t pumpkinOpenPosition = 0;
const uint16_t pumpkinClosedPosition = 180;


/* Function: setup
 * 
 */
void setup()
{
  Serial.begin(9600);
  Serial.print(F("Homebrewed IR Magic Wand System 1.0 initializing..."));

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  
  irrecv.enableIRIn(); // Start the receiver
  
  pumpkinServo.attach(SERVO_PIN);
  pumpkinServo.write(pumpkinClosedPosition);
  delay(15);
  Serial.println(F("READY!"));
}



/* Function: loop
 * 
 */
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    decodeIR(&results);
    irrecv.resume(); // Receive the next value
  }
}




/* Function: decodeIR
 * 
 */
void decodeIR(decode_results *results) {

  int count = results->rawlen;

  if (results->decode_type == MAGIQUEST) {
    Serial.println(F("  |-> MAGIQUEST"));
    if ((int)results->value == MAGICWAND_SERIAL_NUM) {
      Serial.println(F("     |-> MIKE WAND"));
      turnLEDEyesOn();
      operatePumpkinServo(pumpkinOpenPosition);
      delay(100);
      turnLEDEyesOff();
      delay(100);
      operatePumpkinServo(pumpkinClosedPosition); 
      delay(100);  
    }
  }
}



/* Function: turnLEDEyesOn
 * 
 */
void turnLEDEyesOn() {
  Serial.println(F("Turning RED EYES ON!"));
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
}



/* Function: turnLEDEyesOff
 * 
 */
void turnLEDEyesOff() {
  Serial.println(F("Turning RED EYES OFF!"));
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
}



/* Function: operatePumpkinServo
 * 
 */
void operatePumpkinServo(const uint16_t desiredServoPosition) {
  Serial.print(F("Moving pumpkin head to position: "));
  Serial.println(desiredServoPosition);
  pumpkinServo.write(desiredServoPosition);
  delay(15);
}

