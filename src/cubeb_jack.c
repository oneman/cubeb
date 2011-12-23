#include <pthread.h>
#include <sys/time.h>
#include <assert.h>
#include <limits.h>
#include <poll.h>
#include <unistd.h>

#include <jack/jack.h>

#include "cubeb/cubeb.h"

typedef struct jack_St jack_t;

struct jack_St {

	int active;
	int xruns;
	const char *server_name;
	const char *client_name;
	jack_options_t options;
	jack_status_t status;
	jack_client_t *jack_client;
    void *userdata;
    
};

struct cubeb {
  jack_t *jack;
  
};

struct cubeb_stream {
  struct cubeb * context;
  cubeb_data_callback data_callback;
  cubeb_state_callback state_callback;
  cubeb_stream_params params;
  jack_port_t * output_ports;
  void * user_ptr;
};


/** Initialize an application context.  This will perform any library or
    application scoped initialization.
    @param context
    @param context_name
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_init(cubeb ** context, char const * context_name) {

  ctx = calloc(1, sizeof(*ctx));

                
  printf("Wanted to Init context: %s\n", context_name);      

  *context = ctx;
  
  return CUBEB_OK;

}

/** Destroy an application context.
    @param context */
void cubeb_destroy(cubeb * context) {

  free(context);

}

/** Initialize a stream associated with the supplied application context.
    @param context
    @param stream
    @param stream_name
    @param stream_params
    @param latency Approximate stream latency in milliseconds.  Valid range is [1, 2000].
    @param data_callback Will be called to preroll data before playback is
                          started by cubeb_stream_start.
    @param state_callback
    @param user_ptr
    @retval CUBEB_OK
    @retval CUBEB_ERROR
    @retval CUBEB_ERROR_INVALID_FORMAT */
int cubeb_stream_init(cubeb * context, cubeb_stream ** stream, char const * stream_name,
                      cubeb_stream_params stream_params, unsigned int latency,
                      cubeb_data_callback data_callback,
                      cubeb_state_callback state_callback,
                      void * user_ptr) {
                
  printf("Wanted to Init stream\n");      
                      
  return CUBEB_OK;
                      
}

/** Destroy a stream.
    @param stream */
void cubeb_stream_destroy(cubeb_stream * stream) {

  printf("Wanted to destroy stream\n");      
                      
  return CUBEB_OK;
}

/** Start playback.
    @param stream
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_stream_start(cubeb_stream * stream) {

  printf("Wanted to start stream\n");      
                      
  return CUBEB_OK;

}

/** Stop playback.
    @param stream
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_stream_stop(cubeb_stream * stream) {

  printf("Wanted to stop stream\n");      
                      
  return CUBEB_OK;
  

}

/** Get the current stream playback position.
    @param stream
    @param position Playback position in frames.
    @retval CUBEB_OK
    @retval CUBEB_ERROR */
int cubeb_stream_get_position(cubeb_stream * stream, uint64_t * position) {


  printf("Wanted to get stream position\n");      
                      
  return CUBEB_OK;


}
