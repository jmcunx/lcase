## lcase - Change character case of each line in a text file

lcase was created for systems that lack tr(1).
All it does is change the Upper/Lower Case
of characters in a Text File.

If tr(1) is a better choice, but its command
line can be a but hard to remember.

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
