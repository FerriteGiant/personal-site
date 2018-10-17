+++
date = "2018-09-23T16:16:36-07:00"
title = "DIY Suunto Vyper Data Cable"
showonlyimage = false
image = "projects/vyper-cable/LinkImage-graph.png"
draft = false

+++
Replacing an $85 cable with less than $15 in parts.
<!--more-->

To buy the cable from Suunto for connecting my Vyper dive computer to my desktop computer is absurdly expensive. [On Amazon it goes for $85.](https://www.amazon.com/Suunto-Download-Cobra-Mosquito-computers/dp/B000JL2C06) Fortunately I was able to find info online about building an adapter from components I already had. 

* [PDF](http://homepage.hispeed.ch/scubadiver/download/usb.pdf) from which I mainly adapted this circuit
* [Image gallery](http://homepage.hispeed.ch/scubadiver/english.html) with ideas of how to made the physical connection (click "Picture Gallery" on the sidebar)

The main downside of the info already available was that much of it was designed for hooking up to a serial port (which computers don't really have any more), or was simply more complicated than strictly needed. Below is what I believe to be the simplest and probably cheapest way to build a vyper interface cable.

The Suunto software doesn't seem to work with this, but from reading around I'm not sure if my adapter is to blame or it's just that the software is crap. I've been using the fantastic [Subsurface](https://subsurface-divelog.org/) software on Windows 10. This should work fine on Linux as well. 

**Obviously you should know what you are doing and I take no responsibility if you kill any of your computers, or really for anything else in your life.**

##### Parts List

* 3.3 V capable Serial to USB adapter ([Link](https://www.amazon.com/Micro-Basic-Breakout-Module-Arduino/dp/B00N4MCS1A))
* Old floppy disk drive power connector
* NPN transistor (such as 2N3904)
* 10 kOhm resistors (x3)
* 100 kOhm resistor (x1)

The finished product

<br />
<img src="/projects/vyper-cable/cable-and-computer.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

So fancy

<br />
<img src="/projects/vyper-cable/cable.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

Oh yeah that fits nice

<br />
<img src="/projects/vyper-cable/connection.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

Grind down the connector a bit in two places so the wire can be more flush.

<br />
<img src="/projects/vyper-cable/connector.jpg" alt=""  style="width:300px" class="img-responsive"/>
<br />

Apparently the computer uses negative voltage for logic high (at least according to this one place on the internet, I'm not actually sure they are correct, but this works so I'm just going with it for now). With the computer face down and the two pin data port facing you, common is on the right and the I/O pin is on the left.

<br />
<img src="/projects/vyper-cable/circuit.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

There is an initial burst of data being sent to the vyper and then the rest is data being sent from the vyper. 

<br />
<img src="/projects/vyper-cable/scope-output.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

