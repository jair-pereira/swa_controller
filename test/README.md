## Tests
This directory contains simplified versions of Joystick.c to test implemented features. 
To compile one of those test:
```bash
docker run -it --rm -v $(pwd):/work gccavr make -f test/makefile_TimerTest
```