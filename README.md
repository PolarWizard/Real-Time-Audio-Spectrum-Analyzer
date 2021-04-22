# Real Time Audio Spectrum Analyzer

Chosen Class Project for ECE 692 - Embedded Computing Systems

The goal of this project was to develop a device that would show the frequency domain spectrum of a sampled audio signal.

## Basic Operation:

## Schematic:

## Pin Assignments:

PA0 - ADC1

PB6 - I2C1 SCL
 
PB7 - I2C1 SDA

## Personal Accomplishments:

* Successfully built a Audio Spectrum Analyzer
* Everything in this project is bare metal, no libraries or external functions used (fix_fft.c FFT function only exception)
* Successfully configured all peripherals: GPIO, ADC, I2C
* Built a custom driver for Hitachi LCD with i2c module from scratch, can be reused for other projects
* Built a circuit that would amplify audio voltage to a readable ADC value

## Things to Improve Upon

* Build a proper amplifier circuit, Common Collector Amplifier for example
* Create my own FFT algorithm function
