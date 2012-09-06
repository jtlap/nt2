################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

file(READ ${INPUT} content)

string(LENGTH "${content}" len)
set(expanded 0)
string(FIND "${content}" "[" pos)

set(i 0)
if(NOT pos LESS 0)
  set(expanded 1)
  math(EXPR i "${pos}+1")
  while(i LESS ${len} AND ${expanded} GREATER 0)
    string(SUBSTRING "${content}" ${i} 1 c)
    if(c STREQUAL "[")
      math(EXPR expanded "${expanded}+1")
    elseif(c STREQUAL "]")
      math(EXPR expanded "${expanded}-1")
    endif()
    math(EXPR i "${i}+1")
  endwhile()
endif()

math(EXPR sz "${len}-${i}")
string(SUBSTRING "${content}" 0 ${i} before)
string(SUBSTRING "${content}" ${i} ${sz} after)
file(READ ${MACRO_FILE} middle)
string(STRIP "${middle}" middle)

file(WRITE ${OUTPUT} "${before}\n\n${middle}${after}")
