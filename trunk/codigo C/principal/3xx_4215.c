/*************************************************************************
**
**  VERSION:            @(#)3xx_4215.c  1.10    02/04/25
**
**  IN PACKAGE:         DSP563xx/6xx fftscope
**
**  COPYRIGHT:          Copyright 1997-2004 Altium BV
**
**  DESCRIPTION:
**
**      Routines for CS4215 codec connected to DSP563xx ESSI0.
**      The codec initialisation routine is the C equivalent
**      of the routines supplied by Motorola.
**
**************************************************************************/

//#include <c56.h>
//#include <reg56303.h>

#include "cs4215.h"
#include "loopback.h"

#ifndef CPUCLK
#define CPUCLK      67000000L   /* Hz */
#endif

#if FSAMPLE >= 48000            /* select appropriate sampling freq.  */
#define FS_VALUE SAMP_RATE_48
#elif FSAMPLE >= 32000
#define FS_VALUE SAMP_RATE_32
#elif FSAMPLE >= 27000
#define FS_VALUE SAMP_RATE_27
#elif FSAMPLE >= 16000
#define FS_VALUE SAMP_RATE_16
#elif FSAMPLE >= 9000
#define FS_VALUE SAMP_RATE_9
#elif FSAMPLE >= 8000
#define FS_VALUE SAMP_RATE_8
#endif

#define CTRL_WD_12  (NO_PREAMP+HI_PASS_FILT+FS_VALUE+STEREO+DATA_16)
#define CTRL_WD_34  (IMMED_3STATE+XTAL1_SELECT+BITS_64+CODEC_MASTER)
#define CTRL_WD_56  0x000000
#define CTRL_WD_78  0x000000

#define TONE_INPUT      MIC_IN_SELECT+(15*MONITOR_ATTN)
#define TONE_OUTPUT     HEADPHONE_EN+LINEOUT_EN+(0*LEFT_ATTN)+(0*RIGHT_ATTN)

#define setvect(n, v)   *((_P unsigned short*)(n*2)) = (0x0d0000+(unsigned short)(v)); \
                        *((_P unsigned short*)(n*2+1)) = 0

_Y _circ CS4215DATA txdata, rxdata;
_Y _circ _fract *txdata_p = txdata.b;
_Y _circ _fract *rxdata_p = rxdata.b;

_fract _circ *ptr_buffer;

/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI receive (A/D converter) interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(IRQ_ESSI0_RCV)
ssi_receive(void)
{
    *rxdata_p++ = RX0;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI receive with exception (A/D converter) interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(IRQ_ESSI0_RCE)
ssi_receive_err(void)
{
    SSISR0.B.ROE = 0;
    *rxdata_p++ = RX0;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI receive last slot interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(IRQ_ESSI0_RCL)
ssi_receive_ls(void)
{
//    rxdata_p = rxdata.b;
	*ptr_buffer++ = rxdata.d.i.audio_left;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI transmit (D/A converter) interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(IRQ_ESSI0_TRM)
ssi_transmit(void)
{
    TX00 = *txdata_p++;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI transmit with exception (D/A converter) interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(IRQ_ESSI0_TRE)
ssi_transmit_err(void)
{
    SSISR0.B.TUE = 0;
    TX00 = *txdata_p++;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI transmit last slot interrupt during initialisation
 *           (transmitted data is not retrieved from the output buffers).
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _internal _reentrant _long_interrupt(IRQ_ESSI0_TRL)
ssi_transmit_ls_init(void)
{
    txdata_p = txdata.b;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI transmit last slot interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
void _near _internal _reentrant _long_interrupt(-1)
ssi_transmit_ls(void)
{
    txdata_p = txdata.b;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Handle SSI receive last slot interrupt.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
static void _near _internal _reentrant _long_interrupt(-1)
ssi_receive_ls_dummy(void)
{   
    rxdata_p = rxdata.b;
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Send input gain settings to codec.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
void ssi_set_gains(void)
{
    int i, gain;

    for(i = 0;  i < IN_MAX;  i++)
    {
#if 0
        gain = chan[i].params.gain * 2 / 3; /* 1.5 dB/step   */
#else
		gain = 0;
#endif
        if(gain <  0)  gain = 0;            /* CS4215 limits */
        if(gain > 15)  gain = 15;
        if(i == IN_LEFT)
            txdata.d.b.lgain = gain;
        else
            txdata.d.b.rgain = gain;
    }
}



#define CRA0_VALUE   0x103800 + ((CPUCLK/(2*2500000)) - 1)
#define CRB0_CVALUE  0xFF313C /* value for control mode */
#define CRB0_DVALUE  0xFF310C /* value for data    mode */
#define PRRC_VALUE   0x000003
#define PCRC_VALUE   0x00003C
#define PDRC_NRESET  0x000001
#define PDRC_DATA    0x000002
#define IPRP_SSIMASK 0x00000C

/*------------------------------------------------------------------------------
 *  PURPOSE: Initialize (interrupt driven) ESSI interface between codec and DSP.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
void ssi_init(void)
{
        int i, j;

    /* First, the SSI port is programmed as master to be able to write    */
    /* to the CS4215's control registers.                                 */
    /* 'Sampling frequency' here is 2 MHz/(4*16) = 39 kHz (immaterial).   */
    /* Switch to control mode and reset the CS4215.                       */

    PCRC   = 0x0000;        /* Turn off SSI port */
    CRA0.I = CRA0_VALUE;    /* (CPUCLK/4)/N = 2MHz SCLK, WL=16 bits, 4W/F */
    CRB0.I = (int)CRB0_CVALUE; /* RIE,TIE,RE,TE, NTWK, SYN, FSR/RSR->bit  */
    PRRC   = PRRC_VALUE;    /* setup pc2, pc3 and pc4 as outputs          */
    PDRC   = 0x0000;        /* D/C~ = 0, RESET~ = 0 ==> reset mode        */
    
    /* Allow for power supply stabilization before codec calibration.     */

    for(i = 0;  i < 1000;  i++)             /* 100 ms total delay:        */
    {
        for(j = 0;  j < (int)(100*CPUCLK/(2*1E6));  j++)     /* 100 us    */
        {
            _nop();
        }
    }    

    txdata.c.i.ctrl_wd_12 = CTRL_WD_12;
    txdata.c.i.ctrl_wd_34 = CTRL_WD_34;
    txdata.c.i.ctrl_wd_56 = CTRL_WD_56;
    txdata.c.i.ctrl_wd_78 = CTRL_WD_78;

    setvect(IRQ_ESSI0_TRL, ssi_transmit_ls_init);
    
    PDRC    = PDRC_NRESET;   /* D/C~ = 0, RESET~ = 1 ==> control mode     */
    IPRP.I |= IPRP_SSIMASK;  /* set SSI interrupt priority level to 3     */

    enable_interrupts();

    PCRC = PCRC_VALUE;           /* Turn on SSI port                      */

    /* The CS4215's control register are now written from the interrupt   */
    /* routine ssi_trm_init() with the control word values above.         */

    while(!SSISR0.B.RFS)  ;      /* wait for synchronization              */
    while( SSISR0.B.RFS)  ;      /* wait for one complete buffer to be    */
    while(!SSISR0.B.RFS)  ;      /* written to the CS4215                 */

    while(rxdata.c.b.clb)  ;    /* wait for received clb to go low        */
                                /*  indicating data has been accepted     */

    txdata.c.b.clb = 1;         /* set clb to finalize transfer           */

    for(i = 0;  i < 4;  i++)    /* wait four transmit cycles              */
    {   while(!SSISR0.B.TFS)  ;
        while( SSISR0.B.TFS)  ;
    }

    /* Now switch the SSI port to slave mode. The CS4215 will drive the   */
    /* SCLK and FS lines from now on. Sampling frequency is determined by */
    /* the clock source of the CS4215 and the divide ratio selected.      */

    PCRC   = 0x0000;            /* Turn off SSI port                      */
    CRA0.I = CRA0_VALUE;        /* (CPUCLK/4)/N = 2MHz SCLK, WL=16, 4W/F  */
    CRB0.I = (int)CRB0_DVALUE;  /* rx,tx & int ena,netwk,syn,sclk==i/p,msb 1st*/
    PDRC   = PDRC_DATA|PDRC_NRESET;/* D/C~ = 1  ==> data mode             */

    txdata.d.i.audio_left     = 0;
    txdata.d.i.audio_right    = 0;
    txdata.d.i.output_setting = TONE_OUTPUT;
    txdata.d.i.input_setting  = TONE_INPUT;
    ssi_set_gains();

    setvect(IRQ_ESSI0_TRL, ssi_transmit_ls);
    
    PCRC = PCRC_VALUE;          /* Turn on SSI port                       */

}


/*------------------------------------------------------------------------------
 *  PURPOSE: Change interrupt handler for receive-last-frame interrupts.
 *  INPUT  : Flag: 1 = run mode, 0 = init mode.
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
void ssi_enable_receive(int flag)
{
    setvect(IRQ_ESSI0_RCL, flag ? ssi_receive_ls : ssi_receive_ls_dummy );
}


/*------------------------------------------------------------------------------
 *  PURPOSE: Toggle an I/O line for timing measurements.
 *  INPUT  : -
 *  OUTPUT : -
 *----------------------------------------------------------------------------*/
void ssi_toggle_indicator(void)
{
    TCSR0.B.TDIR = 1;            /* set to 'output'                           */
    TCSR0.B.TDO ^= 1;            /* toggle TIO0, LED next to audio connector  */
}

/* END OF FILE */
        
