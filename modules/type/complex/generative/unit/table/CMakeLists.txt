##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
     cic.cpp
     cif.cpp
     cols.cpp
     deltac.cpp
     deltaf.cpp
     eye.cpp
     falses.cpp
     fill_pattern.cpp
     homot.cpp
     indices.cpp
     linspace.cpp
     logspace.cpp
     ndgrid.cpp
     ones.cpp
     rephorz.cpp
     repmat.cpp
     repnum.cpp
     repvert.cpp
     ric.cpp
     rif.cpp
     rows.cpp
     trues.cpp
     zeros.cpp
   )

nt2_module_add_tests(type.complex.generative.table.unit ${SOURCES})
