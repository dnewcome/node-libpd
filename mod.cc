#include <stdio.h>
#include <v8.h>
#include <node.h>
#include "z_libpd.h"
 
using namespace node;
using namespace v8;
 
void pdprint(const char *s) {
  printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel) {
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}

static Handle<Value> foo(const Arguments& args)
{
  int srate = 44100;
  libpd_printhook = (t_libpd_printhook) pdprint;
  libpd_noteonhook = (t_libpd_noteonhook) pdnoteon;
  libpd_init();
  libpd_init_audio(1, 2, srate, 1);
  float inbuf[64], outbuf[128];  // one input channel, two output channels
                                 // block size 64, one tick per buffer

  // compute audio    [; pd dsp 1(
  libpd_start_message();
  libpd_add_float(1.0f);
  libpd_finish_message("pd", "dsp");

  // open patch       [; pd open file folder(
  libpd_openfile("test.pd", ".");

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
  static void init(Handle<Object> target)
  {
    NODE_SET_METHOD(target, "foo", foo);
  }
 
  NODE_MODULE(libpd, init);
}
