nRF5 BLE timesync transmitter and 50kHz output to drive two Arduino Due output sound synchronously. 

`drive_speaker` folder contains Arduino Due source codes that drive two speakers per Due to play chirps. Flash two Dues to drive four speakers concurrently. 

Current issue: speakers output static noise. It seems due to DAC output of Arduino Due. A high-pass filter between the amplifier output and the speaker would address this problem.

# Assembly

Two nRF52840 dev boards are used as the tag side and the AP side respectively. The tag side is connected to the microphone. The AP side is connected with the two Arduinos and also a PC or Raspberry Pi via the USB Serial port. The two USB cables from the Arduinos can be powered without connecting to the PC.

# Other repos

The code for AP side nRF52840 is at https://github.com/mkimhj/shio/tree/bp-calibration/udon
The code for tag side nRF52840 is at https://github.com/mkimhj/shio/tree/bp-calibration
