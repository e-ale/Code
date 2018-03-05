#!/usr/bin/env node
// Based on https://groups.google.com/forum/#!category-topic/beagleboard/iT3JsATQIjI

//# fekerr 20180227
//# https://github.com/beagleboard/pocketbeagle/wiki/System-Reference-Manual#221_PocketBone

// Writing to SPI GPIO to 7-segment LEDs per https://github.com/e-ale/BaconBitsCapeHW Rev 0/1

var b = require('bonescript');

var LE = "P2_31" ; // nCS
var SPI = "P2_25"; // MOSI
var CLK = "P2_29"; // CLK

var chip = [
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xfe
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xfe
    ],
    [
        0x40, 0x00, // Write address 0 (IODIRA)
        0x00
    ],
    [
        0x40, 0x01, // Write address 0x01 (IODIRB)
        0x00
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xfd
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xfd
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xfb
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xfb
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xf7
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xf7
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xef
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xef
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xdf
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xdf
    ],
    [
        0x40, 0x12, // Write address 0x12 (GPIOA)
        0xbf
    ],
    [
        0x40, 0x13, // Write address 0x13 (GPIOB)
        0xbf
    ],
];

// Configure pins as outputs
b.pinMode(LE, b.OUTPUT);
b.pinMode(SPI, b.OUTPUT);
b.pinMode(CLK, b.OUTPUT);

// initial states
b.digitalWrite(LE, b.LOW);
b.digitalWrite(SPI, b.LOW);
b.digitalWrite(CLK, b.LOW);

doUpdate();

function doUpdate()
{
    var i, j;
    for(j=0; j<chip.length; j++)
    {
        b.digitalWrite(LE, b.LOW);
        for(i=0; i<chip[j].length; i++)
        {
            b.shiftOut(SPI, CLK, b.MSBFIRST, chip[j][i]);
        }
        b.digitalWrite(LE, b.HIGH);
    }
    doUpdate();
}

