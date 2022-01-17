# Record the angular velocity finger tips
# Using bluetooth to transfer data
import serial
import mouse
import time
import numpy as np
ser = serial.Serial("COM11", 9600) # read the bluetooth data
count = 0
record_alphabet = 'Y' # record alphabet 
exp = []
read_value_x = 0
read_value_y = 0
read_value_z = 0
while count < 50: # record times
    start = time.time()
    #print(read_bluetooth[0],read_bluetooth[1])
    #print(read_bluetooth.shape())
    print('-----------------------')
    print('start : ',count)
    sec_x = []
    sec_y = []
    sec_z = []
    import time
    for i in range(300):
        read_bluetooth=ser.readline()
        try:
            read_value_x = int(read_bluetooth[0])-127
            read_value_y = int(read_bluetooth[1])-127
            read_value_z = int(read_bluetooth[2])-127
        except:
            pass
        sec_x.append(read_value_x)
        sec_y.append(read_value_y)
        sec_z.append(read_value_z)
        

    end = time.time()
    sec_all = [sec_x,sec_y,sec_z]
    exp.append(sec_all)
    count += 1
    print(np.mean(sec_x),np.mean(sec_y),np.mean(sec_z))
    print(end-start)
print(len(exp))
np.save(record_alphabet,exp) #save the alphabet