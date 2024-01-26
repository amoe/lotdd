# lotdd

Jeff Langr -- Modern C++ Programming with Test-Driven Development

## Build Process -- Linux

This has been tested with scons version `4.5.2` from pip.  Other versions may or
may not work.

**You need to provide a Mapquest API key in the local gitignored file,
`.mapquest_api_key`, in the repository root.**

To build, you need to define `googletest_framework_root` in the SConscript file.

You also need to install `libjsoncpp-dev`.  The include files location are
detected using `pkg-config`.

You need `libboost-date-time-dev` for the date classes.

When adding a new chapter directory you must nuke the entire `build` directory
otherwise SCons won't pick up the new one.  Not sure why at the moment.

We decided not to use LSP-mode on this, even after switching it to build using
clang, because the build system is too complex to interface it with clangd's
configuration.

The SCons version that has been tested is SCons 4.5.2

## Build Process -- Mac

    pip3 install --user scons==4.5.2

With later versions of pip (>21ish), pip recommends against using global
installations.  So you can satisfy its neediness by using the `--user` flag
here.  Hopefully, you have `~/.local/bin` setup in your PATH.

## Adding a new example directory

Each new example also needs its own test driver file, which is named `main.cc`,
and should read as follows:

    #include <gmock/gmock.h>

    int main(int argc, char **argv) {
        testing::InitGoogleMock(&argc, argv);
        return RUN_ALL_TESTS();
    }


## Author's conventions

Langr uses a 3-space indent in his code archive, which is rather satanic.

He also likes to use the `_` suffix to distinguish member variables.  We also
follow that convention here.  It makes it easier to avoid name clashes,
especially since we use `camelCase` for member function names where Langr does
not.

## Logging

At chapter 8, Langr wants to use logging.  He chooses the "rlog" library.  I
couldn't find where this is available.  I chose spdlog instead, because I already
know how to link with this.  You can install it with `libspdlog-dev` on Debian.

## Errata

Errata for the book are located here:
https://pragprog.com/cms/errata/lotdd-errata/

You can find Langr's solutions in the file named `lotdd-code.tgz`.
