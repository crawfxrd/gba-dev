untitled
========

Embedded development targeting Game Boy Advance.

Building
--------

Building requires `devkitPro <https://devkitpro.org/>`_ installed and the
``DEVKITPRO`` and ``DEVKITARM`` environment variables set.

.. code:: shell

   ./configure.sh
   cmake --build build/

Debugging
---------

Enable remote debugging in the emulator and run the binary:

.. code:: shell

   vbam -G tcp:2345 -d build/untitled.gba

In another shell, attach to the instance with gdb:

.. code:: shell

   $ arm-none-eabi-gdb -q
   (gdb) file ./build/untitled
   Reading symbols from /data/Projects/gba-dev/build/untitled...done.
   (gdb) target remote :2345
   Remote debugging using :2345
   0x08000000 in _start ()
   (gdb) cont
   Continuing.

License
-------

This software is made available under the terms of the Mozilla Public License,
version 2.0. See LICENSE for details.
