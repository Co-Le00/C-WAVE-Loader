#include "source/waveloader.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
	wave_t * wav_file = load_wave_file("life.wav");

	if(wav_file)
	{
		printf("%d\n", wav_file -> subchunk_2_size);
	}

	close_wave_file(wav_file);

	return 0;
}