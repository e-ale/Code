#!/usr/bin/env node
var b = require('bonescript');
var wd = require('./write-digit.js');

// usage ex: sudo node e-ale/writeDigitTest.js a b

wd.writeChars(process.argv[2], process.argv[3])
