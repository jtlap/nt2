##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  caucdf.cpp
  caupdf.cpp
  cauinv.cpp 
#  caurnd.cpp
  normcdf.cpp
  normpdf.cpp
  norminv.cpp
  unifpdf.cpp
  unifcdf.cpp 
  unifrnd.cpp
  unifinv.cpp
  expcdf.cpp
  exppdf.cpp
  expinv.cpp
  gamcdf.cpp
# List of scalar test files for toolbox statistics
   )

nt2_module_add_tests(statistics.scalar.unit ${SOURCES})
