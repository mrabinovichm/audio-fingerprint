EESchema Schematic File Version 1
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./LCD16x2.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "11 oct 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 4700 2900
Connection ~ 4700 2800
NoConn ~ 2400 3850
Kmarq B 2400 3850 "Aviso: hay más de un pin conectado aun símbolo de no conexión" F=1
$Comp
L CONN_20X2 P1
U 1 1 4A894A49
P 2800 3700
F 0 "P1" H 2800 4750 60  0000 C C
F 1 "CONN_20X2" V 2800 3700 50  0000 C C
	1    2800 3700
	1    0    0    -1  
$EndComp
Kmarq B 4700 2900 "Warning Pin power_in not driven (Net 15)" F=1
Kmarq B 4700 2800 "Warning Pin power_in not driven (Net 4)" F=1
Text Label 2300 2050 0    60   ~
BL
Wire Wire Line
	8000 3450 8000 2050
Wire Wire Line
	8000 3450 8050 3450
Wire Wire Line
	2400 2600 2400 2750
Wire Wire Line
	2400 2600 4700 2600
Wire Wire Line
	4700 2600 4700 2800
Connection ~ 3200 2400
Connection ~ 3500 2750
Wire Wire Line
	3200 2750 4450 2750
Wire Wire Line
	3700 3000 3700 2950
Wire Wire Line
	3700 2950 3750 2950
Wire Wire Line
	3750 2950 3750 2900
Wire Wire Line
	4200 2900 4200 3000
Wire Wire Line
	4200 2900 4100 2900
Wire Wire Line
	4100 2900 4100 2800
Wire Wire Line
	3200 2750 3200 2400
Wire Wire Line
	3200 2400 8600 2400
Wire Wire Line
	8600 2400 8600 3850
Wire Wire Line
	8600 3850 8000 3850
Wire Wire Line
	8000 3850 8000 3750
Wire Wire Line
	2400 3550 2400 3500
Wire Wire Line
	2400 3500 3350 3500
Wire Wire Line
	3350 3500 3350 3100
Wire Wire Line
	3350 3100 4700 3100
Wire Wire Line
	2400 3750 2400 3700
Wire Wire Line
	2400 3700 3450 3700
Wire Wire Line
	3450 3700 3450 3300
Wire Wire Line
	3450 3300 4700 3300
Wire Wire Line
	2400 4050 1800 4050
Wire Wire Line
	1800 4050 1800 5450
Wire Wire Line
	1800 5450 4150 5450
Wire Wire Line
	4150 5450 4150 4000
Wire Wire Line
	4150 4000 4700 4000
Wire Wire Line
	2400 4250 2000 4250
Wire Wire Line
	2000 4250 2000 5250
Wire Wire Line
	2000 5250 3950 5250
Wire Wire Line
	3950 5250 3950 3800
Wire Wire Line
	3950 3800 4700 3800
Wire Wire Line
	2400 4450 2200 4450
Wire Wire Line
	2200 4450 2200 5050
Wire Wire Line
	2200 5050 3750 5050
Wire Wire Line
	3750 5050 3750 3600
Wire Wire Line
	3750 3600 4700 3600
Wire Wire Line
	4700 3400 3550 3400
Wire Wire Line
	3550 3400 3550 4850
Wire Wire Line
	3550 4850 2400 4850
Wire Wire Line
	2400 4850 2400 4650
Wire Wire Line
	2600 2400 2800 2400
Wire Wire Line
	8050 3650 8050 3750
Wire Wire Line
	8050 3750 8000 3750
Wire Wire Line
	4700 3500 3650 3500
Wire Wire Line
	3650 3500 3650 4950
Wire Wire Line
	3650 4950 2300 4950
Wire Wire Line
	2300 4950 2300 4550
Wire Wire Line
	2300 4550 2400 4550
Wire Wire Line
	4700 3700 3850 3700
Wire Wire Line
	3850 3700 3850 5150
Wire Wire Line
	3850 5150 2100 5150
Wire Wire Line
	2100 5150 2100 4350
Wire Wire Line
	2100 4350 2400 4350
Wire Wire Line
	4700 3900 4050 3900
Wire Wire Line
	4050 3900 4050 5350
Wire Wire Line
	4050 5350 1900 5350
Wire Wire Line
	1900 5350 1900 4150
Wire Wire Line
	1900 4150 2400 4150
Wire Wire Line
	4700 4100 4250 4100
Wire Wire Line
	4250 4100 4250 5550
Wire Wire Line
	4250 5550 1700 5550
Wire Wire Line
	1700 5550 1700 3950
Wire Wire Line
	1700 3950 2400 3950
Wire Wire Line
	4700 3200 3400 3200
Wire Wire Line
	3400 3200 3400 3600
Wire Wire Line
	3400 3600 2400 3600
Wire Wire Line
	2400 3600 2400 3650
Connection ~ 8000 3350
Wire Wire Line
	4700 2800 4600 2800
Wire Wire Line
	4200 3000 4700 3000
Wire Wire Line
	4700 2900 4450 2900
Wire Wire Line
	4450 2900 4450 2750
Wire Wire Line
	2400 2750 2100 2750
Wire Wire Line
	2100 2750 2100 2400
Wire Wire Line
	2400 3450 1750 3450
Wire Wire Line
	1750 3450 1750 2050
Wire Wire Line
	1750 2050 8000 2050
Text Label 4200 2400 0    60   ~
GND
Text Label 3800 2600 0    60   ~
Vcc
Text Label 3500 3300 0    60   ~
E
Text Label 3600 5550 0    60   ~
PB7
Text Label 3400 5450 0    60   ~
PB6
Text Label 3250 5350 0    60   ~
PB5
Text Label 3100 5250 0    60   ~
PB4
Text Label 2950 5150 0    60   ~
PB3
Text Label 2800 5050 0    60   ~
PB2
Text Label 2650 4950 0    60   ~
PB1
Text Label 3450 3200 0    60   ~
R/W
Text Label 3500 3100 0    60   ~
RS
$Comp
L POT RV1
U 1 1 4AD20FA4
P 3500 2900
F 0 "RV1" H 3500 2800 50  0000 C C
F 1 "1k" H 3500 2900 50  0000 C C
	1    3500 2900
	1    0    0    -1  
$EndComp
NoConn ~ 3250 2900
$Comp
L LCD16x2_WH1602D S1
U 1 1 4A8B00AD
P 6500 3450
F 0 "S1" H 5450 4200 60  0000 C C
F 1 "LCD16x2_WH1602D" H 6750 2700 60  0000 C C
	1    6500 3450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4A89501D
P 4350 2800
F 0 "R2" V 4430 2800 50  0000 C C
F 1 "3k3" V 4350 2800 50  0000 C C
	1    4350 2800
	0    1    1    0   
$EndComp
NoConn ~ 2400 3250
NoConn ~ 2400 3350
Text Label 2450 4850 0    60   ~
PB0
NoConn ~ 3200 3250
NoConn ~ 3200 3650
NoConn ~ 3200 3750
NoConn ~ 3200 4650
NoConn ~ 3200 4250
NoConn ~ 3200 4050
NoConn ~ 3200 3950
NoConn ~ 3200 4350
NoConn ~ 3200 4550
NoConn ~ 8050 3550
$Comp
L CONN_3 K1
U 1 1 4A89A0B4
P 8400 3550
F 0 "K1" V 8350 3550 50  0000 C C
F 1 "CONN_3" V 8450 3550 40  0000 C C
	1    8400 3550
	1    0    0    -1  
$EndComp
Text Notes 7500 7550 0    60   ~
Display LCD16x2 para usar con DSP56303
NoConn ~ 3200 4450
NoConn ~ 3200 4150
NoConn ~ 3200 3850
NoConn ~ 2400 3150
NoConn ~ 2400 3050
NoConn ~ 2400 2950
NoConn ~ 2400 2850
NoConn ~ 3200 3550
NoConn ~ 3200 3450
NoConn ~ 3200 3350
NoConn ~ 3200 3150
NoConn ~ 3200 3050
NoConn ~ 3200 2950
NoConn ~ 3200 2850
$Comp
L R R1
U 1 1 4A895018
P 3950 3000
F 0 "R1" V 4030 3000 50  0000 C C
F 1 "470" V 3950 3000 50  0000 C C
	1    3950 3000
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 4A894B0E
P 3000 2400
F 0 "D1" H 3000 2500 50  0000 C C
F 1 "LED" H 3000 2300 50  0000 C C
	1    3000 2400
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4A894AB1
P 2350 2400
F 0 "R3" V 2430 2400 50  0000 C C
F 1 "1k" V 2350 2400 50  0000 C C
	1    2350 2400
	0    1    1    0   
$EndComp
$EndSCHEMATC
