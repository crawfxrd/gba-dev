# untitled

Embedded development targeting the Nintendo Game Boy Advance.

## Dependencies

- [CMake] >= 3.13
- [devkitPro]
- [mGBA] for running the binary

## Building

The `DEVKITPRO` and `DEVKITARM` environment variables must be set.

```sh
./configure.sh -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/
```

If a build type is not specified, CMake is configured to produce a debug build.

## Running

Pass the ELF file or GBA ROM to mGBA. If using the SDL version of mGBA, pass
a viewport size option for a better viewing experience.

```sh
mgba -2 ./build/untitled.gba
```

### Debugging

Run a debug build with a debug session. mGBA will wait for a connection on the
localhost port 2345.

```sh
mgba -g ./build/untitled
```

In another window, attach to the session. The file [`.gdbinit`][gdbinit]
specifies the binary to load debug symbols from and the remote target. GDB must
be configured to allow loading this file (`local-gdbinit`, `safe-path`).

```
$ gdb -q -iex "set auto-load safe-path ."
0x00000000 in ?? ()
(gdb) cont
Continuing.
```

## License

This software is made available under the terms of the Mozilla Public License,
version 2.0. See [LICENSE](./Licenses/MPL-2.0.txt) for details.

[CMake]: https://cmake.org/
[devkitPro]: https://devkitpro.org
[gdbinit]: https://sourceware.org/gdb/onlinedocs/gdb/gdbinit-man.html
[mGBA]: https://mgba.io/
