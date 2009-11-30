/*************************************************************************
**
**  VERSION:            @(#)cs4215.h    1.6     02/04/25
**
**  IN PACKAGE:         DSP563xx/6xx fftscope
**
**  COPYRIGHT:          Copyright 1997-2004 Altium BV
**
**  DESCRIPTION:        Defines for CS4215 codec.
**
**************************************************************************/

#ifndef _CS4215_H
#define _CS4215_H

typedef union
{   union
    {   struct
        {   int             : 8; /* CTRL_WD_12 in most significant 16 bits */
            unsigned df     : 2;
            int      st     : 1;
            unsigned dfr    : 3;
            int             : 1;
            int  hpf        : 1;    
            int             : 2;
            int  clb        : 1;
            int  olb        : 1;
            int  mlb        : 1;
            int             : 3; 

            int             : 8; /* CTRL_WD_34 in most significant 16 bits */
            int  dad        : 1;
            int      enl    : 1;
            unsigned test   : 6;
            int  xen        : 1;
            int  xclk       : 1;
            unsigned bsel   : 2;
            unsigned mck    : 3;
            int  its        : 1;

            int             : 8; /* CTRL_WD_56 in most significant 16 bits */
            int             : 8;
            int             : 6;
            int      pio0   : 1;
            int      pio1   : 1;

            int             : 8; /* CTRL_WD_78 in most significant 16 bits */
            int             : 8;
            unsigned ver    : 4;
            int             : 4;
        } b;
        struct
        {   unsigned int ctrl_wd_12;
            unsigned int ctrl_wd_34;
            unsigned int ctrl_wd_56;
            unsigned int ctrl_wd_78;
        } i;
    } c;    /* control mode */
    union
    {   struct
        {   _fract   audio_left;
            _fract   audio_right;

            int             : 8; /* output_setting in most significant 16 bits */
            unsigned ro     : 6;
            int  se         : 1;
            int  adi        : 1;
            unsigned lo     : 6;
            int  le         : 1;
            int  he         : 1;

            int             : 8; /* input_setting in most significant 16 bits */
            unsigned rgain  : 4;
            unsigned matt   : 4;
            unsigned lgain  : 4;
            int  is         : 1;
            int  ovr        : 1;
            int  pio0       : 1;
            int  pio1       : 1;
        } b;
        struct
        {   _fract  audio_left;
            _fract  audio_right;
            unsigned int output_setting;
            unsigned int input_setting;
        } i;
    } d;    /* data mode */
    _fract b[4];    /* (circular) buffer */
} CS4215DATA;

#define NO_PREAMP       0x100000
#define LO_OUT_DRV      0x080000
#define HI_PASS_FILT    0x008000
#define SAMP_RATE_9     0x003800
#define SAMP_RATE_48    0x003000
#define SAMP_RATE_32    0x001800
#define SAMP_RATE_27    0x001000
#define SAMP_RATE_16    0x000800
#define SAMP_RATE_8     0x000000
#define STEREO          0x000400
#define DATA_8LIN       0x200300
#define DATA_8ALAW      0x200200
#define DATA_8ULAW      0x200100
#define DATA_16         0x200000
#define IMMED_3STATE    0x800000
#define XTAL1_SELECT    0x100000 /* 24.576  MHz */
#define XTAL2_SELECT    0x200000 /* 16.9344 MHz */
#define BITS_64         0x000000
#define BITS_128        0x040000
#define BITS_256        0x080000
#define CODEC_MASTER    0x020000
#define CODEC_TX_OFF    0x010000

#define HEADPHONE_EN    0x800000
#define LINEOUT_EN      0x400000
#define LEFT_ATTN       0x010000 /* 63*LEFT_ATTN   = -94.5 dB, 1.5 dB steps */
#define SPEAKER_EN      0x004000
#define RIGHT_ATTN      0x000100 /* 63*RIGHT_ATTN  = -94.5 dB, 1.5 dB steps */
#define MIC_IN_SELECT   0x100000
#define LEFT_GAIN       0x010000 /* 15*LEFT_GAIN    = 22.5 dB, 1.5 dB steps */
#define MONITOR_ATTN    0x001000 /* 15*MONITOR_ATTN = mute,    6   dB steps */
#define RIGHT_GAIN      0x000100 /* 15*RIGHT_GAIN   = 22.5 dB, 1.5 dB steps */

#endif /* _CS4215_H */


/* END OF FILE */


