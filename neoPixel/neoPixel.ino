#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6
#define NUMPIXELS 240

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


String receivedString = "";  // Variable to store the received string
bool receivingData = false;  // Flag to track if data reception is in progress

void setup() {
  Serial.begin(115200);  // Initialize Serial communication
  Serial.println("Waiting for data...");
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {

  pixels.clear();  // Set all pixel colors to 'off'

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    // Check for the start character
    if (incomingChar == '*') {
      receivingData = true;  // Start receiving data
      receivedString = "";   // Clear the received string
    }

    // Append the character if we're receiving data
    if (receivingData) {
      receivedString += incomingChar;

      // Check for the end character
      if (incomingChar == '$') {
        receivingData = false;  // Stop receiving data

        // Validate the format of the string
        if (isValidString(receivedString)) {
          Serial.print("Valid string received: ");
          Serial.println(receivedString);
          processReceivedString(receivedString);  // Process the valid string
        } else {
          Serial.print("Invalid string received: ");
          Serial.println(receivedString);
        }
        receivedString = "";  // Clear the string for the next message
      }
    }
  }
}

// Function to validate the string format
bool isValidString(String str) {
  // Check the total length (should be 5: * + 3 digits + $)
  if (str.length() != 5) {
    return false;
  }

  // Check the first character is '*'
  if (str.charAt(0) != '*') {
    return false;
  }

  // Check the last character is '$'
  if (str.charAt(4) != '$') {
    return false;
  }

  // Check the middle three characters are digits
  for (int i = 1; i <= 3; i++) {
    if (!isDigit(str.charAt(i))) {
      return false;
    }
  }

  return true;  // Passed all checks
}

// Function to process the received string
void processReceivedString(String str) {
  // Extract the numerical part of the string (characters 1 to 3)
  String numericPart = str.substring(1, 4);
  int value = numericPart.toInt();  // Convert to integer

  // Perform your desired actions with the value
  Serial.print("Processed value: ");
  Serial.println(value);
  animatePixel(value);

    delay(10);
    pixels.show();  // Send the updated pixel colors to the hardware.
    delay(10);
}

void animatePixel(int pixel) {
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < pixel; i++) {  // For each pixel...

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  }
}
