################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

list(LENGTH VAR VAR_LENGTH)
list(LENGTH VALUE VALUE_LENGTH)
if(NOT VAR_LENGTH EQUAL VALUE_LENGTH)
  message(FATAL_ERROR "nt2.env.cmake must have as many elements in VAR and VALUE")
endif()

set(i 0)
while(i LESS VAR_LENGTH)
  list(GET VAR ${i} var)
  list(GET VALUE ${i} value)
  set(ENV{${var}} ${value})
  math(EXPR i "${i} + 1")
endwhile()

execute_process(COMMAND ${COMMAND})
