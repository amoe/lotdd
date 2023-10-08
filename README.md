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

## Build Process -- Mac

I currently recommend getting Scons 3.0.5 from pip.  You can do this as such:

    sudo pip3 install scons==3.0.5

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

## Errata

Errata for the book are located here:
https://pragprog.com/cms/errata/lotdd-errata/

You can find Langr's solutions in the file named `lotdd-code.tgz`.
