# Crop JPEG files losslessly, Unicode version

(In this context, lossless means the uncropped pixels do not go thru re-encoding and therefore suffer no loss.)

This project is based on [the JpegCrop source code](https://jpegclub.org/preview/) published by [Independent JPEG Group (IJG)](https://jpegclub.org/reference/reference-sources/). I made the following changes:

* Changed code use Unicode characters so it can handle non-ANSI filenames.
* Moved project to modern SLN/VCXPROJ format, because the old DSW/DSP format is no longer supported by Visual Studio 2022.
* Patched code (mostly scope issue of loop variable) so it compiles using Visual C++ 2022.

If you want to look at the code, be warned that the GUI application really old MFC code. It looks like it was based on the 1998 version of a
MFC sample called DibLook.

I'm kind of amazed it didn't take much effort to bring it up-to-date, and it still works with today's MFC framework after some minor changes.
And the minor changes were necessary only because the original code used some internal/private MFC functions that aren't there today.

Adding Unicode support wasn't difficult, it was mostly converting many, many ANSI strings to _T() or L strings. Very tedious to
do it manually. If you are really good with regular expression, you can probably write a RE to do that,
but I just aked AI to do it and it worked.

Removed using CDocManagerEx class, which seems unneeded. But the source code files are left in the repo just in case.

