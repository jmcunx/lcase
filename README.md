## lcase - Change character case of each line in a text file

lcase was created for systems that lack tr(1).
All it does is change the Upper/Lower Case
of characters in a Text File.

If tr(1) is a better choice, but its command
line can be a but hard to remember.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.
For MS-DOS, it should be rather easy to create a Makefile.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
