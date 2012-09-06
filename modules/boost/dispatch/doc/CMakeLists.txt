################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

nt2_module_doc( boost.dispatch
                dispatch.qbk
                reference.doxyfile
                ${NT2_BINARY_DIR}/doc/html/dispatch/tags.png
              )

if(NOT IS_DIRECTORY ${NT2_BINARY_DIR}/doc/html/dispatch)
  file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/doc/html/dispatch)
endif()

add_custom_command(OUTPUT ${NT2_BINARY_DIR}/doc/html/dispatch/tags.png
                   COMMAND ${DOXYGEN_DOT_EXECUTABLE}
                   -Tpng ${CMAKE_CURRENT_SOURCE_DIR}/tags.gv
                   -o ${NT2_BINARY_DIR}/doc/html/dispatch/tags.png
                  )
