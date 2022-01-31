# StarBlaster

This repository holds the c programs, as well as the top level schematics, used in PSoC Creator to create a game using a PSoC Pioneer Kit, joystick board, and GLCD screen. The tilt control version also uses an accelerometer. 

## StarBlaster Button-Control

This version is the orginal, basic version of starblaster, using a joystick board for control. The program is designed to have:
- Randomly-generated twinkling stars
- Endless scrolling
- The cross-hairs displayed can be moved using the ABCD buttons
- When the joystick is pressed inward, the game displays an explosion as the blaster is fired. 
- Three-level blaster charge-up. The user must wait for the blaster to charge before using it (indicated by changing color of light, starting at green). If the user waits long enough, a hyper-blaster mode is engaged (blue light), which displays a larger explosion. Using the blaster depletes the charge to zero (red light)

## Starblaster Tilt-Control

This version implements an accelerometer in place of the joystick board. 

The changes are as follows:
- The crosshairs displayed can be moved by tilting the screen. When the game system is level, the crosshairs stay still. The speed of movement is proportional to the angle of the screen. 
- The blaster is activated using a single-tap on the accelerometer. The hyperblaster is activated using a double-tap. 
