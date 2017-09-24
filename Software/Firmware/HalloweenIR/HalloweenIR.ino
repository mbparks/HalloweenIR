/*
   IRremote: IRrecvDump - dump details of IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
   JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
   RCMM protocol added by Matthias Neeracher
*/

#include <IRremote.h>


int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Serial.println("starting...");
  irrecv.enableIRIn(); // Start the receiver
}


// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void dump(decode_results *results) {

  int count = results->rawlen;

  if (results->decode_type == MAGIQUEST) {
    Serial.println("  |-> MAGIQUEST");
    if (results->value == 0x9235E81) {
      Serial.println("     |-> MIKE WAND");
    }
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}
