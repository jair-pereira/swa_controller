# AutoSW

**!!under development!!**

## About
This project enables a computer to send controller inputs to your Switch via an AVR microcontroller (arduino, teensy, etc).

I'm building on top of two other projects:
1. [progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick): reverse-engineered the Pokken Pro Pad, allowing us to use microcontrollers to send commands to the Switch. This enables automation! After all, who has time to play video games in this year and economy?

2. [ebith/Switch-Fightstick](https://github.com/ebith/Switch-Fightstick): wrote an interface to send commands from the computer to the Switch using serial communication. This makes automation even easier, as there is no need to recompile and flash the AVR for every new macro. Instead, logic can be updated directly on the computer and executed on the fly, without unplugging the AVR from the Switch.

Previously I had modified [ebith/Switch-Fightstick](https://github.com/ebith/Switch-Fightstick) to allow multiple button presses simultaneously, where the PC maintained the full button state, while the AVR simply "forwarded" it to the Switch ([jair-pereira/SwitchPC_Controller](https://github.com/jair-pereira/SwitchPC_Controller/tree/multi_button)).

There are other interesting repositories for automation such as [Zelda Snowball-thrower](https://github.com/bertrandom/snowball-thrower) and [Splatoon 2 post printer](https://github.com/shinyquagsire23/Switch-Fightstick). 

I used this project mainly to automate shiny hunting in Pokemon Sword/Shield, combined with a separate project that used a capture card and opencv to read the game screen. 

At this point, I thought this project needed no further development. However, that changed with the re-release of Pokemon FireRed and LeafGreen to the Nintendo Switch, as RNG manipulation in these games requires input precision of millisecond. This is not feasible when the PC is responsible for timing. 

This project exists to address this limitation by moving timing control to the AVR, while keeping the command logic on the PC.

## Overview
PC ─serial─> AVR ─usb─> SWITCH

- **PC (Python):** Defines the automation logic, sends button presses and their execution timing
- **AVR:** Receives the button presses and updates its state according to the provided timing

## Requirement
### Hardware
- 1x Teensy (at90usb1286) or Arduino (atmega32u4)
- 1x USB to Serial Adapter
- 1x USB Micro-B Cable
- 2x Male-Female Breadboard Wires

### Software
- Python and the pyserial library
- A software to run containers (Colima, Docker, others) 
    - Alternatively, AVR-GCC

## Compiling the AVR code
Build the docker image:
```bash
docker build -t avrcompiler .
```

Mounts the current directory into the container and compile the code:
```bash
docker run -it --rm -v $(pwd):/work avrcompiler make
```

## Automation with Python
todo

## Done
todo

## Todo
todo :)