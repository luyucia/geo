dnl $Id$
dnl config.m4 for extension geo

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(geo, for geo support,
Make sure that the comment is aligned:
[  --with-geo             Include geo support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(geo, whether to enable geo support,
dnl Make sure that the comment is aligned:
dnl [  --enable-geo           Enable geo support])

if test "$PHP_GEO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-geo -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/geo.h"  # you most likely want to change this
  dnl if test -r $PHP_GEO/$SEARCH_FOR; then # path given as parameter
  dnl   GEO_DIR=$PHP_GEO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for geo files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GEO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GEO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the geo distribution])
  dnl fi

  dnl # --with-geo -> add include path
  dnl PHP_ADD_INCLUDE($GEO_DIR/include)

  dnl # --with-geo -> check for lib and symbol presence
  dnl LIBNAME=geo # you may want to change this
  dnl LIBSYMBOL=geo # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GEO_DIR/$PHP_LIBDIR, GEO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GEOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong geo lib version or lib not found])
  dnl ],[
  dnl   -L$GEO_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GEO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(geo, geo.c, $ext_shared)
fi
