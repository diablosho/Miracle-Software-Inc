#include <stdio.h>
#include <stdlib.h>
#define NOARGS -1
#define SUCCESS 0

/*	[Given]			Real Mem Size	=	{[2 ^ 32]}*Bytes		=	4,294,967,296 Bytes
	[Given]			Page Size		=	{[2 ^ 12]}*Bytes		=	4,096 Bytes
	[Calculated]	Page Qty		=	{[(2^32)/(2^12)]}*Pages	=	{[2^20]}*Pages	=	{[1,048,576]} Pages
*/

const	long	unsigned	rangePageIndices		=	4294963200,	//	[32-bits - 12-bits] = 20 High-Order Bits	=	0xFFFFF000
							rangePageOffsets		=	4095;		//	[32-bits - 20-bits] = 12 Low-Order Bits		=	0x00000FFF

void Output(long unsigned decimalInput, long unsigned pageIndex, long unsigned pageOffset)
{
	fprintf(stderr, "The Virtual-Address %lu contains:\n",	decimalInput);
	fprintf(stderr, "\tPage Index:\t%lu\n",					pageIndex);
	fprintf(stderr, "\tPage Offset:\t%lu\n\n",			pageOffset);
}