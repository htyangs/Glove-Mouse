# Glove-Mouse and Keyboard
* A glove mouse that can replace your physical mouse and keyboard. <br>
* It is able to control the cursor, left click, right click, scroll up and down, and predict the alphabets from the gesture. <br>
* The glove mouse use the bluetooth to pass the signal to computer
![alt text](http://url/to/img.png)
### Classifier model
Gate recurrent neural network used the angular velocity of the three-axis as input to predict the alphabets written by users. <br>
### Aims
The purpose of this device is to provide all users with a keyboard and mouse that can be used in their most comfortable posture. It solves the problem of poor posture caused by computer users who have long placed their hands and shoulders in line with the table and the keyboard. 

## How to use?

#### record.py
Collect the angular accleration of Accelerometer on the index finger

#### train.ipynb
Train the GRU model to predict the alphabet from angular accleration

#### control.py
Use the data passing from glove mouse to control the mouse and input the words. 

#### Arduino.ino
Collect the data from each sensor and transfer the data to computer using bluetooth.