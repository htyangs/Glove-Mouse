# Glove Mouse and Keyboard [(Homepage)](https://www.htyang.com/projects)
* A glove mouse that can replace your physical mouse and keyboard. <br>
* It is able to control the cursor, left click, right click, scroll up and down, and predict the alphabets from the gesture. <br>
* The glove mouse uses Bluetooth to pass the signals to computer
* Deep learning based alphabet classifier


<p align="center">
<img src="https://user-images.githubusercontent.com/29053630/201852810-1eb19dc9-5de0-49c1-9c75-0247f53e96e1.PNG"> <br>
<p/> 


### Aims
The purpose of this device is to provide all users with a keyboard and mouse that can be used in their most comfortable posture. It solves the problem of poor posture caused by computer users who have long placed their hands and shoulders in line with the table and the keyboard. 

## DEMO

<table>
  <tr>
    <td align="center"> scroll up and down</td>
     <td align="center"> right click and save image </td>
  </tr>
  <tr>
    <td style="text-align: center; vertical-align: middle;"><img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/scroll.gif" width="600"/>
    <td style="text-align: center; vertical-align: middle;"><img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/right click.gif" width="600"/>
  </tr>
 </table>


<table>
  <tr>
    <td align="center"> writing "rib" </td>
     <td align="center"> writing "beef" </td>
  </tr>
  <tr>
    <td style="text-align: center; vertical-align: middle;"><img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/rib.gif" width="600"/>
    <td style="text-align: center; vertical-align: middle;"><img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/beef_.gif" width="600"/>
  </tr>
 </table>
 
## How to use?
Connect the sensor on the sensor list below to the given pin and use arduino.ino to modify some parameter such as pressure sensivity.
#### Arduino.ino
* Collect the data from each sensor and transfer the data to computer using bluetooth.

#### record.py
* Collect the angular accleration of Accelerometer on the index finger

#### train.ipynb
* Train the GRU model to predict the alphabet from angular accleration

#### control.py
* Use the data passing from glove mouse to control the mouse and input the words. 
 
#### machine learning.ipynb
* Tranform the time domain data to frequency domain and apply dimension reduction methods(PCA/LDA) to 25 dimensions, use Support vector machine/Random forest to predict the alphabet. 

### Classifier model
Gate recurrent neural network use the angular velocity of the three-axis as input to predict the alphabets written by users. <br>

<p align="center">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/gru.png" width="600"> <br>
<p/> 

## Sensor list
* FSR400 : Force Sensing Resistor
* BH-37 : bending sensor
* LSM9DS0 : Accelerometer + Gyro + Magnetometer
* HC-05 : Bluetooth to Serial Port Module

<p align="center">
<img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/list.png" width="600"> <br>
<p/> 

## Gestures supported

<p align="center">
    <img src="https://user-images.githubusercontent.com/29053630/201854477-42d05f5d-4d2a-47bd-91d1-32327f0c7eb5.png" width="600">
    <br>
<p/> 

<p align="center">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/control-light.png#gh-light-mode-only" width="600">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/control-dark.png#gh-dark-mode-only" width="600">
    <br>
<p/> 
## Machine learning based classifier (new)
To alleviate the effort of training a GRU model, we also use PCA/LDA + Random forest/Support vector machine to classify the 26 alphabets.
The model reads the frequency domain data converted from Fast Fourier transform.
It achieves high accuracy (97.5% in test dataset) when PCA+SVM is used.

<p align="center">
<img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/table.png" width="600"> <br>
<p/> 
