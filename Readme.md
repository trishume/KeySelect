# KeySelect

An app that uses libccv to do the stroke width transform on a screenshot of your screens current state.
It then identifies a prevailing text grid.

It uses Qt and some OSX specific code (but not much) to do overlays and mouse control.
It includes a statically linked libccv library built for OSX using clang.
You might have to compile libccv yourself and put your own lib in there, I really should have a better system for this.

## Status

Currently a total hack, code is terrible, interface is terrible/non-existent. The reason for this is that it was written in 6 hours for Waterloo's SE Hack Day.

## Interface

Currently driven through a debug window. Take a screenshot, process it, use VIM keybinds or arrow keys to move your cursor around the grid, then hold space and move the cursor to select some text.

## Screenshot

![Screenshot](http://i.imgur.com/Iz6uFOR.jpg)
