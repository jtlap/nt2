################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Display a post-configuration installation directives list
################################################################################
MESSAGE ( STATUS "
################################################################################

 NT2 is now configured.
 * If you use make or GNU make, you may run:
   - make all to build the library
   - make install to install the compiled binary and library headers on your
     system
   - make doc to build the HTML documentation
   - make examples to build the documentation examples
   - make bench to build the performance tests
   - make unit to build the unit tests
   - make cover to build the coverage tests

 * If you use Microsoft Visual C++ or XCode, you may open the IDE-specific
   project and build those targets.

 We strongly encourage you to run the Unit Tests suite at least once before
 reporting any issues or if you're installing NT2 on a yet unsupported
 platform/compiler combination.

 Build, install and other issues can be reported through our Github Issues
 tracker at http://github.com/NumScale/nt2/issues

################################################################################
        ")
