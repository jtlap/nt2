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

include(nt2.info)

set(NT2_FLAGS_TEST "-DBOOST_ENABLE_ASSERT_HANDLER -DNT2_ASSERTS_AS_EXCEPTIONS")
set(NT2_FLAGS_BENCH "-DNDEBUG")

# No debug symbols in tests because of excessive time and memory costs at compile time;
# use special debug targets instead
set(NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TEST} -DBOOST_FORCEINLINE=inline")

if(MSVC)
  # Remove /EHsc from CMAKE_CXX_FLAGS and re-add per configuration; useful to avoid 'overriding' warnings
  string(REPLACE " /EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  foreach(config Debug Release)
    string(TOUPPER ${config} config_U)
    set(CMAKE_CXX_FLAGS_${config_U} "/EHsc ${CMAKE_CXX_FLAGS_${config_U}}")
  endforeach()

  # Global MSVC settings: multithreaded + IEEE754 floating-point
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:precise /fp:except- /MP")

  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} /MDd /D_SECURE_SCL=1 /D_ITERATOR_DEBUG_LEVEL=2 /Oxt /GF /Gm- /GS- /EHa")
  set(NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG} ${CMAKE_CXX_FLAGS_DEBUG} /EHa")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} /MD /D_SECURE_SCL=0 /GL /Oxt /GF /Gm- /GS- /wd4530")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
  # Strict aliasing disabled due to GCC bug #50800
  # -D_GLIBCXX_DEBUG=1 not used because of incompatibilities with libraries
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -DBOOST_SIMD_NO_STRICT_ALIASING")
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST} -O2")
  set(NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG} -O0 -g")
  if(NT2_ARCH_X86) # valgrind doesn't support SSE4 or AVX
     set(NT2_FLAGS_TESTDEBUG "${NT2_FLAGS_TESTDEBUG} -mno-sse4.1 -mno-sse4.2 -mno-avx")
  endif()
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} -O3 -fomit-frame-pointer -fno-exceptions")
else()
  set(NT2_FLAGS_TEST "${NT2_FLAGS_TEST}")
  set(NT2_FLAGS_TESTDEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${NT2_FLAGS_TESTDEBUG}")
  set(NT2_FLAGS_BENCH "${NT2_FLAGS_BENCH} ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
set(CMAKE_C_FLAGS_NT2TEST ${NT2_FLAGS_TEST})
set(CMAKE_C_FLAGS_NT2TESTDEBUG ${NT2_FLAGS_TESTDEBUG})
set(CMAKE_C_FLAGS_NT2BENCH ${NT2_FLAGS_BENCH})
set(CMAKE_CXX_FLAGS_NT2TEST ${NT2_FLAGS_TEST})
set(CMAKE_CXX_FLAGS_NT2TESTDEBUG ${NT2_FLAGS_TESTDEBUG})
set(CMAKE_CXX_FLAGS_NT2BENCH ${NT2_FLAGS_BENCH})
set(CMAKE_EXE_LINKER_FLAGS_NT2TEST ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
set(CMAKE_EXE_LINKER_FLAGS_NT2TESTDEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
set(CMAKE_EXE_LINKER_FLAGS_NT2BENCH ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
set_property(GLOBAL APPEND PROPERTY DEBUG_CONFIGURATIONS NT2Test NT2TestDebug)

include(options/nt2.extra.warnings)

if(CMAKE_CXX_FLAGS MATCHES "[^ ]")
  message(STATUS "[nt2] Global flags: ${CMAKE_CXX_FLAGS}")
endif()

# Make sure no build type is selected
set(CMAKE_BUILD_TYPE)

message(STATUS "[nt2] Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "[nt2] Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

message(STATUS "[nt2] Test flags: ${CMAKE_CXX_FLAGS_NT2TEST}")
message(STATUS "[nt2] Test debug flags: ${CMAKE_CXX_FLAGS_NT2TESTDEBUG}")
message(STATUS "[nt2] Bench flags: ${CMAKE_CXX_FLAGS_NT2BENCH}")

endif()
