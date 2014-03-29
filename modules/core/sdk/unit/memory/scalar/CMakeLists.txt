##############################################################################
###   Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
###   Copyright 2012 - 2014 MetaScale SAS
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  splat.cpp
   )

nt2_module_add_tests(core.sdk.memory.scalar.unit ${SOURCES})
