import argparse
from time import sleep
from joycon import JoyCon

parser = argparse.ArgumentParser()
parser.add_argument('port')
args = parser.parse_args()

joycon = JoyCon(port=args.port)

try:
    while True:
        sleep(0.1)
        joycon.press_button('A')
except KeyboardInterrupt:
    joycon.press_button('RELEASE')
    joycon.unpair()