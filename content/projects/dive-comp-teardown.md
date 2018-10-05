+++
draft = false
date = "2018-09-29T11:26:38-07:00"
title = "Dive Computer Teardown"
showonlyimage = false
image = "projects/dive-comp-teardown/front.jpg"

+++

Taking a look at the guts of a computer designed to work over 100 ft underwater.
<!--more-->

I recently took out my old Genesis ReSource dive computer to see if it still worked. While a fresh set of batteries did induce it to turn on, it insisted on shutting down right after a brief LCD test cycle. I looked online to see if anyone had info on the hardware in the computer and I discovered a rather appalling lack of dive computer teardowns. Obviously the only course of action was to take mine apart and see the insides for myself.


The outer ring slid off easily enough.

<br />
<img src="/projects/dive-comp-teardown/outer-ring.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

Removing the battery cover turned out not to be necessary but I didn't know that at the time.

<br />
<img src="/projects/dive-comp-teardown/back.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/battery-compartment.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

This was the hard part. The clear shell has internal threads that a ring which fits over the sandwich of the screen, circuitboard and back section screws into. I had to pry the edge up all the way around to break the glue, and then I managed to stab a flathead screwdriver rather deeply into my finger which trying to exert enough torque to unscrew things. What ended up working was banging on the back of the screwdriver with a hammer as I held it angled down into one of the 4 small indents and at a tangent to the circle of rotation.

<br />
<img src="/projects/dive-comp-teardown/outer-shell-a.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/outer-shell-b.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

Here you can see the zebra strip along the bottom of the screen and the corresponding contact points on the circuit board. I was sad to see that two of the ICs were blobbed over.

<br />
<img src="/projects/dive-comp-teardown/circuit-and-screen.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

The two large contact areas on the back of the circuit board get pressed against the battery contacts.

<br />
<img src="/projects/dive-comp-teardown/circuit-and-back.jpg" alt=""  style="width:500px" class="img-responsive"/>
<br />

If you look closely, you can see a bodge resistor on the far right edge.

<br />
<img src="/projects/dive-comp-teardown/circuit-front-full.jpg" alt=""  style="width:600px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/circuit-front-full-labeled.png" alt=""  style="width:400px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/circuit-front-close-a.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/circuit-front-close-b.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

<br />
<img src="/projects/dive-comp-teardown/circuit-front-close-c.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

The metal can thing at the top is the pressure sensor which is exposed to the water via the three small holes visible in the pictures of the back of the computer. The large component in the upper right is a 470 uH inductor. Also visible are a few capacitors and what I'm guessing is a crystal oscillator.

<br />
<img src="/projects/dive-comp-teardown/circuit-back-full.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

The inductor is connected to pin 4 of the mystery IC.

<br />
<img src="/projects/dive-comp-teardown/circuit-back-close.jpg" alt=""  style="width:400px" class="img-responsive"/>
<br />

I measure the logic voltage level to be 4.5 V, so I suspect the mystery IC with the inductor is a step down switching DC-DC converter since the 6 volts from the batteries must be getting stepped down somewhere.

I believe this computer was originally purchased at some point in the 90's and I don't know how similar modern dive computers are, but they still need to do all the same things so probably not that different. I hope this will be interesting to someone and if you know what that mystery IC is, shoot me an email!

