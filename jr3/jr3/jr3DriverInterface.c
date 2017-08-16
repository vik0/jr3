/*
 *  jr3DriverInterface.c  : this files defines functions to dialog with 
 *          jr3 driver.
 *
 * Copyright (c) 2006 CNRS/LAAS
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "jr3DriverInterface.h"

static int f_id;

int jr3Init(void)
{
  f_id = open("/dev/jr3", O_RDWR);
  if (f_id < 0) {
    perror("can't open /dev/jr3\n");
    return -1;
  }
  return 1;
}

int jr3Close(void)
{
  if (close(f_id) != 0) {
    perror("can't close /dev/jr3\n");
    return -1;
  }
  f_id = 0; /* ? */
  return 0;
}

int jr3ReadData1(unsigned long int addr, unsigned short* data)
{
  unsigned short data_l;

  if (lseek(f_id, addr, SEEK_SET) == -1) {
    perror("jr3ReadData1 lseek: ");
    return -1;
  }
  if (read(f_id, (void*) &data_l, (sizeof data_l)) == -1) {
    perror("jr3ReadData1 lseek: ");
    return -1;
  }
  *data = data_l;
  return 0;
}

int jr3DataRead(jr3DSPStruct* jr3Data)
{
  int status;

  if (lseek(f_id, 0, SEEK_SET) == -1) {
    perror("jr3DataRead lseek: ");
    return -1;
  }
  status = read(f_id, (void*) jr3Data, (sizeof(jr3DSPStruct)));
  if (status != sizeof(jr3DSPStruct))
    perror("jr3DataRead lseek: ");

  return status;
}

int jr3WriteData(off_t addr, unsigned short data)
{
  int status;

  if (lseek(f_id, addr, SEEK_SET) == -1) {
    perror("jr3ReadData lseek: ");
    return -1;
  }
  status = write(f_id, (void*) &data, (sizeof data));
  if (status != 2) {
    fprintf(stderr, "jr3WriteData write status= %d\n", status);
    perror("jr3WriteData write: ");
    return -1;
  }
  return 2;
}

int jr3DataWrite1(jr3DSPStruct* base, short int* field)
{
  short int* addr = (short int*) (field - (short int*) base);
  if (addr < 0
      || addr > &(base->thickness)) {
    fprintf(stderr, "jr3DataWrite1 error:\n\t\t");
    fprintf(stderr, "base= 0x%X  field= %X  addr= %X  *field= %d\n",
	    (unsigned int) base, (unsigned int) field, (unsigned int) addr,
	    *field);
    return -1;
  }
  printf("jr3DataWrite1: base= 0x%X  field= Ox%X  addr= 0x%X  *field= %d\n",
	 (unsigned int) base, (unsigned int) field, (unsigned int) addr, 
	 *field);
  return jr3WriteData((off_t) addr, *field);
}

int jr3DataWriteNM(jr3DSPStruct* base, short int* fieldN, short int* fieldM)
{
  short int* addr;
  int status;

  for(addr = fieldN; addr <= fieldM; addr++) {
    status = jr3DataWrite1(base, addr);
    if (status != 2) {
      fprintf(stderr, "jr3DataWrite1 error\n");
      return status;
    }
  }
  return fieldM - fieldN; /* Ok: return the number of short int writen */
}


#define JR3_COMMANDWORD_0 0x00e7
#define JR3_COMMANDWORD_1 0x00e6
#define JR3_COMMANDWORD_2 0x00e5

#define JR3_COMMAND_USE_OFFSET 0x0600
#define JR3_COMMAND_SET_OFFSET 0x0700
#define JR3_COMMAND_RESET_OFFSET 0x0800

int jr3SensorResetOffsets()
{
  return jr3WriteData(JR3_COMMANDWORD_0, JR3_COMMAND_RESET_OFFSET);
  //return jr3WriteData(0x0088, 1000);
}

void jr3DSPStruct_channelPrint(FILE* file, jr3DSPStruct_channel *channel,
			       char* mess) {
  fprintf(file, "%s: time= %d\t data= %d", mess, channel->time, channel->data);
  fprintf(file, "\t reserved1= %d\t reserved2= %d", 
	  channel->reserved1, channel->reserved2);
  fprintf(file, "\n");
}

void jr3DSPStruct_f6Print (FILE* file, jr3DSPStruct_f6* f6, char* mess)
{
  fprintf(file, "%s: fx= %d\tfy= %d\tfz= %d\t  mx= %d\tmy= %d\tmz= %d\n",
	  mess, f6->fx, f6->fy, f6->fz, f6->mx, f6->my, f6->mz);
}

void jr3DSPStruct_f8Print (FILE* file, jr3DSPStruct_f8* f8, char* mess)
{
  fprintf(file,
   "%s: fx= %d\tfy= %d\tfz= %d\n\t   mx= %d\tmy= %d\tmz= %d\tv1= %d\tv2= %d\n",
	  mess,
	  f8->fx, f8->fy, f8->fz, f8->mx, f8->my, f8->mz, f8->v1, f8->v2);
}

void jr3DataPrintChannels(FILE* file, jr3DSPStruct* data)
{
  jr3DSPStruct_channelPrint(file, &(data->channel0), "channel0");
  jr3DSPStruct_channelPrint(file, &(data->channel1), "channel1");
  jr3DSPStruct_channelPrint(file, &(data->channel2), "channel2");
  jr3DSPStruct_channelPrint(file, &(data->channel3), "channel3");
  jr3DSPStruct_channelPrint(file, &(data->channel4), "channel4");
  jr3DSPStruct_channelPrint(file, &(data->channel5), "channel5");
  jr3DSPStruct_channelPrint(file, &(data->channel6), "channel6");
  jr3DSPStruct_channelPrint(file, &(data->channel7), "channel7");
  jr3DSPStruct_channelPrint(file, &(data->channel8), "channel8");
  jr3DSPStruct_channelPrint(file, &(data->channel9), "channel9");
  jr3DSPStruct_channelPrint(file, &(data->channelA), "channelA");
  jr3DSPStruct_channelPrint(file, &(data->channelB), "channelB");
  jr3DSPStruct_channelPrint(file, &(data->channelC), "channelC");
  jr3DSPStruct_channelPrint(file, &(data->channelD), "channelD");
  jr3DSPStruct_channelPrint(file, &(data->channelE), "channelE");
  jr3DSPStruct_channelPrint(file, &(data->channelF), "channelF");
}

void jr3DataPrint(FILE* file, jr3DSPStruct* data)
{
  jr3DataPrintChannels(file, data);
  fprintf(file, "copyright= %s\n", (char*) data->copyright);
  jr3DSPStruct_f6Print(file, &(data->shunt), "shunt");
  fprintf(file, "\t\treserved0[2]= %d %d\n", 
	  data->reserved0[0], data->reserved0[1]);
  /* 0x68 */
  jr3DSPStruct_f6Print(file, &(data->sensorDefaultFullScale), 
		       "sensorDefaultFullScale");
  fprintf(file, "\t\treserved1= %d   load_envelope= %d\n", 
	  data->reserved1, data->load_envelope);
  /* 0x70 */
  jr3DSPStruct_f6Print(file, &(data->min_fs), "min_fs");
  fprintf(file, "\t\treserved2= %d   xForm= %d\n", 
	  data->reserved2, data->xForm);
  /* 0x78 */
  jr3DSPStruct_f6Print(file, &(data->max_fs), "max_fs");
  fprintf(file, "\t\treserved3= %d   peak_addr= %d\n", 
	  data->reserved3, data->peak_addr);
  /* 0x80 */
  jr3DSPStruct_f8Print(file, &(data->fullScale), "fullScale");
  /* 0x88 */
  jr3DSPStruct_f6Print(file, &(data->current_offset_value),
		       "current_offset_value");
  fprintf(file, "\t\toffset_number= %d   vect_axes= %d\n", 
	  data->offset_number, data->vect_axes);
  /* 0x90 */
  jr3DSPStruct_f8Print(file, &(data->f0), "f0");
  /* 0x98 */
  jr3DSPStruct_f8Print(file, &(data->f1), "f1");
  /* 0xa0 */
  jr3DSPStruct_f8Print(file, &(data->f2), "f2");
  /* 0xa8 */
  jr3DSPStruct_f8Print(file, &(data->f3), "f3");
  /* 0xb0 */
  jr3DSPStruct_f8Print(file, &(data->f4), "f4");
  /* 0xb8 */
  jr3DSPStruct_f8Print(file, &(data->f5), "f5");
  /* 0xc0 */
  jr3DSPStruct_f8Print(file, &(data->f6), "f6");
  /* 0xc8 */
  jr3DSPStruct_f8Print(file, &(data->rate), "rate");
  /* 0xd0 */
  jr3DSPStruct_f8Print(file, &(data->min), "min");
  /* 0xd8 */
  jr3DSPStruct_f8Print(file, &(data->max), "max");
  /* 0xe0 */
  fprintf(file, "near_sat= %d sat= %d rate_addr= %d rate_div= %d\n",
	  data->near_sat, data->sat, data->rate_addr, data->rate_div);
  fprintf(file, "\t\trate_count= %d comm2= %d comm1= %d comm0= %d\n",
	  data->rate_count, data->comm2, data->comm1, data->comm0);
  /* 0xe8 */
  jr3DSPStruct_f6Print(file, &(data->count), "count");
  fprintf(file, "\t\terrors= %d   countx= %d\n", 
	  data->errors, data->countx);
  /* 0xf0 */
  fprintf(file, "warning= %d error= %d threshold= %d crc= %d\n",
	  data->warning, data->error, data->threshold, data->crc);
  fprintf(file,
	  "\tromVersion= %d versionNumber= %d versionDay= %d versionYear= %d\n",
	  data->romVersion, data->versionNumber,
	  data->versionDay, data->versionYear);
  /* 0xf8 */
  fprintf(file, "serial= %d model= %d calibrationDay= %d calibrationYear= %d\n",
	  data->serial, data->model,
	  data->calibrationDay, data->calibrationYear);
  fprintf(file, "\tunits= %d bits= %d chans= %d thickness= %d\n",
	  data->units, data->bits, data->chans, data->thickness);
}

void jr3DataWarningBitsPrint(FILE* file, unsigned short int bits)
{
  fprintf(file, "JR3_BIT_FX_SAT= %d\n", bits & JR3_BIT_FX_SAT);
  fprintf(file, "JR3_BIT_FY_SAT= %d\n", bits & JR3_BIT_FY_SAT);
  fprintf(file, "JR3_BIT_FZ_SAT= %d\n", bits & JR3_BIT_FZ_SAT);
  fprintf(file, "JR3_BIT_MX_SAT= %d\n", bits & JR3_BIT_MX_SAT);
  fprintf(file, "JR3_BIT_MY_SAT= %d\n", bits & JR3_BIT_MY_SAT);
  fprintf(file, "JR3_BIT_MZ_SAT= %d\n", bits & JR3_BIT_MZ_SAT);
//  fprintf(file, "JR3_BIT_RESERVED1= %d\n", bits & JR3_BIT_RESERVED1);
//  fprintf(file, "JR3_BIT_RESERVED2= %d\n", bits & JR3_BIT_RESERVED2);
//  fprintf(file, "JR3_BIT_RESERVED3= %d\n", bits & JR3_BIT_RESERVED3);
//  fprintf(file, "JR3_BIT_RESERVED4= %d\n", bits & JR3_BIT_RESERVED4);
  fprintf(file, "JR3_BIT_MEMORY_ERROR= %d\n", bits & JR3_BIT_MEMORY_ERROR);
  fprintf(file, "JR3_BIT_SENSOR_CHANGE= %d\n", bits & JR3_BIT_SENSOR_CHANGE);
  fprintf(file, "JR3_BIT_SYSTEM_BUSY= %d\n", bits & JR3_BIT_SYSTEM_BUSY);
  fprintf(file, "JR3_BIT_CAL_CRC_BAD= %d\n", bits & JR3_BIT_CAL_CRC_BAD);
  fprintf(file, "JR3_BIT_WATCH_DOG2= %d\n", bits & JR3_BIT_WATCH_DOG2);
  fprintf(file, "JR3_BIT_WATCH_DOG= %d\n", bits & JR3_BIT_WATCH_DOG);
}

void jr3DataErrorBitsPrint(FILE* file, unsigned short int bits)
{
  fprintf(file, "JR3_BIT_FX_NEAR_SAT= %d\n", bits & JR3_BIT_FX_NEAR_SAT);
  fprintf(file, "JR3_BIT_FY_NEAR_SAT= %d\n", bits & JR3_BIT_FY_NEAR_SAT);
  fprintf(file, "JR3_BIT_FZ_NEAR_SAT= %d\n", bits & JR3_BIT_FZ_NEAR_SAT);
  fprintf(file, "JR3_BIT_MX_NEAR_SAT= %d\n", bits & JR3_BIT_MX_NEAR_SAT);
  fprintf(file, "JR3_BIT_MY_NEAR_SAT= %d\n", bits & JR3_BIT_MY_NEAR_SAT);
  fprintf(file, "JR3_BIT_MZ_NEAR_SAT= %d\n", bits & JR3_BIT_MZ_NEAR_SAT);
}
