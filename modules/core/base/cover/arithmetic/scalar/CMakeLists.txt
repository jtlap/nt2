
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
abs.cpp
adds.cpp
arg.cpp
average.cpp
ceil.cpp
correct_fma.cpp
dist.cpp
divceil.cpp
divfix.cpp
divfloor.cpp
divround.cpp
divs.cpp
fast_hypot.cpp
floor.cpp
fma.cpp
hypot.cpp
iceil.cpp
idivceil.cpp
idivfix.cpp
idivfloor.cpp
idivround.cpp
ifloor.cpp
iround.cpp
isqrt.cpp
logical_xor.cpp
max.cpp
minmod.cpp
minusone.cpp
min.cpp
mod.cpp
muls.cpp
negs.cpp
oneminus.cpp
oneplus.cpp
random.cpp
rec.cpp
remainder.cpp
remquo.cpp
rem.cpp
round.cpp
rsqrt.cpp
sqr.cpp
subs.cpp
tofloat.cpp
toint.cpp
toints.cpp
trunc.cpp
two_add.cpp
two_prod.cpp
two_split.cpp

# List of scalar test files for toolbox arithmetic
   )

nt2_module_add_tests(core.base.arithmetic.scalar.cover ${SOURCES})

