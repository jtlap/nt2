################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Load the Template Profiler if Perl is here
################################################################################

INCLUDE(FindPerl)

IF(PERL_FOUND)
MESSAGE( STATUS "[nt2] Perl found - Template profiling available." )
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/cmake/profiler)
ELSE(PERL_FOUND)
MESSAGE( STATUS "[nt2] Perl not found - Template profiling unavailable." )
ENDIF(PERL_FOUND)