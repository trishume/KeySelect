# KeySelect

An app that uses libccv to do the stroke width transform on a screenshot of your screens current state.
It then identifies a prevailing text grid.

It uses Qt and some OSX specific code (but not much) to do overlays and mouse control.
It includes a statically linked libccv library built for OSX using clang.
You might have to compile libccv yourself and put your own lib in there, I really should have a better system for this.
