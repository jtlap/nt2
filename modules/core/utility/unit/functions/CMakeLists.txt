##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
#    arecatcompatible.cpp
#    class.cpp
#    disp.cpp
#    extent.cpp
#    first_last_index.cpp
#    firstnonsingleton.cpp
#    havesamesize.cpp
#    height.cpp
#    length.cpp
#    linesstride.cpp
#    nblines.cpp
#    ndims.cpp
#    numel.cpp
#    of_size.cpp
#    streaming.cpp
#    width.cpp
# List of test files for toolbox core.utility
   )

nt2_module_add_tests(core.utility.functions.unit ${SOURCES})
