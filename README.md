![releases](https://img.shields.io/github/tag/mohabouje/AcousticLPS.svg)
![issues](https://img.shields.io/github/issues/mohabouje/AcousticLPS.svg)
![license](https://img.shields.io/github/license/mohabouje/AcousticLPS.svg)
![built](https://img.shields.io/badge/built%20with-Qt/C++-6f62ba.svg)

***

Acoustic LPS  - Server
===================

This project it's part of **Acoustic - LPC project**. The project consist in the design, analysis, testing and implementation of an advanced signal processing tool suitable for indoor positioning of portable devices. 

The server node emits different modulated acoustic signals (*M-QPSK modulation*) with different encoding codes (*CDMA-based*) to locate a device indoors.

The clients nodes can identify the current location by estimating the **Time Of Flight (TOF)**  and a **Trilateration Algorithm**.  To accurate the estimation any node integrate a capability to mitigate the effects of *Multipath propagation*.

***This repository include the project to debug/simulate the system for both sides.*** 


----------
**NODES MANIPULATION**

The app allows to create, modify, disable or remove existing nodes easily.  

![enter image description here](https://lh3.googleusercontent.com/-p_TzLYRgPPs/WWU0eB7OTmI/AAAAAAAAA-s/PyAl6fLRubkpDvprqxIdKfyTv2UVSgrNQCLcBGAs/s0/Screenshot_20170711_220829.png "Nodes Manipulation")


----------
**LOCAL POSITIONING SYSTEM**

The app can identify the current location with a previous configuration of the environment and a DSP process.

![enter image description here](https://lh3.googleusercontent.com/-5RzX60y1yM8/WWU1gd0HUXI/AAAAAAAAA_E/8pD0zzJbxHYCKxLIcrwxXj36-Rhe7IXxwCLcBGAs/s0/Screenshot_20170711_223041.png "Identification of the current position.")

You can display the DSP algorithm in real time:

![enter image description here](https://lh3.googleusercontent.com/_7ftAnj9Nghr2YN_cgr0R0YLRDV50nDW55hGST-ceL8d0s5B7tMsrpu9IWufsMXK60xgqwcSj4Sg=s0 "Power Spectral Density in real time.")

Compilation
-------------


The project integrate different dependencies for the Digital Signal Processing (DSP) tools  and for data manipulation. 

 - Lib FFTW, needed for the estimation of the DFT & DCT (Fourier Transforms)
 - Lib Armadillo, it's recommended to use OpenBlas for the Algebra operations.
 - Lib PortAudio, needed for the audio recording process.
 - Lib Sndfile, used to read audio files.
 - **Qt 5.X Framework** it's required.
