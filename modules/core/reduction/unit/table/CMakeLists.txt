##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
    asum1.cpp
    asum2.cpp
    asump.cpp
    all.cpp
    any.cpp
    dot.cpp
    global.cpp
    globalall.cpp
    globalany.cpp
    globalmax.cpp
    globalmin.cpp
    globalsum.cpp
    globalprod.cpp
    maximum.cpp
#    medianad.cpp
    median.cpp
    mean.cpp
    meanad.cpp
    minimum.cpp
    none.cpp
    norm2.cpp
    normp.cpp
    prod.cpp
    sum.cpp
    var.cpp
    wmean.cpp
    nansum.cpp
    nanmean.cpp
    nanasum2.cpp
# List of test files for toolbox core.reduction
   )

nt2_module_add_tests(core.reduction.table.unit ${SOURCES})
