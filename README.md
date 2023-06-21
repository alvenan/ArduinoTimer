# Arduino Timer
### This firmware code is designed for Arduino Nano to function as a timer, accurately counting time based on triggers.
<img src="/img/timer.jpeg" width="200">

## How to Use

This repository provides instructions on how to utilize the timer functionality using the following GPIO pins:

1. GPIO4: This pin serves as an output source indicating the readiness of the timer.

   - [0]: Indicates that the timer is turned off or currently counting.
   - [1]: Indicates that the timer is ready to start counting.

2. GPIO2: This pin acts as the trigger.

   - 1st trigger: Initiates the counting process.
   - 2nd trigger: Stops the counting and sends the result through the Serial communication.
