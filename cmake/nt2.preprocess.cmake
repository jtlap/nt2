################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.info)

macro(nt2_preprocess target)
  find_file(WAVE_EXECUTABLE wave $ENV{BOOST_ROOT}/dist/bin)
  if(NOT WAVE_EXECUTABLE MATCHES "NOTFOUND$")
    get_directory_property(INCLUDES INCLUDE_DIRECTORIES)
  
    if(NT2_PROCESSOR STREQUAL x86)
      set(INCLUDE_ARCH i686)
    else()
      set(INCLUDE_ARCH ${NT2_PROCESSOR})
    endif()
    set(INCLUDE_DIRECTORIES -S/usr/lib/gcc/${INCLUDE_ARCH}-linux-gnu/4.5/include
                            -S/usr/include/c++/4.5
                            -S/usr/include/c++/4.5/${INCLUDE_ARCH}-linux-gnu
                            -S/usr/include
       )
       
    foreach(INCLUDE ${INCLUDES})
      list(APPEND INCLUDE_DIRECTORIES "-S${INCLUDE}")
    endforeach()
    set(prev 0)
    foreach(src ${ARGN})
      math(EXPR n "${prev} + 1")
      add_custom_target(${target}.${n}
                        COMMAND echo "wave ${src}" && ${WAVE_EXECUTABLE} -DNT2_DONT_USE_PREPROCESSED_FILES -DNT2_CREATE_PREPROCESSED_FILES
                        --c++0x --timer
                        ${INCLUDE_DIRECTORIES} -o - ${src}
                        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/include
                       )
      if(prev)
        add_dependencies(${target}.${n} ${target}.${prev}) # we force sequential execution
      endif()
      set(prev ${n})
    endforeach()
    add_custom_target(${target})
    add_dependencies(${target} ${target}.${prev})
    
    # Create target "preprocess" if it doesn't already exist, and make it depend on target
    get_target_property(preprocess_exists preprocess EXCLUDE_FROM_ALL)
    if(preprocess_exists MATCHES "NOTFOUND$")
      add_custom_target(preprocess)
    endif()
    add_dependencies(preprocess ${target})
  endif()
endmacro()
