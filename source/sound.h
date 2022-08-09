#ifndef SOUND_H
#define SOUND_H

#include <stdio.h>
#include <stdlib.h>

#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

void fill_buffer(void *audioBuffer, size_t offset, size_t size, int frequency);


#endif