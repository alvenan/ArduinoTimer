# Arduino Timer
### This is a firmware code made for Arduino Nano to count time according to the triggers as a real timer.
<img src="/img/timer.jpeg" width="200">

## How to use

There are 2 GPIO pins to use:

GPIO4 -> Is an output source that indicates if the timer is ready to start.

[0] -> Turned off or counting

[1] -> Ready to start counting

GPIO2 -> Is the trigger

1st trigger -> Start counting

2nd trigger -> Stop counting and send the result through Serial
