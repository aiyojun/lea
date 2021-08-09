# directory bin

This directory prepared for generated executable binary file!

## linux platform - elf

To decrease the volume of final binary file,

"lea" must have a small compiler without any other dependency.

This compiler without any dependency can generate binary file directly!

## windows platform - exe

To generate binary file for windows(.exe), "lea" can take advantage of nasm!

First, let "lea" compiler generate middle language file of nasm.

Then, we can generate .exe file by using nasm compiler.