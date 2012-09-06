################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Load the Template Profiler if Perl and Boost.Regex are found
################################################################################

find_package(Perl)
find_package(Boost 1.49.0 COMPONENTS regex)

if(PERL_FOUND AND Boost_FOUND)
  message( STATUS "[nt2] Template profiling available." )
  include(profiler/profiler)
else()
  message( STATUS "[nt2] Template profiling unavailable." )
endif()
