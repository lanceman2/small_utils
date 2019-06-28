# small_utils

small GNU/Linux utility programs

It's a bunch of small programs that aid in Web, C code development, and
other things on GNU/Linux and maybe like systems.


## Dependencies

On Debian GNU/Linux 8.6 (jessie)

```
dpkg --add-architecture i386

apt-get update

apt-get install\
 build-essential\
 gcc-multilib\
 libgnutls30\
 csh\
 libstdc++6:i386\
 libgcc1:i386\
 zlib1g:i386\
 libncurses5:i386

apt-get install\
 libgtk2.0-dev\
 libgtk2.0-doc\
 libgtk-3-dev\
 libgtk-3-doc\
 devhelp\
 sox\
 at\
 imagemagick-doc\
 imagemagick\
 graphviz-dev\
 curl\
 pkgconf\
 autoconf\
 libtool\
 automake\
 locate\
 libgnutls28-dev
```

## Build and Install

Run optionally:
````
make configure PREFIX=/MY/prefix PRE=pre
```

then:

```
make && make install
```
