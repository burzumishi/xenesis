# XENESIS

[https://github.com/burzumishi/xenesis] (https://github.com/burzumishi/xenesis)

```
Copyright © 2014 Antonio Cao (@burzumishi)

This is free software;
You have unlimited permission to copy and/or distribute it,
with or without modifications, as long as this notice is preserved.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY, to the extent permitted by law; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
```

**Xenesis** is a remote task manager, it will help you on manage and
schedule tasks on remote hosts conected to the same network over SSH.

**Xenesis** is a shell script and uses basic shell tools, it's simple and fully customizable!

Administrators will execute tasks on remote hosts with a single command line.

Remote administration of tasks, is done trought Remote Admin Layer (RAL) Plugins.


Releases
--------

**[ There are NO WORKING RELEASES yet! ]**

Check out the latest working [Xenesis Releases] (https://github.com/burzumishi/xenesis/releases)


Features
--------

 - GNU AutoTools Support.
 - Terminal Color Support.
 - Dinamic Configuration Files Support (conf.d).
 - Remote Admin Layer (RAL) Plugin Support.
 - Dinamic Host List scripts.


Install
-------

**Xenesis** is using **GNU AutoTools**, as build system.

**Xenesis** is a shell script, but it needs to be built and setup some strings to be installed on your host system.

Type the following commands to install:

```
sh autogen.sh
./configure --prefix=/usr
make
make install
```


Supported OS
------------

Linux, CygWin, HP-UX, FreeBSD, and maybe more. ;)


Authors
-------

Antonio Cao ([@burzumishi] (https://github.com/burzumishi))


