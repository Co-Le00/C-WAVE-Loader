#ifndef KAGETANE_HIRUKO_FILE_MANAGER
#define KAGETANE_HIRUKO_FILE_MANAGER

#ifndef KAGETANE_HIRUKO_API

	#ifdef __cplusplus
		
		#define EXTERN_C extern "C"
	
	#else

		#define EXTERN_C

	#endif

	#ifdef _WIN32

		#ifdef BUILD_MODE

			#define KAGETANE_HIRUKO_API __declspec(dllexport)

		#else

			#define KAGETANE_HIRUKO_API __declspec(dllimport)

		#endif

	#endif

	// #define KAGETANE_HIRUKO_API
	#define DREF(pointer) (*pointer)
 
#endif

typedef struct
{
	/**

		Variable: file_path
		Holds absoulte or relative file path.

	**/
	const char * file_path;

	/**

		Variable: file_stream
		Holds the opened file stream.

	**/
	void * file_stream;
	/** 
	
		Variable: size
		Holds size of file in bytes.

	**/
	unsigned int size;;

} file_t;


/**

	Function: create_manager_for_file
	Return type: file_t *
	Params: const char *

	This function is used for creating file manger through which we will write and read.

**/
EXTERN_C file_t * KAGETANE_HIRUKO_API create_file_manager(const char * file_path, const char * mode);

/**

	Function: write_to_file
	Return type: void
	Params: const char *, const char *, const char *

	This function is used for writing text to file.

**/
EXTERN_C void KAGETANE_HIRUKO_API write_to_file(file_t * file, const char * text);

/**

	Function: read_from_file
	Return types: cons char *
	Params: const char *

	This function will read text from file and return it.

**/
EXTERN_C char * KAGETANE_HIRUKO_API read_from_file(file_t * file);

/**

	Function: close_file_manager
	Return types: void
	Params: file_t *

	This function is used for closing file streams.

**/
EXTERN_C void   KAGETANE_HIRUKO_API close_file_manager(file_t * file);

/**

	Function: set_file_stream_position
	Return type: void
	Params: file_t *, unsigned int

	This functions is used to se position of file stream.

**/
EXTERN_C void   KAGETANE_HIRUKO_API set_file_stream_position(file_t * file, unsigned int position);

/**

	Function: buffer_read_file
	Return type: void
	Params: char *, unsigned int, file_t *

	This functions is used for reading blocks of file.


**/
EXTERN_C void   KAGETANE_HIRUKO_API buffer_read_file(char * buffer, unsigned int size, file_t * file);

#endif