#include "cs4215.h"
#include "loopback.h"
#include "lcd16x2.h"
#include "zcr_func.h"
#include "int.h"

#define LARGO 		32
#define NRO_HUELLAS 3


/* ***************** Mensajes a desplegar y sus largos en display ********************** */
	 _Y unsigned char dsp_afp[]   = "DSP 2009        AUDIOFINGERPRINT";
	 _Y unsigned char sw_2[]      = "Presione SW2    para  comenzar  ";
	 _Y unsigned char busq[]      = "Buscando        huella...       ";
     _Y unsigned char h_enc[]     = "Huella          encontrada      ";
	 _Y unsigned char h_no_enc[]  = "Huella          no encontrada   ";
 	 _Y unsigned char error[]     = "Error                           ";
 
 	 _Y unsigned char enya[]      = "Enya:           Only Time       ";
	 _Y unsigned char oasis[]     = "Oasis:          Headshrinker    ";
	 _Y unsigned char van_halen[] = "Van Halen:      Eruption        ";

	 _Y unsigned char *dply[NRO_HUELLAS] = {enya, oasis, van_halen};
/* ********************************************************************************** */

/* ********************** Base de datos de huellas conocidas ************************ */
  	 _Y float h_enya[q]      = {200.000000,166.666667,166.666667,166.666667,166.666667,166.666667,166.666667,233.333333,233.333333,266.666667,233.333333,500.000000,833.333333,866.666667,700.000000,366.666667,300.000000,300.000000,266.666667,333.333333,333.333333,433.333333,433.333333,366.666667,300.000000,300.000000,233.333333,233.333333,266.666667,300.000000,400.000000,433.333333,433.333333,300.000000,300.000000,300.000000,300.000000,166.666667,300.000000,366.666667,500.000000,366.666667,400.000000,300.000000,433.333333,433.333333,666.666667,600.000000,533.333333,366.666667,333.333333,500.000000,533.333333,533.333333,400.000000,400.000000,400.000000,400.000000,433.333333,433.333333,433.333333,333.333333,333.333333,300.000000,333.333333,366.666667,366.666667,333.333333,300.000000,400.000000,400.000000,600.000000,733.333333,733.333333,566.666667,400.000000,466.666667,466.666667,466.666667,433.333333,400.000000,333.333333,333.333333,333.333333,366.666667,333.333333,366.666667,333.333333,333.333333,333.333333,333.333333,366.666667,333.333333,366.666667,333.333333,333.333333,333.333333,333.333333,433.333333,400.000000,433.333333,466.666667,566.666667,1066.666667,1700.000000,1666.666667,1600.000000,933.333333,1133.333333,666.666667,866.666667,833.333333,966.666667,733.333333,700.000000,866.666667,800.000000,1300.000000,1033.333333,1000.000000,500.000000,433.333333,600.000000,466.666667,500.000000,466.666667,366.666667,433.333333,300.000000,333.333333,233.333333,266.666667,266.666667,266.666667,266.666667,233.333333,333.333333,300.000000,600.000000,666.666667,666.666667,800.000000,1166.666667,1900.000000,1700.000000,1366.666667,733.333333,600.000000,466.666667,533.333333,500.000000,466.666667,566.666667,600.000000,833.333333,566.666667,566.666667,333.333333,433.333333,400.000000,533.333333,500.000000,766.666667,700.000000,766.666667,766.666667,866.666667,1300.000000,1100.000000,1166.666667,1166.666667,1133.333333,1066.666667,1000.000000,1033.333333,1066.666667,1033.333333,933.333333,1133.333333,733.333333,1066.666667,833.333333,1066.666667,1333.333333,1166.666667,1700.000000,1433.333333,2166.666667,1533.333333,1600.000000,1100.000000,1233.333333,1366.666667,1200.000000,1033.333333,600.000000,900.000000,966.666667,1366.666667,1133.333333,1266.666667,966.666667,866.666667,733.333333,533.333333,933.333333,1100.000000,1366.666667,1400.000000,1600.000000,1666.666667,1333.333333,1066.666667,1066.666667,1266.666667,1400.000000,1466.666667,1433.333333,1400.000000,1433.333333,1666.666667,1500.000000,1366.666667,966.666667,966.666667,900.000000,766.666667,633.333333,466.666667,466.666667,400.000000,333.333333,366.666667,333.333333,366.666667,333.333333,366.666667,333.333333,333.333333,333.333333,400.000000,466.666667,866.666667,866.666667,833.333333,566.666667,966.666667,1400.000000,1833.333333,2033.333333,2833.333333,3533.333333,3866.666667,3666.666667,3266.666667,3266.666667,3066.666667,3533.333333,4200.000000,4966.666667,4933.333333,4566.666667,4533.333333,4866.666667,5433.333333,5400.000000,5833.333333,5633.333333,5733.333333,5900.000000,5933.333333,5533.333333,4966.666667,5233.333333,5300.000000,4400.000000,3400.000000,3000.000000,2400.000000,2100.000000,1533.333333,2166.666667,1833.333333,1700.000000,933.333333,733.333333,600.000000,500.000000,733.333333,666.666667,1166.666667,966.666667,1333.333333,1100.000000,1133.333333,733.333333,533.333333,566.666667,633.333333,800.000000,633.333333,866.666667,833.333333,966.666667,866.666667,666.666667,533.333333,666.666667,933.333333,1200.000000,833.333333,733.333333,566.666667,666.666667,666.666667,600.000000,600.000000,566.666667,666.666667,833.333333,866.666667,700.000000,600.000000,533.333333,600.000000,466.666667,566.666667,600.000000,633.333333,733.333333,800.000000,933.333333,933.333333,1033.333333,933.333333,700.000000,666.666667,600.000000,633.333333,533.333333,600.000000,566.666667,566.666667,500.000000,600.000000,633.333333,833.333333,966.666667,833.333333,933.333333,800.000000,866.666667,766.666667,633.333333,666.666667,633.333333,866.666667,766.666667,966.666667,800.000000,933.333333,833.333333,900.000000,800.000000,766.666667,766.666667,900.000000,866.666667,866.666667,966.666667,1033.333333,1166.666667,1333.333333,1133.333333,1066.666667,766.666667,966.666667,1066.666667,1066.666667,966.666667,833.333333,900.000000,1133.333333,1033.333333,866.666667,566.666667,566.666667,533.333333,600.000000,666.666667,800.000000,933.333333,866.666667,900.000000,800.000000,1066.666667,1300.000000,1133.333333,1033.333333,633.333333,666.666667,566.666667,500.000000,466.666667,566.666667,533.333333,500.000000,233.333333,766.666667,766.666667,833.333333,366.666667,333.333333,300.000000,233.333333,333.333333,300.000000,366.666667,400.000000,366.666667,500.000000,400.000000,533.333333,433.333333,466.666667,433.333333,433.333333,433.333333,433.333333,433.333333,500.000000,500.000000,433.333333,366.666667,466.666667,500.000000,433.333333,266.666667,400.000000,500.000000,700.000000,633.333333,533.333333,533.333333,800.000000,1133.333333,1133.333333,900.000000,833.333333,766.666667,800.000000,666.666667,666.666667,766.666667,933.333333,1166.666667,1166.666667,1400.000000,1333.333333,1333.333333,966.666667,1100.000000,1000.000000,1233.333333,1066.666667,1100.000000,800.000000,566.666667,466.666667,500.000000,733.333333,1000.000000,900.000000,766.666667,533.333333,466.666667,500.000000,433.333333,466.666667,666.666667,666.666667,666.666667,366.666667,333.333333,300.000000,333.333333,300.000000,733.333333,733.333333,733.333333,533.333333,466.666667,633.333333,600.000000,666.666667,766.666667,633.333333,733.333333,466.666667,466.666667,733.333333,933.333333,1133.333333,1066.666667,900.000000,1133.333333,900.000000,1300.000000,866.666667,800.000000,400.000000,733.333333,800.000000,833.333333,600.000000,600.000000,666.666667,700.000000,733.333333,900.000000,1000.000000,1100.000000,1000.000000,1000.000000,866.666667,1033.333333,1333.333333,1533.333333,1166.666667,666.666667,600.000000,600.000000,666.666667,466.666667,500.000000,400.000000,666.666667,733.333333,800.000000,466.666667,466.666667,700.000000,700.000000,833.333333,466.666667,400.000000,400.000000,533.333333,633.333333,466.666667,366.666667,400.000000,266.666667,400.000000,333.333333,400.000000,366.666667,400.000000,466.666667,533.333333,633.333333,666.666667,666.666667,700.000000,933.333333,866.666667,700.000000,433.333333,666.666667,800.000000,800.000000,466.666667,433.333333,400.000000,433.333333,500.000000,766.666667,733.333333,933.333333,1033.333333,1100.000000,866.666667,600.000000,666.666667,733.333333,733.333333,733.333333,633.333333,633.333333,633.333333,666.666667,566.666667,666.666667,633.333333,666.666667,466.666667,500.000000};
	 _Y float h_oasis[q]     = {2266.666667,2300.000000,2066.666667,1633.333333,1633.333333,1500.000000,1400.000000,1600.000000,1800.000000,1533.333333,1133.333333,1033.333333,1266.666667,1200.000000,900.000000,1133.333333,1500.000000,2000.000000,1633.333333,1233.333333,1166.666667,1300.000000,1800.000000,1333.333333,1366.666667,1233.333333,1366.666667,1400.000000,1233.333333,1166.666667,1200.000000,1266.666667,1500.000000,1300.000000,1300.000000,1033.333333,1133.333333,766.666667,733.333333,866.666667,1266.666667,1300.000000,1100.000000,1033.333333,1200.000000,1600.000000,1733.333333,1633.333333,1233.333333,1166.666667,1233.333333,1500.000000,1466.666667,1600.000000,1200.000000,1200.000000,966.666667,1333.333333,1166.666667,1266.666667,1033.333333,1366.666667,1600.000000,1466.666667,1066.666667,633.333333,1066.666667,1466.666667,1666.666667,1100.000000,700.000000,533.333333,1000.000000,1066.666667,1166.666667,766.666667,766.666667,1233.333333,1633.333333,1933.333333,1666.666667,1366.666667,1166.666667,1366.666667,1700.000000,1866.666667,1600.000000,1300.000000,1300.000000,1066.666667,1266.666667,1133.333333,1233.333333,1300.000000,1333.333333,1266.666667,1066.666667,766.666667,900.000000,1066.666667,1400.000000,1700.000000,1800.000000,1733.333333,1700.000000,1633.333333,1833.333333,1733.333333,1533.333333,1333.333333,1400.000000,1566.666667,1366.666667,1233.333333,1400.000000,1733.333333,1700.000000,1266.666667,1066.666667,966.666667,1166.666667,1533.333333,1566.666667,1333.333333,800.000000,966.666667,1100.000000,1400.000000,1233.333333,1333.333333,1400.000000,1533.333333,1366.666667,1466.666667,1666.666667,1933.333333,1833.333333,1800.000000,1933.333333,1733.333333,1666.666667,1300.000000,1333.333333,1233.333333,1466.666667,1666.666667,1733.333333,1833.333333,1766.666667,1933.333333,1800.000000,1700.000000,1800.000000,1833.333333,2133.333333,2100.000000,2166.666667,2100.000000,1866.666667,1533.333333,1366.666667,1533.333333,1866.666667,2066.666667,2200.000000,2200.000000,2200.000000,1933.333333,2166.666667,2233.333333,2233.333333,1766.666667,1566.666667,1666.666667,2133.333333,2500.000000,2566.666667,2400.000000,2200.000000,2266.666667,2333.333333,2433.333333,2466.666667,2433.333333,2566.666667,2166.666667,2566.666667,2100.000000,2433.333333,1933.333333,2300.000000,2400.000000,2500.000000,2666.666667,2033.333333,1766.666667,1533.333333,1566.666667,1966.666667,1766.666667,2433.333333,2166.666667,2033.333333,2033.333333,1833.333333,2233.333333,1766.666667,1766.666667,1600.000000,1466.666667,1233.333333,1033.333333,1300.000000,1733.333333,2200.000000,2066.666667,1766.666667,1300.000000,1100.000000,1366.666667,1600.000000,1833.333333,1933.333333,2300.000000,2566.666667,2400.000000,2133.333333,1700.000000,1966.666667,1866.666667,1933.333333,2100.000000,2066.666667,2466.666667,2366.666667,2466.666667,2200.000000,1933.333333,1900.000000,1966.666667,2133.333333,2266.666667,2033.333333,1966.666667,1500.000000,1633.333333,1666.666667,1833.333333,2066.666667,2200.000000,2400.000000,2233.333333,1933.333333,2166.666667,2133.333333,2366.666667,2066.666667,2100.000000,1900.000000,1833.333333,1900.000000,2033.333333,1700.000000,1633.333333,1333.333333,1700.000000,1600.000000,1700.000000,1633.333333,1466.666667,1666.666667,1400.000000,1766.666667,1700.000000,1566.666667,1433.333333,1266.666667,1733.333333,1666.666667,1533.333333,1600.000000,1500.000000,1700.000000,1500.000000,1433.333333,1500.000000,1300.000000,1800.000000,1733.333333,1933.333333,1666.666667,1466.666667,1400.000000,1200.000000,1500.000000,1633.333333,1700.000000,1800.000000,1533.333333,1633.333333,1566.666667,1633.333333,1966.666667,1633.333333,1866.666667,1666.666667,1900.000000,1933.333333,1533.333333,1400.000000,1300.000000,1400.000000,1600.000000,1300.000000,1500.000000,1600.000000,2000.000000,1933.333333,1700.000000,1166.666667,1066.666667,1033.333333,1600.000000,1500.000000,1700.000000,1466.666667,2400.000000,2366.666667,2333.333333,2000.000000,1900.000000,1900.000000,2000.000000,1900.000000,1933.333333,1600.000000,1966.666667,2166.666667,2000.000000,2133.333333,1800.000000,1733.333333,1433.333333,1433.333333,1666.666667,1700.000000,1800.000000,1766.666667,1300.000000,1333.333333,1300.000000,1833.333333,1966.666667,2333.333333,2266.666667,2366.666667,2500.000000,2900.000000,3033.333333,3200.000000,3166.666667,2800.000000,2533.333333,2066.666667,2300.000000,2033.333333,2633.333333,2566.666667,2566.666667,2233.333333,2166.666667,2200.000000,2233.333333,2366.666667,2733.333333,2700.000000,2766.666667,2633.333333,2733.333333,2433.333333,1833.333333,1200.000000,1066.666667,1066.666667,1566.666667,1566.666667,1433.333333,1233.333333,1533.333333,1833.333333,1600.000000,1466.666667,1400.000000,1500.000000,1500.000000,1666.666667,2100.000000,1900.000000,2033.333333,1533.333333,1833.333333,1633.333333,1700.000000,1900.000000,1933.333333,2233.333333,2300.000000,2200.000000,2100.000000,1900.000000,1933.333333,2000.000000,1833.333333,1900.000000,1766.666667,2000.000000,1833.333333,2100.000000,2066.666667,2166.666667,2200.000000,2000.000000,2100.000000,1933.333333,2266.666667,2833.333333,2666.666667,2866.666667,2533.333333,2533.333333,2133.333333,1866.666667,2366.666667,2233.333333,2200.000000,1666.666667,1700.000000,1666.666667,1700.000000,1633.333333,1666.666667,1600.000000,1566.666667,1366.666667,1500.000000,1533.333333,1600.000000,1466.666667,1233.333333,1400.000000,1266.666667,1766.666667,2000.000000,2433.333333,2333.333333,2033.333333,1933.333333,1833.333333,1900.000000,1833.333333,1700.000000,1700.000000,1733.333333,1866.666667,1933.333333,1833.333333,1866.666667,1600.000000,1566.666667,1566.666667,1566.666667,1633.333333,1600.000000,1733.333333,1633.333333,1366.666667,1433.333333,1600.000000,1800.000000,1766.666667,1500.000000,1700.000000,1566.666667,1666.666667,1700.000000,1533.333333,1500.000000,1366.666667,1800.000000,2200.000000,2600.000000,2333.333333,2233.333333,2466.666667,2766.666667,3066.666667,2933.333333,3000.000000,3166.666667,2700.000000,2400.000000,1933.333333,2200.000000,2833.333333,3166.666667,3266.666667,2933.333333,2666.666667,2566.666667,2466.666667,2400.000000,2200.000000,2033.333333,2300.000000,2433.333333,2666.666667,2200.000000,2033.333333,1633.333333,1833.333333,2000.000000,2600.000000,2666.666667,2766.666667,3033.333333,2766.666667,2833.333333,2333.333333,2366.666667,2366.666667,2300.000000,2500.000000,1833.333333,1766.666667,1600.000000,1833.333333,1900.000000,1733.333333,1700.000000,1500.000000,1600.000000,1533.333333,1466.666667,1600.000000,1966.666667,2266.666667,2200.000000,1833.333333,1900.000000,1700.000000,1966.666667,1800.000000,1933.333333,1433.333333,1300.000000,1366.666667,1766.666667,1700.000000,1966.666667,1966.666667,1766.666667,1166.666667,766.666667,1166.666667,1333.333333,1533.333333,1400.000000,1300.000000,1166.666667,1100.000000,1300.000000,1500.000000,1500.000000,1433.333333,1200.000000,1200.000000,1133.333333,1166.666667,1333.333333,1266.666667,1666.666667,1700.000000,1700.000000,1566.666667,1433.333333,1400.000000,1533.333333,1400.000000,1933.333333,1633.333333,1800.000000,1500.000000,2000.000000,1733.333333,1533.333333,1133.333333,1333.333333};
	 _Y float h_van_halen[q] = {3000.000000,3166.666667,3000.000000,2933.333333,2700.000000,2733.333333,2766.666667,2933.333333,2933.333333,2833.333333,2800.000000,2833.333333,2833.333333,2800.000000,2666.666667,2633.333333,2733.333333,2966.666667,3066.666667,3133.333333,3000.000000,2900.000000,2600.000000,2633.333333,2733.333333,3000.000000,2933.333333,2800.000000,2866.666667,3066.666667,3533.333333,3500.000000,3500.000000,3100.000000,3033.333333,3033.333333,3100.000000,3100.000000,3000.000000,2633.333333,2566.666667,2733.333333,3033.333333,3066.666667,2633.333333,2633.333333,2366.666667,2433.333333,2233.333333,2433.333333,2466.666667,2566.666667,2566.666667,2633.333333,2600.000000,2500.000000,2733.333333,2866.666667,3066.666667,2733.333333,2400.000000,2166.666667,2466.666667,2866.666667,2933.333333,2700.000000,2366.666667,2333.333333,2266.666667,2400.000000,2300.000000,2366.666667,2466.666667,2700.000000,2700.000000,2566.666667,2566.666667,2800.000000,2900.000000,3033.333333,2700.000000,2866.666667,2833.333333,3333.333333,3233.333333,3033.333333,2700.000000,2733.333333,2766.666667,2833.333333,2833.333333,3000.000000,3000.000000,3133.333333,2733.333333,2533.333333,2233.333333,2333.333333,2466.666667,2400.000000,2666.666667,2966.666667,3200.000000,3233.333333,2800.000000,2733.333333,2800.000000,3133.333333,3166.666667,3200.000000,3033.333333,2866.666667,2566.666667,2500.000000,2600.000000,2733.333333,2900.000000,2800.000000,2466.666667,2100.000000,2000.000000,2033.333333,2133.333333,2133.333333,2066.666667,1933.333333,1800.000000,1933.333333,1966.666667,2133.333333,2100.000000,2366.666667,2466.666667,2533.333333,2633.333333,2833.333333,3000.000000,2866.666667,2666.666667,2600.000000,2400.000000,2333.333333,2366.666667,2533.333333,2600.000000,2566.666667,2566.666667,2600.000000,2500.000000,2533.333333,2700.000000,2533.333333,2633.333333,2366.666667,2466.666667,2266.666667,2133.333333,2200.000000,2066.666667,2200.000000,2333.333333,2333.333333,2200.000000,1966.666667,2066.666667,2266.666667,2433.333333,2700.000000,2600.000000,2833.333333,2933.333333,2933.333333,2766.666667,2433.333333,2466.666667,2366.666667,2333.333333,2266.666667,2400.000000,2700.000000,2666.666667,2600.000000,2533.333333,2466.666667,2333.333333,2166.666667,2600.000000,2966.666667,2666.666667,2633.333333,2666.666667,3166.666667,2966.666667,2633.333333,2166.666667,2233.333333,2133.333333,2300.000000,2100.000000,1900.000000,2133.333333,2533.333333,3133.333333,3000.000000,2900.000000,2733.333333,2933.333333,3066.666667,3233.333333,3133.333333,2966.666667,2800.000000,2966.666667,2600.000000,2466.666667,2533.333333,2766.666667,2866.666667,2733.333333,2966.666667,3133.333333,2866.666667,2566.666667,2566.666667,2900.000000,3200.000000,2933.333333,2700.000000,2600.000000,2900.000000,3166.666667,3133.333333,2766.666667,2566.666667,2866.666667,2966.666667,2933.333333,2666.666667,2733.333333,2733.333333,2700.000000,2700.000000,2766.666667,2733.333333,2733.333333,2700.000000,2800.000000,3033.333333,2966.666667,3100.000000,2933.333333,2933.333333,3033.333333,2833.333333,2866.666667,2733.333333,2900.000000,3100.000000,2900.000000,2733.333333,2433.333333,2300.000000,2566.666667,2566.666667,2866.666667,2700.000000,2833.333333,2633.333333,2833.333333,2866.666667,2766.666667,2400.000000,2100.000000,2133.333333,2100.000000,2133.333333,2033.333333,2066.666667,2033.333333,2066.666667,2266.666667,2733.333333,2733.333333,2700.000000,2466.666667,2800.000000,2766.666667,2766.666667,2433.333333,2300.000000,2400.000000,2266.666667,2233.333333,1900.000000,2200.000000,2500.000000,2833.333333,2933.333333,2833.333333,2800.000000,2733.333333,2733.333333,2633.333333,2733.333333,2766.666667,2666.666667,2433.333333,2466.666667,2533.333333,2833.333333,3000.000000,3300.000000,3366.666667,3300.000000,2966.666667,2733.333333,2466.666667,2733.333333,2566.666667,2600.000000,2400.000000,2466.666667,2400.000000,2300.000000,2500.000000,2733.333333,2800.000000,2733.333333,2800.000000,2766.666667,2733.333333,2800.000000,3100.000000,3300.000000,3233.333333,3066.666667,3033.333333,3166.666667,3300.000000,3233.333333,3200.000000,3066.666667,2900.000000,2466.666667,2466.666667,2233.333333,2166.666667,2100.000000,2333.333333,2433.333333,2000.000000,1700.000000,1733.333333,1966.666667,2233.333333,2133.333333,2300.000000,2300.000000,2200.000000,2133.333333,1966.666667,2266.666667,2333.333333,2766.666667,2933.333333,2866.666667,2733.333333,2466.666667,2733.333333,2900.000000,3133.333333,3000.000000,2700.000000,2466.666667,2366.666667,2366.666667,2566.666667,2700.000000,2866.666667,2766.666667,2666.666667,2500.000000,2633.333333,2733.333333,2766.666667,2700.000000,2833.333333,3233.333333,3433.333333,3600.000000,3466.666667,3200.000000,3000.000000,2800.000000,3133.333333,3133.333333,3233.333333,2966.666667,2933.333333,2900.000000,2900.000000,2733.333333,2533.333333,2666.666667,2900.000000,2766.666667,2600.000000,2533.333333,2766.666667,2500.000000,2400.000000,2533.333333,2800.000000,3033.333333,2800.000000,2933.333333,2766.666667,2900.000000,2700.000000,2666.666667,2600.000000,2766.666667,2833.333333,2933.333333,2900.000000,3033.333333,3100.000000,3100.000000,2933.333333,2833.333333,3033.333333,3133.333333,3333.333333,3433.333333,3600.000000,3633.333333,3333.333333,3200.000000,3366.666667,3666.666667,3800.000000,3666.666667,3566.666667,3633.333333,3600.000000,3400.000000,3266.666667,3100.000000,2966.666667,2733.333333,2733.333333,3100.000000,3066.666667,2833.333333,2666.666667,2433.333333,2666.666667,2433.333333,2666.666667,2433.333333,2300.000000,2233.333333,2166.666667,2433.333333,2633.333333,3033.333333,3300.000000,3400.000000,3566.666667,3466.666667,3600.000000,3466.666667,3533.333333,3266.666667,3166.666667,2900.000000,2866.666667,2900.000000,3000.000000,3000.000000,3100.000000,2966.666667,2866.666667,2633.333333,2700.000000,2666.666667,2733.333333,2900.000000,2833.333333,2733.333333,2400.000000,2300.000000,2166.666667,2233.333333,2333.333333,2600.000000,2700.000000,2500.000000,2333.333333,2300.000000,2933.333333,3000.000000,2933.333333,2600.000000,2533.333333,2400.000000,2266.666667,2333.333333,2266.666667,2433.333333,2266.666667,2533.333333,2400.000000,2633.333333,2466.666667,2533.333333,2633.333333,2933.333333,3033.333333,2800.000000,2700.000000,2533.333333,2500.000000,2333.333333,2466.666667,2500.000000,2566.666667,2600.000000,2666.666667,2800.000000,2800.000000,2733.333333,2633.333333,2533.333333,2633.333333,2466.666667,2666.666667,2466.666667,2866.666667,2600.000000,2633.333333,2333.333333,2333.333333,2400.000000,2633.333333,2800.000000,2866.666667,2800.000000,2866.666667,2733.333333,2466.666667,2366.666667,2600.000000,2733.333333,2800.000000,2766.666667,2700.000000,2533.333333,2333.333333,2466.666667,2600.000000,2766.666667,2866.666667,3033.333333,2966.666667,2866.666667,2700.000000,2733.333333,2866.666667,2866.666667,2633.333333,2266.666667,2000.000000,2000.000000,2133.333333,2133.333333,2133.333333,2033.333333,2033.333333,2300.000000,2333.333333,2666.666667,2600.000000,2700.000000,2533.333333,2500.000000,2633.333333,2833.333333,3000.000000,3166.666667,3000.000000,3000.000000,2633.333333,2466.666667,2233.333333,2133.333333,2400.000000};

	 _Y float *h_conocidas[NRO_HUELLAS] = {h_enya, h_oasis, h_van_halen};
/* ********************************************************************************** */

/* ********** Buffers y punteros para los datos de entrada desde el codec *********** */
	_fract _circ buffer_in0[S+1];
	_fract _circ buffer_in1[S+1];/*+1 para cumplir el while del llenado de los buffers*/
	_fract _circ buffer_in2[S+1];

	_fract _circ buffer_aux[2*S];	   /*buffer auxiliar para no sobreescribir memoria*/
																 
	extern _fract _circ *ptr_buffer;
	_fract *ptr_fin;
	_fract *ptr_ini;
	
/* ********************************************************************************** */

/* ***************** Buffers y punteros para el manejo de huellas ******************* */
	float huella[q/3];		   	  			   /*muestras de frecuencias fundamentales*/
	int ceros_tramo[T];		   					 /*cantidad de ceros en c/tramo de 5ms*/

	extern float *ptr_huella;
	extern float *ptr_h_fin;
/* ********************************************************************************** */

short h_lista ; 						/*indica que la huella generada est� lista*/
extern short sw2;
	
int main(void)
{
	short resultado;							   /*0 = no encontrada, 1 = encontrada*/
	short uso_buff;									  /*indica numero de buffer en uso*/

			
/* ************** Inicializa puerto, display, switch2, interrupciones  ************** */
	init_gpio();						   /*inicializa puerto donde se conecta el lcd*/	
	init_lcd();								  /*inicializa el display, ver HD44780.pdf*/
	init_sw();										   /*inicializa switch 2 y led D12*/
  	ssi_init(); 				  									/*inicializa codec*/

    
	/*mensaje de bienvenida*/
	disable_interrupts();
	dato_lcd(dsp_afp, LARGO);
	delay(5000);														  /*esperar 0.5s*/
	write_lcd(CLEAR, CTRL_WR);	    							  /*comando Clear Dply*/
	delay(100);  				    									/*esperar 10ms*/
	
	sw2 = 0;
	ptr_buffer = buffer_aux;			           
	enable_interrupts();
	dato_lcd(sw_2, LARGO);
	delay(1000);
	while(!sw2);									   /*sw2=1 arranca la busqueda*/	while(!sw2);									   /*sw2=1 arranca la busqueda*/

	for(;;) 
	{
		resultado = -1;
		uso_buff = 0;
		h_lista = 0;
		ptr_huella = huella;				 /*inicio el puntero al arreglo de frec f0*/
		ptr_h_fin = ptr_huella + q/3;
		ptr_buffer = buffer_aux;			           

//		dato_lcd(sw_2, LARGO);
//		delay(1000);
//		enable_interrupts();
//		while(!sw2);									   /*sw2=1 arranca la busqueda*/
	 
		disable_interrupts();
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/
		dato_lcd(busq, LARGO);
		enable_interrupts();

/* *************************************************************************************
Calculo los ceros en 2 tramos de 5ms y luego el tercero dentro del loop
la funcion fundamentales() calcula la frecuencia fundamental de 3 tramos de
5ms c/u y la guarda en el arreglo huellas[]
************************************************************************************* */

		ptr_buffer = buffer_in0;						  /*inicializo puntero buffer0*/
		ptr_fin = buffer_in0 + (S-1); 
		ptr_ini = buffer_in0;
		
		while(ptr_buffer < ptr_fin);				   /*espero hasta llenar el buffer*/
		ptr_buffer = buffer_in1;						  /*inicializo puntero buffer1*/
		ptr_fin = buffer_in1 + (S-1); 
		ceros_tramo[1] = zcr(ptr_ini, S);						 /*ceros en un tramo 0*/
		ptr_ini = buffer_in1;
		while(ptr_buffer < ptr_fin);				   /*espero hasta llenar el buffer*/
		ptr_buffer = buffer_in2;						  /*inicializo puntero buffer1*/
		ptr_fin = buffer_in2 + (S-1); 
		ceros_tramo[2] = zcr(ptr_ini, S);						 /*ceros en un tramo 1*/

			
		while(!h_lista)
		{
			while(ptr_buffer < ptr_fin);			   /*espero hasta llenar el buffer*/
			switch(uso_buff)
			{
				case 0: ptr_buffer = buffer_in0;		  /*inicializo puntero buffer0*/
						ptr_ini = buffer_in2;
						break;
				case 1: ptr_buffer = buffer_in1;		  /*inicializo puntero buffer1*/
						ptr_ini = buffer_in0;
						break;
				case 2: ptr_buffer = buffer_in2;		  /*inicializo puntero buffer2*/
						ptr_ini = buffer_in1;
						break;
				default: break;
			}							  
			ptr_fin = ptr_buffer + (S-1); /*no puedo sumar S porque ptr_buffer es circ*/
			ceros_tramo[uso_buff] = zcr(ptr_ini, S);	    	   /*ceros en un tramo*/
			h_lista = fundamentales(ceros_tramo);	  /*indica si la huella esta lista*/
			uso_buff++;
			uso_buff = uso_buff % 3;			
		}
		disable_interrupts();
		resultado = busqueda(huella, (float **)h_conocidas, NRO_HUELLAS);
	
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);
		if(resultado != -1)
		{
			dato_lcd(h_enc, LARGO);                                                   
 			delay(2000);                                                              
 			write_lcd(CLEAR, CTRL_WR);	    			  		  /*comando Clear Dply*/        
 			delay(100);  				    					        /*esperar 10ms*/        
 			dato_lcd(dply[resultado], LARGO);
		}
		else
			dato_lcd(h_no_enc, LARGO);
		delay(2000);
		write_lcd(CLEAR, CTRL_WR);	    						  /*comando Clear Dply*/
		delay(100);  				    								/*esperar 10ms*/
		//TCSR0.B.TDO = OFF;							/*led D12 OFF, termina la busqueda*/
	} /*Fin loop ppal*/ 
} /*Fin main*/