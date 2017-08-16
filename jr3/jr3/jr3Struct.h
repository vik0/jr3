/*
 * jr3Struct.h
 *
 */

#ifndef JR3STRUCT_H
#define JR3STRUCT_H

typedef struct jr3DSPStruct_channel {
  short int time; /* time last data for channel was received */
  short int data; /* last data received for raw channel */
  short int reserved1;
  short int reserved2;
} jr3DSPStruct_channel;

typedef struct jr3DSPStruct_f6 {
  short int fx;
  short int fy;
  short int fz;
  short int mx;
  short int my;
  short int mz;
} jr3DSPStruct_f6;

typedef struct jr3DSPStruct_f8 {
  short int fx;
  short int fy;
  short int fz;
  short int mx;
  short int my;
  short int mz;
  short int v1;
  short int v2;
} jr3DSPStruct_f8;


typedef struct jr3DSPStruct {
  /* 0x00 */
  jr3DSPStruct_channel channel0;
  jr3DSPStruct_channel channel1;
  jr3DSPStruct_channel channel2;
  jr3DSPStruct_channel channel3;
  jr3DSPStruct_channel channel4;
  jr3DSPStruct_channel channel5;
  jr3DSPStruct_channel channel6;
  jr3DSPStruct_channel channel7;
  jr3DSPStruct_channel channel8;
  jr3DSPStruct_channel channel9;
  jr3DSPStruct_channel channelA;
  jr3DSPStruct_channel channelB;
  jr3DSPStruct_channel channelC;
  jr3DSPStruct_channel channelD;
  jr3DSPStruct_channel channelE;
  jr3DSPStruct_channel channelF;
  /* 0x38 */
  short int copyright[32];
  /* 0x60 */
  jr3DSPStruct_f6 shunt; /* shunt readind for channel */
  short int reserved0[2];
  /* 0x68 */
  jr3DSPStruct_f6 sensorDefaultFullScale;
  short int reserved1;
  short int load_envelope; /* number of currently active load envelope */
  /* 0x70 */
  jr3DSPStruct_f6 min_fs; /* min full scale, at which the data will not 
			     have the lsb zero filled */
  short int reserved2;
  short int xForm; /* number of transform currently in use */
  /* 0x78 */
  jr3DSPStruct_f6 max_fs; /* max full scale, at which the data will not
			     have the lsb truncated */
  short int reserved3;
  short int peak_addr; /* addr of the data used in finding the maxima 
			  and minima */
  /* 0x80 */
  jr3DSPStruct_f8 fullScale; /* full scale value for fi when fi=16384
				this is the equivalent engineering units */
  /* 0x88 */
  jr3DSPStruct_f6 current_offset_value;
  short int offset_number; /* ofs : number of the offset currently in use */
  short vect_axes; /* bit map for the axes which are being used for
		      calculating the vectors */
  /* 0x90 */
  jr3DSPStruct_f8 f0;
  /* 0x98 */
  jr3DSPStruct_f8 f1;
  /* 0xa0 */
  jr3DSPStruct_f8 f2;
  /* 0xa8 */
  jr3DSPStruct_f8 f3;
  /* 0xb0 */
  jr3DSPStruct_f8 f4;
  /* 0xb8 */
  jr3DSPStruct_f8 f5;
  /* 0xc0 */
  jr3DSPStruct_f8 f6;
  /* 0xc8 */
  jr3DSPStruct_f8 rate; /* rate calculation */
  /* 0xd0 */
  jr3DSPStruct_f8 min; /* minimum peak (valley) value */
  /* 0xd8 */
  jr3DSPStruct_f8 max; /* maximum peak value */
  /* 0xe0 */
  short int near_sat; /* raw value which sets near sat bit in warning word */
  short int sat; /* raw value which sets near sat bit in error word */
  short int rate_addr; /* address of data used for calculating the rate data */
  short int rate_div;  /* rate divisor, the number of samples between rate
			  calculations */
  short int rate_count; /* this counter counts up to rate div, and then 
			   the rates are calculated */
  short int comm2; /* command word 2 \                                */
  short int comm1; /* command word 1  } area used to send commands to */
  short int comm0; /* command word 0 /                      JR3 DSP   */
  /* 0xe8 */
  jr3DSPStruct_f6 count; /* counter for filter, 1 count = 1 filter iteration */
  short int errors; /* a count of data reception errors */
  short int countx; /* ??? */
  /* 0xf0 */
  short int warning;   /* warning word */
  short int error;     /* error word */
  short int threshold; /* threshold monitoring word (load envlopes) */
  short int crc;
  short int romVersion; /* version no. of data stored in sensor EEProm */
  short int versionNumber; /* software version number that the JR3 DSP is
			      running */
  short int versionDay;
  short int versionYear;
  /* 0xf8 */
  short int serial; /* sensor serial number */
  short int model;  /* sensor model number */
  short int calibrationDay;  /* last calibration date of the sensor */
  short int calibrationYear;
  short int units; /* engineering units of full scale, 0 is lbs, in-lbs
		                                       1 is Newtons ...*/
  short int bits; /* number of bits in sensor ADC */
  short int chans; /* bit map of channels the sensor is capable of sending */
  short int thickness; /* the thickness of the sensor */
} jr3DSPStruct;


#define JR3_BIT_FX_SAT         (1    )
#define JR3_BIT_FY_SAT         (1<<1 )
#define JR3_BIT_FZ_SAT         (1<<2 )
#define JR3_BIT_MX_SAT         (1<<3 )
#define JR3_BIT_MY_SAT         (1<<4 )
#define JR3_BIT_MZ_SAT         (1<<5 )
#define JR3_BIT_RESERVED1      (1<<6 )
#define JR3_BIT_RESERVED2      (1<<7 )
#define JR3_BIT_RESERVED3      (1<<8 )
#define JR3_BIT_RESERVED4      (1<<9 )
#define JR3_BIT_MEMORY_ERROR   (1<<10)
#define JR3_BIT_SENSOR_CHANGE  (1<<11)
#define JR3_BIT_SYSTEM_BUSY    (1<<12)
#define JR3_BIT_CAL_CRC_BAD    (1<<13)
#define JR3_BIT_WATCH_DOG2     (1<<14)
#define JR3_BIT_WATCH_DOG      (1<<15)

#define JR3_BIT_FX_NEAR_SAT         (1    )
#define JR3_BIT_FY_NEAR_SAT         (1<<1 )
#define JR3_BIT_FZ_NEAR_SAT         (1<<2 )
#define JR3_BIT_MX_NEAR_SAT         (1<<3 )
#define JR3_BIT_MY_NEAR_SAT         (1<<4 )
#define JR3_BIT_MZ_NEAR_SAT         (1<<5 )

#endif
