# NeoPixels - Serial

This project uses an Arduino to control a 4-meter NeoPixel LED strip with 240 LEDs.

The Arduino script listens for instructions sent via Serial communication. Each instruction consists of 5 characters in the following format:

- **First character:** A leading `*`
- **Next three characters:** Integers ranging from `000` to `999`, always padded with leading zeros
- **Last character:** A trailing `$`

Based on the number received via Serial, the script turns on the LEDs sequentially, starting from LED #0 up to the specified number. For example, if the instruction `*120$` is received, the first 120 LEDs will be turned on, while the remaining LEDs will stay off.

## TouchDesigner Patch

The accompanying TouchDesigner patch is inspired by the tutorial at [this link](https://youtu.be/8J2WSOWAyTs).

### Features:
1. **LFO for Frequency Control:**  
   This LFO controls the frequency at which data is sent via Serial communication.
   
2. **Sine Wave Generator:**  
   An LFO generates a sine wave curve between 0 and 240. This value is formatted as `*###$` (e.g., `*001$`) and sent to the Arduino, controlling the NeoPixel LEDs.