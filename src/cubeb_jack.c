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
  int callbacks;
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
  jack_port_t * output_ports[2];
  void * user_ptr;
};


int jack_process(jack_nframes_t nframes, void *arg) {

  cubeb *ctx = (cubeb *)arg;
	
  ctx->jack->callbacks++;
	
  return 0;
}


void jack_shutdown(void *arg) {

  //cubeb *ctx = (cubeb *)arg;

}

int jack_xrun(void *arg)
{

  cubeb *ctx = (cubeb *)arg;

  ctx->jack->xruns++;
	
  printf("Cubeb Jack %s xrun number %d!\n", ctx->jack->client_name, ctx->jack->xruns);

  return 0;

}

int cubeb_init(cubeb ** context, char const * context_name) {

  cubeb *ctx;
  jack_t *jack;
	
  ctx = calloc(1, sizeof(*ctx));

  assert(ctx);
             
  printf("Cubeb Jack init context: %s\n", context_name);      

  jack = calloc (1, sizeof (jack_t));

  assert(jack);

  jack->client_name = "cubeb";

  jack->server_name = NULL;
  jack->options = JackNoStartServer;

  jack->userdata = ctx;

  // Connect up to the JACK server 

  jack->jack_client = jack_client_open (jack->client_name, jack->options, &jack->status, jack->server_name);
  
  if (jack->jack_client == NULL) {
    printf("jack_client_open() failed, status = 0x%2.0x\n", jack->status);
    if (jack->status & JackServerFailed) {
      printf("Unable to connect to JACK server\n");
	}
	free(jack);
	free(ctx);
    return CUBEB_ERROR;
  }

  if (jack->status & JackNameNotUnique) {
    jack->client_name = jack_get_client_name(jack->jack_client);
    printf("unique name `%s' assigned\n", jack->client_name);
  }

  /* Set up Callbacks */

  jack_set_process_callback (jack->jack_client, jack_process, jack->userdata);
  jack_on_shutdown (jack->jack_client, jack_shutdown, jack->userdata);
  jack_set_xrun_callback (jack->jack_client, jack_xrun, jack->userdata);

  // Activate

  if (jack_activate (jack->jack_client)) {
    printf("cannot activate client\n");
	free(jack);
	free(ctx);
    return CUBEB_ERROR;
  }

  ctx->jack = jack;
  *context = ctx;
  
  return CUBEB_OK;

}

/** Destroy an application context.
    @param context */
void cubeb_destroy(cubeb * context) {

  printf("Cubeb Jack destroy context\n");      

  printf("%d callbacks, %d xruns.\n", context->jack->callbacks, context->jack->xruns);
	
  jack_client_close (context->jack->jack_client);
  free(context->jack);
  free(context);

}


int cubeb_stream_init(cubeb * context, cubeb_stream ** stream, char const * stream_name,
                      cubeb_stream_params stream_params, unsigned int latency,
                      cubeb_data_callback data_callback,
                      cubeb_state_callback state_callback,
                      void * user_ptr) {
                
  printf("Cubeb Jack init stream\n");
  
  cubeb_stream *stm = calloc(1, sizeof(cubeb_stream));
  
  stm->context = context;
  
  stm->output_ports[0] = jack_port_register (stm->context->jack->jack_client, "Test_Left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  stm->output_ports[1] = jack_port_register (stm->context->jack->jack_client, "Test_Right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  *stream = stm;
                   
  return CUBEB_OK;
                      
}

void cubeb_stream_destroy(cubeb_stream * stream) {

  printf("Cubeb Jack destroy stream\n");      

  jack_port_unregister (stream->context->jack->jack_client, stream->output_ports[0]);
  jack_port_unregister (stream->context->jack->jack_client, stream->output_ports[1]);
     
  free(stream);   
  
  return CUBEB_OK;
}

int cubeb_stream_start(cubeb_stream * stream) {

  printf("Cubeb Jack start stream\n");      
                      
  return CUBEB_OK;

}

int cubeb_stream_stop(cubeb_stream * stream) {

  printf("Cubeb Jack stop stream\n");      
                      
  return CUBEB_OK;

}

int cubeb_stream_get_position(cubeb_stream * stream, uint64_t * position) {

  printf("Cubeb Jack stream position\n");      
                      
  return CUBEB_OK;

}
