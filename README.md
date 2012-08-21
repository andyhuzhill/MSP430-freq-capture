# Freq and Voltage Capture
This project is a simple program used to capture frequence and voltage
using MSP430G2553.

## File description

1. main.c main file with all the process functions.
2. lcd12864.c lcd12864.h LCD12864 Serial Port Driver.
3. delay.h  a simple delay defination.

## Usage

These files are managed by Code Composer Studio V5, you can import it 
into your CCS easily. But it will also work in IAR .

## Algorthm

The main function is in main.c file. It Capture 100 period , and calculate    
the frequences. Voltage is calulated after 10 times largest value of ADC result.    
In the mainloop, it will make 100 times AD Covention to find the largest voltage value.

## Copyright

These files are in this hope that it will be useful for you, so they are    
distributed under the LGPL licence. You can feel free to use them in your    
programs.

