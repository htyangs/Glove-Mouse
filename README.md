# Glove Mouse and Keyboard
* A glove mouse that can replace your physical mouse and keyboard. <br>
* It is able to control the cursor, left click, right click, scroll up and down, and predict the alphabets from the gesture. <br>
* The glove mouse uses Bluetooth to pass the signals to computer
* Deep learning based alphabet classifier

<p align="center">
<img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/sample.png"> <br>
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


### Classifier model
Gate recurrent neural network use the angular velocity of the three-axis as input to predict the alphabets written by users. <br>

<p align="center">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/gru.png" width="600"> <br>
<p/> 

## Sensor list

<p align="center">
<img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/list.png" width="600"> <br>
<p/> 

## Gestures supported

<p align="center">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/control-light.png#gh-light-mode-only" width="600">
    <img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/control-dark.png#gh-dark-mode-only" width="600">
    <br>
<p/> 

## Machine learning based classifier (new)
To alleviate the effort of training a GRU model, we also use PCA/LDA + Randoom forest/Support vector machine to classify the alphabet
The model read the frequency domain data which converts from Fast Fourier transform.
It achieves high accuracy (97.5% in test dataset) when PCA+SVM is used.

<p align="center">
<img src="https://github.com/alwaysmle/Glove-Mouse/blob/main/figure/table.png" width="600"> <br>
<p/> 
