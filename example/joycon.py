import serial
import time

class JoyCon(object):
    mapping = {
        # right d-pad and others
        "Y"       : 0x01,
        "B"       : 0x02,
        "A"       : 0x04,
        "X"       : 0x08,
        "L"       : 0x10,
        "R"       : 0x20,
        "ZL"      : 0x40,
        "ZR"      : 0x80,
        "SELECT"  : 0x100,
        "START"   : 0x200,
        "LCLICK"  : 0x400,
        "RCLICK"  : 0x800,
        "HOME"    : 0x1000,
        "CAPTURE" : 0x2000,
        "RELEASE" : 0x00,

        # left d-pad
        "TOP"          : 0x00,
        "TOP_RIGHT"    : 0x01,
        "RIGHT"        : 0x02,
        "BOTTOM_RIGHT" : 0x03,
        "BOTTOM"       : 0x04,
        "BOTTOM_LEFT"  : 0x05,
        "LEFT"         : 0x06,
        "TOP_LEFT"     : 0x07,
        "CENTER"       : 0x08,

        # for right and left stick (just for reference)
        "STICK_MIN"    : 0,
        "STICK_CENTER" : 128,
        "STICK_MAX"    : 255
    }
    
    def __init__(self, port="COM6", baud=9600):
        #start serial comm
        self._serial = serial.Serial(port, baud)
        
        # button's state
        self._buttons = None
        self._hat     = None
        self._stick   = {"LX":None, "LY":None, 
                         "RX":None, "RY":None}
        
        # send neutral position
        self.pair()
        
    def pair(self):
        self.buttons  = JoyCon.mapping["RELEASE"]
        self.hat      = JoyCon.mapping["HAT_CENTER"]
        self.stick    = "LX", JoyCon.mapping["STICK_CENTER"]
        self.stick    = "LY", JoyCon.mapping["STICK_CENTER"]
        self.stick    = "RX", JoyCon.mapping["STICK_CENTER"]
        self.stick    = "RY", JoyCon.mapping["STICK_CENTER"]

    def unpair(self):
        # send neutral position
        self.pair()
        
        # close serial
        self._serial.close()
    
    # send to teensy then switch
    def send(self, target, command):
        self._serial.write(f'{target} {command}\r\n'.encode('utf-8'))
            
    # button's methods
    def hold_button(self, key):
        self.buttons |= JoyCon.mapping[key]
    
    def release_button(self, key):
        self.buttons &= ~JoyCon.mapping[key]
        
    def press_button(self, key, duration=0.1, delay=0):
        self.hold_button(key)
        time.sleep(duration)
        self.release_button(key)
        time.sleep(delay)

    # stick's methods (left and right)
    def hold_stick(self, target, value):
        self.stick = target, value
        
    def release_stick(self, target):
        self.stick = target, JoyCon.mapping["STICK_CENTER"]
        
    def press_stick(self, target, value, duration=0.1, delay=0):
        self.hold_stick(target, value)
        time.sleep(duration)
        self.release_stick(target)
        time.sleep(delay)
    
    # left d-pad's methods
    def hold_hat(self, key):
        self.hat = JoyCon.mapping[key]
        
    def release_hat(self):
        self.hat = JoyCon.mapping["HAT_CENTER"]
        
    def press_hat(self, key, duration=0.1, delay=0):
        self.hold_hat(key)
        time.sleep(duration)
        self.release_hat()
        time.sleep(delay)
        
    # setters and getters
    @property
    def buttons(self):
        return self._buttons
    
    @buttons.setter
    def buttons(self, value):
        self._buttons = value
        self.send("BTN", self._buttons)
        
    @property
    def hat(self):
        return self._hat
    
    @buttons.setter
    def hat(self, value):
        self._hat = value
        self.send("HAT", value)
        
    @property
    def stick(self):
        return self._stick
    
    @stick.setter
    def stick(self, value):
        self._stick[value[0]] = value[1]
        self.send(value[0], value[1])