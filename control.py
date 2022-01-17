# this program is used to control the mouse and keyboard using glove mouse
import serial
import mouse
import time
from model import *
import torch
from queue import Queue
buffer = 0
qx = []
qy = []
qz = []
model = torch.load('all_final.pt').cuda() # read the well train model from train.py
ser = serial.Serial("COM11", 9600)
last_band = 0
while True:
    read_bluetooth=ser.readline() 

    try:
        read_value_x = int(read_bluetooth[0])-127 # bluetooth only allow 0-255, as a result,  
        read_value_y = int(read_bluetooth[1])-127 
        read_value_z = int(read_bluetooth[2])-127
    except: # bluetooth will miss the value sometime
        pass
    bend = 0
    try:
        pressure1 = read_bluetooth[3] #index finger pressue
        pressure2 = read_bluetooth[4] #middle finger pressure
        bend = read_bluetooth[5]   #ring finger bending
    except:
         pass
    if (abs(read_value_x)<3): #avoid noise
         read_value_x = 0
    if (abs(read_value_y)<3):
         read_value_y = 0
    ratio = 1
    #--------------------alphabet predict------------------
    if (bend == 1): 
        sec_x = []
        sec_y = []
        sec_z = []
        acc = 0
        print(acc)
        while (acc < 12):
            read_bluetooth=ser.readline()
            try:
                read_value_x = int(read_bluetooth[0])-127
                read_value_y = int(read_bluetooth[1])-127
                read_value_z = int(read_bluetooth[2])-127
            except:
                pass
            if len(qx) >= buffer:
                del qx[0]
                del qy[0]
                del qz[0]
            qx.append(read_value_x)
            qy.append(read_value_y)
            qz.append(read_value_z)
            acc = (read_value_x**2+read_value_y**2+read_value_z**2)**0.5
            #print(acc)
        print('------------------------------start-----------------------------------')
        #-------------------------recording data---------------------
        for i in range(buffer):
            read_bluetooth=ser.readline()
            try:
                read_value_x = qx[i]
                read_value_y = qy[i]
                read_value_z = qz[i]
            except:
                pass
            sec_x.append(read_value_x)
            sec_y.append(read_value_y)
            sec_z.append(read_value_z)

        for i in range(300-buffer):
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
        sec_all = [sec_x,sec_y,sec_z]
        for ax in range(3):
            for j in range(300):
                temp = j
                while (sec_all[ax][j]<-80):
                    temp = j-1
                    sec_all[ax][j] = sec_all[ax][temp]
        start = time.time()
        train_numpy = np.array(sec_all).reshape(([-1,3,300])).astype('float')
        train_numpy = np.transpose(train_numpy, (0, 2, 1))
        for i in range(len(train_numpy)):
            for k in range(3):
                max_num = np.max(train_numpy[i,:,k])
                min_num = np.min(train_numpy[i,:,k])
                if((max_num - min_num)!= 0):
                    train_numpy[i,:,k] = (train_numpy[i,:,k]-min_num)/(max_num - min_num)
                else:
                    train_numpy[i,:,k] = 0
        data = torch.from_numpy(train_numpy).cuda().float()
        with torch.no_grad():
            outputs = model(data) #predict by model
        #print(np.sum(outputs.cpu().detach().numpy()))
        print('get',chr(np.argmax(outputs.cpu().detach().numpy()) + 97 ))
        end = time.time()
        print('time',end - start)
        last_band = 1
    #--------------------right click------------------
    elif (pressure1>150 and pressure2>150):
        last_band = 0
        mouse.right_click()
        #print('right')
        for i in range(5):
            read_bluetooth=ser.readline()
    #--------------------scroll up and down------------------
    else:
        last_band = 0
        if (pressure1>30 and pressure2>30 ):
            if (read_value_y>5):
                mouse.wheel(1)
               
            else:
                mouse.wheel(-1)
               
    #--------------------move the cursor------------------           
        elif (pressure1>30):
            mouse.move(-read_value_x*ratio, read_value_y*ratio, absolute=False)
    #--------------------left click------------------ 
        if (pressure1>=150):
            mouse.click()
            for i in range(30):
                read_bluetooth=ser.readline()

    try:
        print(read_value_x,read_value_y,read_value_z,pressure1,pressure2,bend)
    except:
        pass
