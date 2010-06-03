################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Defined SPHINX_FOUND if sphinx is installed
################################################################################
FIND_PROGRAM( SPHINX_EXECUTABLE
              NAMES sphinx-build
              DOC "Sphinx documentation generator (http://sphinx.pocoo.org/)"
            )

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Sphinx DEFAULT_MSG SPHINX_EXECUTABLE)

MARK_AS_ADVANCED( SPHINX_EXECUTABLE )
