#ifndef FILE_LOADER
#define WAVE_FILE_LOADER

#ifndef API

	#ifdef __cplusplus
		
		#define EXTERN_C extern "C"
	
	#else

		#define EXTERN_C

	#endif

	#ifdef _WIN32

		#ifdef BUILD_MODE

			#define API __declspec(dllexport)

		#else

			#define API __declspec(dllimport)

		#endif

	#else
		
		#define APIl

	#endif

	#define DREF(pointer) (*pointer)

	

#endif


typedef struct 
{
	// The canonical WAVE format starts with the RIFF header:

	/**
		
		Variable: chunk_id
		Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).

	**/
	int chunk_id;

	/**

		Variable: chunk_size
		36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
        This is the size of the rest of the chunk following this number.  
        This is the size of the entire file in bytes minus 8 bytes for the
        two fields not included in this count: ChunkID and ChunkSize.

	**/
	int chunk_size;

	/**

		Variable: format
		Contains the letters "WAVE" (0x57415645 big-endian form).

	**/
	int format;

	// The "WAVE" format consists of two subchunks: "fmt " and "data":
	// The "fmt " subchunk describes the sound data's format:

	/**
		
		Variable: subchunk_1_id
		Contains the letters "fmt " (0x666d7420 big-endian form).

	**/
	int subchunk_1_id;

	/**
		
		Variable: subchunk_1_size
		16 for PCM.  This is the size of the rest of the Subchunk which follows this number.

	**/
	int subchunk_1_size;

	/**
		
		Variable: audio_format
		PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.

	**/
	short audio_format;

	/**
		
		Variable: num_channels
		Mono = 1, Stereo = 2, etc.

	**/
	short num_channels;

	/**
		
		Variable: sample_rate
		8000, 44100, etc.

	**/
	int sample_rate;

	/**
		
		Variable: byte_rate
		== SampleRate * NumChannels * BitsPerSample/8

	**/
	int byte_rate;

	/**
		
		Variable: block_align
		== NumChannels * BitsPerSample/8
        The number of bytes for one sample including all channels. I wonder what happens 
        when this number isn't an integer?

	**/
	short block_align;

	/**
		
		Variable: bits_per_sample
		8 bits = 8, 16 bits = 16, etc.

	**/
	short bits_per_sample;

	/**

		Here should come some extra parameters which i will avoid.

	**/

	// The "data" subchunk contains the size of the data and the actual sound:

	/**

		Variable: subchunk_2_id
		Contains the letters "data" (0x64617461 big-endian form).

	**/
	int subchunk_2_id;

	/**

		Variable: subchunk_2_size
		== NumSamples * NumChannels * BitsPerSample/8
        This is the number of bytes in the data. You can also think of this as the size
        of the read of the subchunk following this number.

	**/
	int subchunk_2_size;

	/**
	
		Variable: data
 		The actual sound data.

	**/
	char * data;

} wave_t;


/**

	Function: load_wav_file
	Return type: wav_t
	Params: const char *

	This function is used to fetch all information form given wave file and return formated struct.

**/
EXTERN_C wave_t * API load_wave_file(const char * file_path);

/**

	Function: delete_wave_file
	Return type: void
	Params: wave_t * 

	This function is used to free wave struct.

**/
EXTERN_C void API close_wave_file(wave_t * wave_file);


#endif