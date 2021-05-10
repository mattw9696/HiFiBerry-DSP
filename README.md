# HiFiBerry DAC+DSP 

## Set-Up 

### 1. Connect Board. 
The board should be connected to any Pi. For testing the audio, connect either the SPDIF output or Analog output to some speakers. 
Datasheet: 
https://www.hifiberry.com/docs/data-sheets/datasheet-dac-dsp/

### 2. Configure the Software.
1. In /boot/config.txt - You may need to do this from root 'sudo -i'
..1. Remove `dtparam=audio=on`
..2. Add `dtoverlay=hifiberry-dacplusdsp` 
..3. Enable SPI & I2S
2. Verify board is connected
```root@pi:~# aplay -l
**** List of PLAYBACK Hardware Devices ****
card 0: sndrpihifiberry [snd_rpi_hifiberrydacplusdsp_sou], device 0: Hifiberry DAC+DSP SoundCard HiFi dacplusdsp-codec-0 [Hifiberry DAC+DSP SoundCard HiFi dacplusdsp-codec-0]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
```
3. Test the audio!
..1. Copy a .wav file to the Raspberry Pi
..2. Play the file with `aplay ~/file-name.wav`

4. Install dsptoolkit
..1. Check Python3 & pip are installed.
..2. Install toolkit `sudo pip3 install --upgrade hifiberrydsp`

Sources: 
https://www.hifiberry.com/docs/software/configuring-linux-3-18-x/
https://www.hifiberry.com/docs/software/using-the-dac-dsp-to-record-audio-from-s-pdif/
https://github.com/hifiberry/hifiberry-dsp

### 3. Modify sigma schematic 

Connect via TCP IP (port 8089) - Run as root

Sources: 
https://github.com/hifiberry/hifiberry-dsp/blob/master/doc/adaptexistingprofiles.md

## CLI Tools

### Volume Tool
A volume control tool has been created to modify the volume based on a percentage. This has been developed in C and can be built using the make file.
`make`

This uses the provided SPI CLI tool dsptoolkit, based on the DSP schematic in this repo. To use with an updated schematic:
1. Update the DSP schematic and push to DSP.
2. Ensure the current version has been pushed to self boot memory
3. Acquire the register address of the Volume slider from the schematic, or from the exported artefacts. 
4. Modify the address value in volume.c
5. Re-make the dsp-volume tool  
 
## Example Profiles

### IIR Filter Profile
This is an example of how to export a project into a usable profile. This is achieved by writing the DSP schematic to the eeprom via the self-boot option in SigmaStudios, a sequence created and saved as an xml file. This XML file does not contain any metadata. 

This sequence can be followed in the following guide.  
https://github.com/hifiberry/hifiberry-dsp/blob/master/doc/adaptexistingprofiles.md

To load the DSP profile:
`dsptoolkit load-profile /path/to/profile/dacdsp-profile.xml`

The additional IIR filter has been added at the very end of the audio path, prior to the SPDIF output. The IIR filter coefficients should be normalised, the register values and coeficient values for the filter are:
```b2: 0x2D3 = 0.0
b1: 0x2D4 = 0.0
b0: 0x2D5 = 1.0
a2: 0x2D6 = 0.0
a1: 0x2D7 = 0.0
```
