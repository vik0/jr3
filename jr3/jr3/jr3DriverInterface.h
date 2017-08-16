/*
 * jr3DriverInterface.h
 *
 */
#ifndef JR3DRIVERINTERFACE_H

#include "jr3Struct.h"
#include <sys/types.h>
#include <unistd.h>

extern int jr3Init ( void );
extern int jr3Close ( void );
extern int jr3ReadData1 ( unsigned long int addr, unsigned short* data );
extern int jr3DataRead ( jr3DSPStruct* jr3Data );
extern int jr3WriteData ( off_t addr, unsigned short data );
extern int jr3DataWrite1 ( jr3DSPStruct* base, short int* field );
extern int jr3DataWriteNM ( jr3DSPStruct* base, short int* fieldN, short int* fieldM );

extern int jr3SensorResetOffsets ( void );

extern void jr3DSPStruct_channelPrint ( FILE* file, jr3DSPStruct_channel *channel, char* mess );
extern void jr3DSPStruct_f6Print ( FILE* file, jr3DSPStruct_f6* f6, char* mess );
extern void jr3DSPStruct_f8Print ( FILE* file, jr3DSPStruct_f8* f8, char* mess );
extern void jr3DataPrintChannels ( FILE* file, jr3DSPStruct* data );
extern void jr3DataPrint ( FILE* file, jr3DSPStruct* data );
extern void jr3DataWarningBitsPrint ( FILE* file, unsigned short int bits );
extern void jr3DataErrorBitsPrint ( FILE* file, unsigned short int bits );

#endif
