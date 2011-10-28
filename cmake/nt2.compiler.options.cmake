################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

if(NOT NT2_COMPILER_OPTIONS_INCLUDED)
set(NT2_COMPILER_OPTIONS_INCLUDED 1)

set(NT2_FLAGS_TEST "-DNT2_ASSERTS_AS_EXCEPTIONS")
set(NT2_FLAGS_BENCH "-DNT2_DISABLE_ERROR -DNDEBUG")
if(MSVC)
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} /MD /MP /Zi /D_SECURE_SCL=1 /D_ITERATOR_DEBUG_LEVEL=1 /Oxt /GF /Gm- /GS- /fp:precise /fp:except- /EHa")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} /MD /MP /D_SECURE_SCL=0 /GL /Oxt /GF /Gm- /GS- /fp:precise /fp:except- /EHs-c- /wd4530")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
  # Strict aliasing disabled due to GCC bug #50800
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -D_GLIBCXX_DEBUG=1 -fno-strict-aliasing -DBOOST_SIMD_NO_STRICT_ALIASING")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} -O3 -fomit-frame-pointer -fno-exceptions")
else()
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
set(CMAKE_CXX_FLAGS_NT2TEST ${NT2_FLAGS_TEST} CACHE STRING "Compiler flags for NT2 tests")
set(CMAKE_CXX_FLAGS_NT2BENCH ${NT2_FLAGS_BENCH} CACHE STRING "Compiler flags for NT2 benchmarks")
set_property(GLOBAL APPEND PROPERTY DEBUG_CONFIGURATIONS NT2Test)

include(options/nt2.extra.warnings)
add_definitions(${NT2_FLAGS})

if("${CMAKE_CXX_FLAGS} ${NT2_FLAGS}" MATCHES "[^ ]")
  message(STATUS "[nt2] Global flags: ${CMAKE_CXX_FLAGS} ${NT2_FLAGS}")
endif()

message(STATUS "[nt2] Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "[nt2] Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

message(STATUS "[nt2] Test flags: ${NT2_FLAGS_TEST}")
message(STATUS "[nt2] Bench flags: ${NT2_FLAGS_BENCH}")

endif()
