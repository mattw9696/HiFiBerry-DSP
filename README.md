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

