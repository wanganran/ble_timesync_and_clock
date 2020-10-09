# Arduino Code to Drive the Speakers

The code uses the DAC of Arduino Due and an external clock source (`interruptPin`) to drive the speakers. The external clock should be around 50kHz square wave. 
An interrupt handles the rising edges of the clock source, and the signals defined in `sig.h` are output to the DAC sequentially. It will loop when it reaches the end.
The `startPin` is a switch to start or stop output. 

Note that for MilliSonic application, four speakers are used to transmit signal concurrently. The signal are the same for all the speakers, but with different offsets. 
Specifically, suppose a chirp's duration is 0.05s, the four speakers will start emit the chirp at 0s, 0.01s, 0.02s and 0.03s respectively. 
Hence, when using two Arduino Due to output to four channels, they need to be configured as follows:
* Their external clock source should be the same (e.g., from the BLE chip)
* Their start/stop switch source should be the same (e.g., from a mechanical switch)
* The external clock source and the two Arduinos should share the same ground
* In the code, `count1init` and `count2init` are set to `0` and `wavelen/5` at Arduino #1 (i.e., the first two mics), and `2*wavelen/5` and `3*wavelen/5` at Arduino #2 (i.e., the last two mics) respectively.

