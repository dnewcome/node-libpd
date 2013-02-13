#include <stdio.h>
#include <v8.h>
#include <node.h>
#include "z_libpd.h"
 
using namespace node;
using namespace v8;
 
Handle<Function> printhook_callback;
Handle<Object> printhook_callback_receiver;

void pdprint(const char *s) {
	printf("%s\n", s);
	Handle<Value> msg = String::New(s);
	Handle<Value> arr[] = { msg };
	// printhook_callback->Call( printhook_callback_receiver, 1, &msg );
}

void pdnoteon(int ch, int pitch, int vel) {
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}

static void start_message() {
  libpd_start_message();
}

static void finish_message( const Arguments& args ) {
  String::AsciiValue receiver( args[0]->ToString() );
  String::AsciiValue message( args[0]->ToString() );
  libpd_finish_message( *receiver, *message);
}

static void add_float( const Arguments& args ) {
	float val = ( float )args[0]->NumberValue();
	libpd_add_float( val );
}

static Handle<Value> process_float( const Arguments& args ) {
	float inbuf[64];
	float outbuf[128];
    libpd_process_float(inbuf, outbuf);
}

static Handle<Value> openfile( const Arguments& args ) {
	// segfault 11 here under macos. Not sure if it is
	// the cast or arg[0] is missing
	String::AsciiValue filename( args[0]->ToString() );
	printf( "opening pd patch: %s\n", *filename );
	libpd_openfile( *filename, "." );
}


/**
* TODO: probably want to use EventEmitter for these
* callbacks eventually.
*/
static Handle<Value> add_printhook_listener( const Arguments& args ) {
	printf("adding listener");
	printhook_callback = Handle<Function>::Cast( args[0] );
	printhook_callback_receiver = args.This();
}

/**
* note that setup is not part of the libpd api, just 
* here for testing convenience for now.
*/
static Handle<Value> setup( const Arguments& args ) {
	int srate = 44100;
	libpd_printhook = (t_libpd_printhook) pdprint;
	libpd_noteonhook = (t_libpd_noteonhook) pdnoteon;
	libpd_init();
	libpd_init_audio(1, 2, srate, 1);
}

static Handle<Value> run(const Arguments& args)
{
  int srate = 44100;
  float inbuf[64], outbuf[128];  // one input channel, two output channels
                                 // block size 64, one tick per buffer

  // now run pd for ten seconds (logical time)
  int i;
  for (i = 0; i < 10 * srate / 64; i++) {
    // fill inbuf here
    libpd_process_float(inbuf, outbuf);
    // use outbuf here
  }
  return String::New("PD initialized");
}
 
extern "C" {
  void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "run", run);
    NODE_SET_METHOD(target, "setup", setup);
    NODE_SET_METHOD(target, "openfile", openfile);
    NODE_SET_METHOD(target, "add_printhook_listener", add_printhook_listener );
    NODE_SET_METHOD(target, "process_float", process_float);
  }
 
  NODE_MODULE(libpd, init);
}
