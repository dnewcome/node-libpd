# Pure Data native module for Node.js

# About

node-libpd is a native node.js module that provides access to libpd functions. Libpd provides access
to the Pure Data audio and event processing engine, but there is no UI provided.

The current state of the code supports loading a PD patch file and setting the sample rate, etc.
Processing audio buffers is still a work in progress.

# Prerequisites

    Install on osx using homebrew
    node - tested most recently on node v0.8.16, initially developed starting with version 0.4 or so, so 
	probably works on most of what is in between
    v8 - 3.9.24 - again, developed when v8 was in its infancy, so probably works with many versions of v8

# Building

Run the appropriate build script for your platform. I'm not using anything fancy to build this yet. 
Binaries are under libpd. If you are on a 32 bit platform you'll probably need to build your own libpd.
mac and linux 64 bit binaries are provided here.

# Running

    $ node test.js

# Status

This work is slowly in progress. I'm not actively using it in any projects yet, it's just for fun
and to see if it's possible at this point. Have fun.

