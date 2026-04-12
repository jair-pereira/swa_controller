import argparse
from time import sleep
from joycon import JoyCon

# this script works for regice, registel, and regirock
# you have to manually the script when the shiny appears

parser = argparse.ArgumentParser()
parser.add_argument('port')
args = parser.parse_args()

joycon = JoyCon(port=args.port)

joycon.press_button('A') #wake-up

try:
    while True:
        # interact
        joycon.press_button('A', delay=0.35)
        joycon.press_button('A', delay=0.65)
        joycon.press_button('A', delay=0.65)
        joycon.press_button('A', delay=40) 
        # wait 40 seconds before resetting
        # if it is shiny, press crlt+c or remove the teensy
        
        # close the game
        joycon.press_button('HOME', delay=0.65)
        joycon.press_button('X', delay=1.5) 
        joycon.press_button('A', delay=3.5) 
        
        # open the game
        joycon.press_button('A', delay=1.5) #game
        joycon.press_button('A', delay=23)  #profile
        joycon.press_button('A', delay=8)   #ingame title screen
        
except KeyboardInterrupt:
    joycon.unpair()
