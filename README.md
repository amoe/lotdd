# lotdd

Jeff Langr -- Modern C++ Programming with Test-Driven Development

## Build Process

**You need to provide a Mapquest API key in the local gitignored file,
`.mapquest_api_key`, in the repository root.**

To build, you need to define `googletest_framework_root` in the SConscript file.

You also need to install `libjsoncpp-dev`.  The include files location are
detected using `pkg-config`.

When adding a new chapter directory you must nuke the entire `build` directory
otherwise SCons won't pick up the new one.  Not sure why at the moment.

## Author's conventions

Langr uses a 3-space indent in his code archive, which is rather satanic.

He also likes to use the `_` suffix to distinguish member variables.

## Errata

Errata for the book are located here:
https://pragprog.com/cms/errata/lotdd-errata/

