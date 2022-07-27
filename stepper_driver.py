import pyb
from pyb import SPI, Timer, Pin


class StepperDriver:

    def __init__(self, chip_select_1, chip_select_2, chip_enable_1, chip_enable_2):
        self.X_TARGET = 0b0000000
        self.X_ACTUAL = 0b0000001
        self.V_MIN    = 0b0000010
        self.V_MAX    = 0b0000011
        self.V_TARGET = 0b0000100
        self.V_ACTUAL = 0b0000101
        self.A_MAX    = 0b0000110
        self.A_ACTUAL = 0b0000111
        self.PMUL_PDIV = 0b0001001
        # Expecting more addresses
        
        #SPI receiving comm buffer
        recv_buf = bytearray(4)

        ## Pin object instantiation
        #Enable and Chip Select
        self.CS_1 = chip_select_1
        self.CS_2 = chip_select_2
        self.ENN_1 = chip_enable_1
        self.ENN_2 = chip_enable_2
        
        # Set ENN pins high in preparation for instantiating SPI object
        self.ENN_1.high()
        self.ENN_2.high()
        configureTMC4210()


    def writeRegister(address, data, CS):
        # Write data to address
        self.SPI.send_recv(address, data)
        

    def readRegister(address, CS):
        send_buf = bytearray([address,
                              0b00000000,
                              0b00000000,
                              0b00000000])
        self.CS_1.low()
        self.SPI.send_recv(send_buf, self.recv_buf)
        self.CS_1.high()
        return self.recv_buf

    def setTargetPosition(address, position, chip_select):
        # Write into register
        # Use acceleration criteria
        self.SPI.write(address, position, chip_select)

    def configureTMC4210():
        '''
        If needed perform any configuration of the TMC4210.
        '''
        setRampMode(self.RAMP_REGISTER, RAMP_MODE)

    def setVelocity(address, velocity):
        # Write into register
        # Use acceleration criteria
                # Read from address into buffer
        address = (self.V_ACTUAL<<1)
        return writeRegister(address) #Returns recv_buf

    def setAcceleration(address, acceleration):
        # Write into register
        # Use acceleration criteria
        # Write PMUL and PDIV into addresses
                # Read from address into buffer
        #address = (self.<<1)
        #return writeRegister(address) #Returns recv_buf
        from math import floor, log
#         def setPulseRampDiv(maxVelocity, maxAccel):
#             pulseDiv = floor(log( float(int(clockFreq)) / ((int(abs(maxVelocity)))) ) / log(2.0));
#             rampDiv = floor(log(float((clockFreq * clockFreq) / (abs(maxAccel) * (pulseDiv+29)))) / log(2.0));
#         def setPMUL_PDIV(maxAccel):
#         pmul = int

    def setRampMode(address, mode):
        # Write ramp mode to address
        self.SPI.send_recv(address, mode)

    def readActualPosition(address):
        # Read from address into buffer
        address = (self.X_ACTUAL<<1)|0b1
        return readRegister(address) #Returns recv_buf

    def readAcceleration(address):
        # Read from address into buffer
        address = (self.A_ACTUAL<<1)|0b1
        return readRegister(address) #Returns recv_buf
    
    def readVelocity():
        # Read from address into buffer
        address = (self.V_ACTUAL<<1)|0b1
        return readRegister(address) #Returns recv_buf
        

    def setPmulPdiv(acceleration):
        pass
    
if __name__=='__main__':
    ENN_1 = Pin(Pin.cpu.C3,mode=Pin.OUT_PP) #chip1_enable
    ENN_2 = Pin(Pin.cpu.C2,mode=Pin.OUT_PP) #chip2_enable
    CS_1 = Pin(Pin.cpu.B0,mode=Pin.OUT_PP)  #chip1_select
    CS_2 = Pin(Pin.cpu.C0,mode=Pin.OUT_PP)  #chip2_select
    
    # Timer signal setup
    timer = pyb.Timer(4, period=3, prescaler=0)
    CLK = timer.channel(1, pin=pyb.Pin.cpu.B6, mode=pyb.Timer.PWM, pulse_width=2)
    
    # Set up SPI
    SPI = SPI(2, SPI.CONTROLLER, baudrate=115_200, polarity=1, phase=1)
    
    #Instantiate Driver Objects
    
    
    
    
    
