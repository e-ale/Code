#!/usr/bin/env node
var b = require('bonescript');


const theBits = {
  '0': '0111111',
  '1': '0000110',
  '2': '1011011',
  '3': '1001111',
  '4': '1100110',
  '5': '1101101',
  '6': '1111101',
  '7': '0000111',
  '8': '1111111',
  '9': '1101111',
  'a': '1110111',
  'b': '1111100',
  'c': '0111001',
  'd': '1110001',
  'e': '1111001',
  'f': '1110001',
  'g': '0000000',
  'h': '1010101',
  'i': '0101010',
}


function getBits(c) {
  return theBits[c];
}


function getFileName(gpio) {
  return '/sys/class/gpio/gpio' + gpio + '/direction';
}


function writeBits(gpioBase, c) {
  const bits = getBits(c);
  
  for (let i = 0; i < 7; i++) {
    let fileName = getFileName(gpioBase + i);
    
    switch(bits[6 - i]) {
      case '0':
        b.writeTextFile(fileName, 'in');
        break;
      case '1':
        b.writeTextFile(fileName, 'out');
        break;
    }

  }
}

  
exports.writeChars = function(c1, c2 = 'g') { 
  writeBits(496, c1);
  writeBits(504, c2);
}
