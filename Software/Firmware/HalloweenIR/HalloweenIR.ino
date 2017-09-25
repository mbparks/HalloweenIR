/* Project: HalloweenIR
 * Description: Use a MagiQUest magic wand to open DIY fun for Halloween. 
 * Wehn the correct wand is waved at the IR sensor, red LED mimicking a pumpkin's eyes
 * will light up and a servo will open the top of a pumpkin to reveal a candy treasure
 * inside.
 * Last Modified: 25 September 2017
 * 
 * Attribution: IRremote libraries; Ken Shirriff, Kristian Lauszus, Matthias Neeracher
 * License: GNU Lesser General Public License v2.1
*/

#include <IRremote.h>
#include <Servo.h>

const uint16_t SERVO_PIN = 10;
const uint16_t LED1_PIN = 5;
const uint16_t LED2_PIN = 6;
const uint16_t IRRECV_PIN = 8;
const uint16_t MAGICWAND_SERIAL_NUM = 153312897; //153312897 is the decimal value of hex 0x9235E81

IRrecv irrecv(IRRECV_PIN);
decode_results results;

Servo pumpkinServo;
const uint16_t pumpkinOpenPosition = 90;
const uint16_t pumpkinClosedPosition = 0;
const uint16_t pumpkinDelayLong = 15000;
const uint16_t pumpkinDelayShort = 3000;


/* Function: setup
 * 
 */
void setup()
{
  Serial.begin(9600);
  Serial.println(F("Homebrewed IR Magic Wand System 1.0 initializing..."));

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);

  turnLEDEyesOn();
  delay(pumpkinDelayLong);
  turnLEDEyesOff();
  delay(pumpkinDelayShort);
  
  irrecv.enableIRIn();
  
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
    irrecv.resume();
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
      delay(pumpkinDelayLong);
      turnLEDEyesOff();
      delay(pumpkinDelayShort);
      operatePumpkinServo(pumpkinClosedPosition); 
      delay(pumpkinDelayShort);  
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

