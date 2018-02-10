# Keyboard module for the bomb defuse game

<img src="circuit/keyboard_module_real.jpg" width="350" />

A video of the module in action can be found [here](https://youtu.be/Le4A3sgtfqI)!

## Dependencies

- [AnalogMultiButton](https://github.com/dxinteractive/AnalogMultiButton)

## Building the circuit

See the circuit layout in `circuit/circuit.png`.

<img src="circuit/circuit.png" width="450" />

Alternatively, you can view the circuit on [Tinkercad](https://tinkercad.com). Search for 'defuse_keyboard_module' to find the circuit.

Unfortunately, because the Tinkercad simulator does not allow to import external libraries (AnalogMultiButton in our case), it is not possible to simulate the module there.

## Playing

- At startup, an initialization sequence is played (all LEDs blink sequentially three times in a row).

- A random code is selected in the database (see file `Keyboard.h`), and displayed in coded form to the defuser through a combination of color LEDs.

- A random shift is selected, and displayed in coded form through a combination of color LEDs.

- The defuser has to press every single note in the code correctly, in the right order. If a note is wrong, the red LED will be triggered with a double beep. In that case, the user has to start again from scratch.

## TODO

- Generate documents that indicate the mapping between combinations of color LEDs and code / shift.
