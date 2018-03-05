#!/usr/bin/env node
var b = require('bonescript');

// setup starting conditions
var min = 0.05;
var max = 0.95;
var a = {
    red:   { val: min, step: 0.05, pin: "P2_1" },
    green: { val: min, step: 0.02, pin: "P1_33" },
    blue:  { val: min, step: 0.01, pin: "P1_36" }
};

// configure pin
b.pinMode(a.red.pin, b.ANALOG_OUTPUT);
b.pinMode(a.green.pin, b.ANALOG_OUTPUT);
b.pinMode(a.blue.pin, b.ANALOG_OUTPUT);

// call function to update brightness every 10ms
setTimeout(function() {
    setInterval(fade, 10);
}, 500);


// function to update brightness
function fade() {
    for(var x in a) {
        b.analogWrite(a[x].pin, a[x].val);
        a[x].val += a[x].step;
        if(a[x].val >= max || a[x].val <= min) {
            a[x].step = -1 * a[x].step;
        }
    }
}
