## Description
The main prupose of this project is to read the consumption of an element (Current and voltage)
to calculate the consumption.
To measure the current we are going to use a ACS712 sensor. This sensor works on the principle of hall efect.
They support currents up to 5A,20A,30A depending on the model, on this particular case we are using a 20A sensor.
To read the voltage of the element we use the simple voltage divider.
Using 2 resistor in serial, we plug one side to ground, the other side is conected to the point we want to measure and 
the middle point is connected to the A1 pin of the Atmega 328

We cant do the video of the project beceause we have a problem in our code and are not able to receive the data on the PC via UART
(Problem due to error on the conversion from float to String)

### Schematic

      *--->The point we want to measure-->Vin
	  |
	 ┌┴┐                        
	 | |R1                      
     └┬┘  
	  |
	  |---->Middle point connected to A1 Pin on the Atema328
     ┌┴┐                        
	 | |R2                      
     └┬┘ 
      |
	  |
	  |
	  *-----> GND
	  
	The value of the resistors are given by this equation 
	Vout=(R2/(R1+R2))*Vin
	
	  
	  
	The ACS Sensor simply use 3 wires, 1 for VCC, 1 for GND, and the last one are for the data, connected to the A0 pin.	
	  
	
	  
	  

### UART protocol
For the UART comunication we use the "uart.h" lib, we configure the UART with 8 bit data, no parity, and 1 Stop bit


### ADC Channel selection
To select the channel for the ADC, we created a simple function wich depending on a variable, call another function
which change the configuration of the ADMUX register to change the pin

