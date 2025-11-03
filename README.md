# timefmt
C function to get current time and format it in a
variety of ways.

<!-- mdtoc-start -->
&bull; [timefmt](#timefmt)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Introduction](#introduction)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [License](#license)  
<!-- TOC created by '../mdtoc/mdtoc.pl README.md' (see https://github.com/fordsfords/mdtoc) -->
<!-- mdtoc-end -->

## Introduction

The Linux "date" command supports a flexible format string.
The [strftime()](https://man7.org/linux/man-pages/man3/strftime.3.html)
function does the heavy lifting, but it is missing two things that
I wanted:
* Option to include sub-second precision (down to nanosecond).
* Option to display UTC time.

My "timefmt()" function supports these by added syntax to the format string.

* The first character of the format string must be either 'L' for local time
or 'U' for UTC time.
* The inclusion of multiple periods in a row inserts the decimal part of seconds.
The first period is printed as-is, and subsequent periods are replaced by digits.

For example, to get local time with microsecond precision, use 7 periods in a row:
````
$ ./timefmt -f "L%F %T......."
2024-05-11 14:33:34.492125
````

Here's UTC time with picosecond precision (but only nanosecond accuracy)
and the timezone offset:
````
$ ./timefmt -f "U%F %T.............%z"
2024-05-11 18:38:29.520556535000+0000
````

## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.  But "public domain" does not have an internationally agreed upon definition, so I use CC0:

This work is dedicated to the public domain under CC0 1.0 Universal:
http://creativecommons.org/publicdomain/zero/1.0/

To the extent possible under law, Steven Ford has waived all copyright
and related or neighboring rights to this work. In other words, you can 
use this code for any purpose without any restrictions.
This work is published from: United States.
Project home: https://github.com/fordsfords/timefmt
