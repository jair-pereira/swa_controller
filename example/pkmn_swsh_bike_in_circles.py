import argparse
from time import sleep
from joycon import JoyCon

parser = argparse.ArgumentParser()
parser.add_argument('port')
args = parser.parse_args()

joycon = JoyCon(port=args.port)

try:
    while True:
        joycon.hold_stick('LX', 0)
        joycon.hold_stick('RX', 0)
        
except KeyboardInterrupt:
    joycon.unpair()
