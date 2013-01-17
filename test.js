var libpd = require('./libpd.node');
libpd.setup();
libpd.add_printhook_listener( function(msg) { console.log(msg); } );
libpd.openfile('test.pd');

var srate = 44100;
var inbuf, outbuf = null;
for( var i=0; i < 10 * srate / 64; i++ ) {
//	libpd.process_float(inbuf, outbuf);
}


