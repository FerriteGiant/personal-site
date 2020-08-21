+++
title = "Mojo Toolchain"
date = "2020-08-02T13:07:43-07:00"
showonlyimage = false
image = "blogposts/mojo-toolchain/LinkImage.png"
draft = false

+++
Getting up and running with the Mojo V3 FPGA dev board on Windows 10 as of Aug 2020.
<!--more-->

This is the setup I used for going through the book "Programming FPGAs: Getting Started with Verilog."

* Download Xilinx ISE ([link](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive-ise.html))

<br />
<img src="/blogposts/mojo-toolchain/ISE-download-page.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Unzip downloaded file and locate .ova virtual machine file.
  * Xilinx_ISE_14.7_Win10_14.7_VM_0213_1\ova\14.7_VM.ova
* Download and install VirtualBox
* Load the 14.7_VM.ova into VirtualBox
* Connect the Mojo to the computer via USB and notice which COM port shows up (COM4 in my case)

<br />
<img src="/blogposts/mojo-toolchain/com-port-device-manager.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Modify VirtualBox settings as shown below to gain network access

<br />
<img src="/blogposts/mojo-toolchain/VM-network-settings.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Pipe the COM port through to the VM. The dropdown menu (set to COM1 in the image below) is the internal port which will map to the external host port entered into "Path/Address" field. ([More details](https://techtooltip.wordpress.com/2008/09/12/using-host-serial-port-from-guest-in-virtual-box/))

<br />
<img src="/blogposts/mojo-toolchain/VM-serial-port-settings.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Start VM
* Start ISE
* Help -> Manage License...
* Acquire License (see screenshots below)
  * Free Vivado/ISE Webpack License
  * Download license file "Xilinx.lic"
  * From the "Manage Licenses" tab click "Load License..."

<br />
<img src="/blogposts/mojo-toolchain/ISE-manage-license-acquire.png" alt=""  style="width:800px" class="img-responsive" />
<br />

<br />
<img src="/blogposts/mojo-toolchain/ISE-manage-license-connect-now.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Download Mojo loader program ([link](https://alchitry.com/pages/mojo-loader))

<br />
<img src="/blogposts/mojo-toolchain/mojo-loader-download-page.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Create example program in the ISE

<br />
<img src="/blogposts/mojo-toolchain/ISE-counter-program.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Generate .bit file
* Start Mojo loader (see screenshot below)

<br />
<img src="/blogposts/mojo-toolchain/mojo-loader-start.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Load the .bit file (note you will need to change the viewable file type to "*")

<br />
<img src="/blogposts/mojo-toolchain/opening-counter-bit-file.png" alt=""  style="width:800px" class="img-responsive" />
<br />

* Flash the FPGA by clicking "Load"!

