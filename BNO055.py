"""!@file       DRV8847.py
    @brief      A driver for controlling motors
    @details    This file contains a class which can be called to generate a motor
                driver object. That object allows for control of any subordinate 
                objects generated from a motor class via a single pulse-width 
                modulation channel. This class also allows the user to detect 
                faults from, enable, or disable any subordinate motor objects.
    @author     Logan Williamson
    @author     Brianna Roberts
    @date       02/09/2022
"""

# from motor import Motor
from pyb import I2C, delay #, Pin, Timer, ExtInt,
from time import sleep_ms
import struct
import os

class BNO055:
    '''!@brief      A motor driver class for the BNO055 from TI.
        @details    Objects of this class can be used to configure the BNO055 
                    motor driver and to create one or more objects of the
                    Motor class which can be used to perform motor
                    control.
                    Refer to the BNO055 datasheet here:
                        https://cdn-learn.adafruit.com/assets/assets/000/036/832/original/BST_BNO055_DS000_14.pdf
                        
                    Device Calibration Information:
                        https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/device-calibration
                        
                    bno055 Reference CODE:
                        https://github.com/micropython-IMU/micropython-bno055
    '''
    def __init__ (self):
        '''!@brief      Initializes and returns a BNO055 object.
            @details    Upon calling the BNO055 class, the __init__ method will instantiate
                        a motor driver object with the 
                        timerPin, sleepPin, and faultPin pins passed in by the user.
        '''
        ##@brief        bus_addr is the adress for bus         
        # @details      address on the BNO055 that is used in the configuration mode
        self.bus_addr = 0x28
        ##@brief        cal_coeff_addr is the initial adress for calibration coefficients   
        # @details      address for initial calibration location for the BNO055
        #               having a byte array of a set size will correlate with how
        #               many coefficients will be run through. In this case we use 22.
        self.cal_coeff_addr = 0x55
        
        ##@brief        vel_pos_data_addr is the initial adress for velocity and position data  
        # @details      address for location on the BNO055 for the gyroscope, accelerometer, 
        #               and magnetometer.
        self.vel_pos_data_addr = 0x14
        
        ##@brief        object i2c gets set to controller mode 
        # @details      this initializes the i2c bus 1 object in controller mode.
        self.i2c = I2C(1,I2C.CONTROLLER)                 #Instantiates i2c bus object
        
        self.i2c.mem_write(0b0000,self.bus_addr,0x3D)    #Enables BNO055 in CONFIG mode
        
        ##@brief     MODE is the variable corresponding to the FUSION operating mode of the IMU
        # @details   Passing in a value for MODE to the set_mode method enables the user to select 
        #            one of the three available FUSION modes for the BNO055 Inertial Measurement Unit. 
        #            MODE value 0 corresponds to configuration mode, which the BNO055 object is instantiated in.
        #            MODE value 1 corresponds to IMU mode, 2 corresponds to NDOF mode, and 3 corresponds to M4G mode.
        self.MODE = 0
        
        delay(19)
        
        ##@brief        buf creates a byte array of length 12 
        # @details      this byte array is used in iterating through the velocity
        #               and positional data of the addr. This is run within the update method
        self.buf = bytearray(12)    # Preallocate position and velocity data byte array
        
        ##@brief        bufcal creates a byte array of length 22 
        # @details      this byte array is used in iterating through the calibration
        #               coefficients. 
        self.bufcal = bytearray(22) # Preallocate calibration coefficients byte array
        
        
        ##@brief        theta_x object created for x position values.
        # @details      theta_x is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.theta_x = 0
        ##@brief        theta_y object created for y position values.
        # @details      theta_y is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.theta_y = 0
        ##@brief        theta_z object created for z position values.
        # @details      theta_z is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.theta_z = 0
        
        
        ##@brief        omega_x object created for x velocity values.
        # @details      omega_x is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.omega_x = 0
        ##@brief        omega_y object created for y velocity values.
        # @details      omega_y is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.omega_y = 0
        ##@brief        omega_z object created for z velocity values.
        # @details      omega_z is initiated at 0 and will be repopulated with 
        #               actual values in the update state.
        self.omega_z = 0
        
    def set_mode(self,MODE):
        '''!@brief      Sets the mode for the BNO055 board.
            @details    If a value for mode is passed in, thie method will change the 
                        mode of the board. The modes that can be set are 
                        CONFIG mode: MODE = 0
                        IMU mode: MODE = 1
                        NDOF mode: MODE = 2
        '''

        if MODE == 0:   #CONFIG mode
            self.MODE = 0
            self.i2c.mem_write(0b0000,self.bus_addr,0x3D)
            delay(19)
        elif MODE == 1:  #IMU mode
            self.MODE = 1
            self.i2c.mem_write(0b1000,self.bus_addr,0x3D)
            delay(7)
        elif MODE == 2: #NDOF mode
            self.MODE = 2
            self.i2c.mem_write(0b1100,self.bus_addr,0x3D)
            delay(7)
            
    def get_calStatus(self):
        '''!@brief      Gets the calibration status of the board.
            @details    Reads the existing calibration coefficients into respective 
                        calibration coefficient byte arrays. These include the
                        magnetometer, accelerometer, accelerometer, and the system 
                        coefficients.
                        this method is instantiated in state 2 of taskIMU which is
                        the calibration state                        
        '''
        
        ##@brief        cal_byte creates an object that will be used to store calibration coefficients
        # @details      this uses the mem_read which reads 1 byte from memory peripheral 40
        #               starting at adress 0x35. Because this is used multiple times,
        #               the index is also used starting at [0].
        self.cal_byte = self.i2c.mem_read(1,40,0x35)[0]
        
        # status for calibration
        ##@brief        mag_stat creates an object for the calibration coefficients related to the magnetometer
        # @details      mag_stat reads through the existing calibration coefficients
        #               created in cal_byte and adopts the values related to the
        #               magnetometer.
        self.mag_stat = (self.cal_byte & 0b00000011)
        
        ##@brief        acc_stat creates an object for the calibration coefficients related to the accelerometer
        # @details      acc_stat reads through the existing calibration coefficients
        #               created in cal_byte and adopts the values related to the
        #               accelerometer.
        self.acc_stat = (self.cal_byte & 0b00001100)>>2
        
        ##@brief        gyr_stat creates an object for the calibration coefficients related to the gyroscope
        # @details      gyr_stat reads through the existing calibration coefficients
        #               created in cal_byte and adopts the values related to the
        #               gyroscope.
        self.gyr_stat = (self.cal_byte & 0b00110000)>>4
        
        # is this right?? vvv
        
        ##@brief        sys_stat creates an object for the calibration coefficients related to the system
        # @details      sys_stat reads through the existing calibration coefficients
        #               created in cal_byte and adopts the values related to the
        #               system.
        self.sys_stat = (self.cal_byte & 0b11000000)>>6
        
        return self.mag_stat, self.acc_stat, self.gyr_stat, self.sys_stat
    
    def get_calConstants(self): 
        '''!@brief      Gets the calibration constants for the board.
            @details    once the calibration status has been recognized as calibrated,
                        reads the coefficients into object cal_coeffs.
        '''
        
        ##@brief        cal_coeffs creates an object that will be used to store calibration coefficients
        # @details      this uses mem_read which reads bufcal bytes from memory peripheral bus_addr
        #               starting at adress cal_coeff_addr. 
        self.cal_coeffs = self.i2c.mem_read(self.bufcal, self.bus_addr, self.cal_coeff_addr)
        return self.cal_coeffs
    
    def write_calConstants(self,calDATA):
        '''!@brief      Gets the calibration constants for the board.
            @details    This method is instantiated in state one of taskIMU which writes the
                        calibration constants into object i2c
        '''
        self.i2c.mem_write(calDATA,self.bus_addr,self.cal_coeff_addr)
        
    def update(self):
        '''!@brief      Updates the values of omega x, y, and z and theta x, y, and z.
            @details    This method is instantiated in state 1 and 2 of taskIMU 
                        which updates and scales the values of positions and motor speeds
                        of the platform.
        '''
        
        # what is the adress for our peripherals
        self.i2c.mem_read(self.buf, self.bus_addr, self.vel_pos_data_addr)
        self.omega_y, self.omega_x, self.omega_z, self.theta_z, self.theta_x, self.theta_y = struct.unpack('<hhhhhh',self.buf)
        
        #Process Euler angles into degrees, change sense of axes to correspond to platform axes
        self.theta_x = -self.theta_x/16
        self.theta_y = self.theta_y/16
        self.theta_z = -self.theta_z/16 + 360
        
        self.omega_x = self.omega_x/16
        self.omega_y = -self.omega_y/16
        self.omega_z = self.omega_z/16
        
    def get_data(self):
        '''!@brief      Gets the velocity and positional data for the platform.
            @details    This method is instantiated in state 1 of taskIMU 
                        which returns all the values that are collected and scaled 
                        in the update method.
        '''
        return (self.theta_x,self.theta_y,self.theta_z,self.omega_x,self.omega_y,self.omega_z)

if __name__ == '__main__':
    # Adjust the following code to write a test program for your motor class. Any
    # code within the if __name__ == '__main__' block will only run when the
    # script is executed as a standalone program. If the script is imported as
    # a module the code block will not run.
    #bus_addr = 0x28                    # Physical bus address for i2c
    IMU = BNO055()                      # Instantiate BNO055 derived object, IMU, in CONFIG mode
    IMU.set_mode(2)                     # Set IMU to NDOF mode
    filename = "IMU_cal_coeffs.txt"     # Assign a filename for storing calibration coefficients
    
## Testing for calibration
    while True:
        IMU.update()
        #Create a .txt file containing the calibration coefficients if one doesn't already exist
        if filename in os.listdir():   # if file exists, read from it
            # open filename and 'r' read from it
            with open(filename, 'r') as f:
                # Read the first line of the file
                cal_data_string = f.readline()
                # Split the line into multiple strings and then convert each one to a float
            cal_coeffs = cal_data_string.split(',')
            for i in range(0, len(cal_coeffs)):
                cal_coeffs[i] = int(cal_coeffs[i],16)
                IMU.bufcal[i] = cal_coeffs[i]
            IMU.write_calConstants(IMU.bufcal)
            # IMU.get_calConstants()
            # print(IMU.cal_coeffs)

        else:
            ## These lines are for manual calibration if there is no .txt file present on the pybflash for bypassing this step.
            ## Currently commented out so we can just test writing to a .txt file, but will need to be reintroduced once we have 
            ## that writing to .txt file working so that we actually get the coefficients that we want.
            IMU.get_calStatus()
            
            sleep_ms(1000)
        # IMU in IMU mode
            if IMU.MODE == 1:
                print('acc_stat:',IMU.acc_stat,'gyr_stat:',IMU.gyr_stat)
                if IMU.acc_stat==3 and IMU.gyr_stat==3:
                    # run the get_calConstants() in IMU file
                    IMU.get_calConstants()
                    cal_coeffs = IMU.cal_coeffs
                    with open(filename, 'w') as f:
                        calString = f.write(','.join(hex(cal_coeff) for cal_coeff in cal_coeffs))
                        str_list = []
                    for cal_coeff in cal_coeffs:
                        str_list.append(hex(cal_coeff))
                        f.write(','.join(str_list))
        # IMU in NDOF mode
            elif IMU.MODE == 2:
                print('mag_stat:',IMU.mag_stat,'acc_stat:',IMU.acc_stat,'gyr_stat:',IMU.gyr_stat,'sys_stat:',IMU.sys_stat)
                if IMU.mag_stat==3 and IMU.acc_stat==3 and IMU.gyr_stat==3 and IMU.sys_stat==3:
                    IMU.get_calConstants()
                    cal_coeffs = IMU.cal_coeffs
                    print(f'Calibration complete. Calibration coefficients are: {cal_coeffs}')
                    str_list = []
                    for cal_coeff in cal_coeffs:
                        str_list.append(hex(cal_coeff))
                    with open(filename, 'w') as f:
                        f.write(','.join(str_list))
    
# ## Testing for positional and velocity output data
#     while True:
#         IMU.update()
#         IMU.get_data()
#         print('theta_x:',-IMU.theta_x/16,'theta_y:',IMU.theta_y/16,'theta_z:',-IMU.theta_z/16)
#         print('omega_x:',IMU.omega_x/16,'omega_y:',IMU.omega_y/16,'omega_z:',IMU.omega_z/16)
#         sleep_ms(1000)
    
