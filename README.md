## Motion-Controlled LED Strips for Stairs
### This project involves creating motion-controlled LED strips for stairs. The LED strips are connected to MOSFETs, which are controlled by an ESP32 microcontroller.

### To control the brightness of the LED strips, a TLC5940 LED driver chip is used. This chip allows you to control the brightness of multiple LED strips using a single chip, and its high-resolution PWM output provides smooth and accurate control over the brightness of the LEDs.

### An ultrasonic sensor is used to detect motion on the stairs. When motion is detected, the LED strips turn on and remain on for a specified duration, after which they turn off. The duration of the LED strip's shine time can be adjusted through the web interface, along with the brightness level, number of stairs, and motion sensing state.


### To replicate this project, you will need the following components:

#### - ESP32 microcontroller
#### - TLC5940 LED driver chip
#### - MOSFETs
#### - LED strips (RGB or single color)
#### - Ultrasonic sensor
#### - Resistors, capacitors, and other necessary components
#### - Breadboard or PCB to assemble the circuit
#### - Power supply (5V or 12V, depending on the LED strips)

### Installation and Usage
Clone or download this repository to your local machine.
Open the motion_controlled_led_strips.ino file in the Arduino IDE.
Connect your ESP32 microcontroller and other components to your breadboard or PCB according to the circuit diagram provided.
Upload the code to your ESP32 microcontroller.
Connect to the web server hosted on the ESP32 by entering its IP address in a web browser on any device connected to the same network.
Adjust the brightness, number of stairs, shine duration, and motion sensing state as desired.
Test the motion sensing functionality by walking up and down the stairs.
Contributing
This project is open to contributions and improvements from the community. If you have any suggestions, bug reports, or feature requests, please open an issue on this repository.

