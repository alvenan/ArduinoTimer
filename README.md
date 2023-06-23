# Arduino Timer

This firmware code is designed for Arduino Nano to function as a timer, accurately counting time based on triggers.

<img src="/img/timer.jpeg" width="200">

## How to Use

This repository provides instructions on how to utilize the timer functionality using the following GPIO pins:

1. GPIO4: This pin serves as an output source indicating the readiness of the timer.

   - [0]: Indicates that the timer is turned off or currently counting.
   - [1]: Indicates that the timer is ready to start counting.
  
2. GPIO2: This pin serves as the trigger and has been tested with 200ms rising pulses.

   - 1st pulse: Initiates the counting process.
   - 2nd pulse: Stops the counting and sends the result through Serial communication.<<<<<< HEAD

3. GPIO3: This pin resets the test count.
