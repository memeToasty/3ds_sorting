#include "sound.hpp"

#include <stdio.h>
#include <math.h>
#include <3ds.h>

void fill_buffer(void *audioBuffer, size_t offset, size_t size, int frequency)
{

	u32 *dest = (u32 *)audioBuffer;

	for (int i = 0; i < (int)size; i++)
	{

		s16 sample = INT16_MAX * sin(frequency * (2 * M_PI) * (offset + i) / SAMPLERATE);

		dest[i] = (sample << 16) | (sample & 0xffff);
	}

	DSP_FlushDataCache(audioBuffer, size);
}