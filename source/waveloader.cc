
#include "../include/filemanager.h"
#include "waveloader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_big_endian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int convert_to_int(char *buffer, int len)
{
	int a = 0;
	if(!is_big_endian())
	{
		for(int i = 0; i < len; i++)
		{
			((char*) &a)[i] = buffer[i];
		}
	}
	else
	{
		for(int i = 0; i < len; i++)
		{
			((char*) &a)[3- i] = buffer[i];
		}
	}
	return a;
}

extern "C" wave_t * API load_wave_file(const char * file_path)
{
	wave_t * new_wav_file = (wave_t *) malloc(sizeof(wave_t));

	file_t * file_manager = create_file_manager(file_path, "rb");

	char buffer[4];

	buffer_read_file(buffer, 4, file_manager);
	if(strncmp(buffer, "RIFF", 4) != 0)
	{
		printf("This is not valid WAV file!");
	}
	DREF(new_wav_file).chunk_id = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).chunk_size = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).format = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).subchunk_1_id = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).subchunk_1_size = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 2, file_manager);
	DREF(new_wav_file).audio_format = convert_to_int(buffer, 2);

	buffer_read_file(buffer, 2, file_manager);
	DREF(new_wav_file).num_channels = convert_to_int(buffer, 2);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).sample_rate = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).byte_rate = convert_to_int(buffer, 4);

	buffer_read_file(buffer, 2, file_manager);
	DREF(new_wav_file).block_align = convert_to_int(buffer, 2);

	buffer_read_file(buffer, 2, file_manager);
	DREF(new_wav_file).bits_per_sample = convert_to_int(buffer, 2);

	buffer_read_file(buffer, 4, file_manager);
	if(strncmp(buffer, "data", 4) != 0)
    {
        buffer_read_file(buffer, 4, file_manager);
        int _extra_size = convert_to_int(buffer, 4);
        char _extra_data[_extra_size];
        buffer_read_file(_extra_data, _extra_size, file_manager);  
		buffer_read_file(buffer, 4, file_manager);

        DREF(new_wav_file).subchunk_2_id = convert_to_int(buffer, 4);

    }
    else
    {
    	DREF(new_wav_file).subchunk_2_id = convert_to_int(buffer, 4);
    }


	buffer_read_file(buffer, 4, file_manager);
	DREF(new_wav_file).subchunk_2_size = convert_to_int(buffer, 4);

	DREF(new_wav_file).data = (char *) malloc(DREF(new_wav_file).subchunk_2_size);
	buffer_read_file(DREF(new_wav_file).data, DREF(new_wav_file).subchunk_2_size, file_manager);

	close_file_manager(file_manager);

	return new_wav_file;
}

extern "C" void API close_wave_file(wave_t * wave_file)
{
	free(DREF(wave_file).data);
	free(wave_file);
}