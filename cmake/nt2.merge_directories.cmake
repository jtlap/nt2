################################################################################
##         Copyright 2012 - 2012   MetaScale SAS
##
##          Distributed under the Boost Software License, Version 1.0.
##                 See accompanying file LICENSE.txt or copy at
##                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

if(WIN32)
  set(test_file ${CMAKE_CURRENT_BINARY_DIR}/symlinktest)
  file(TO_NATIVE_PATH ${CMAKE_CURRENT_LIST_FILE} file)
  file(TO_NATIVE_PATH ${test_file} target)
  execute_process(COMMAND cmd /C mklink ${target} ${file} OUTPUT_QUIET ERROR_QUIET)
  if(EXISTS ${test_file})
    set(HAS_SYMLINKS TRUE)
  else()
    set(HAS_SYMLINKS FALSE)
    message(STATUS "Symlinks are NOT supported.")
  endif()
elseif(UNIX)
  set(HAS_SYMLINKS TRUE)
endif()

function(merge_directory output input)

  if(NOT HAS_SYMLINKS)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${input} ${output})
    return()
  endif()

  file(GLOB files RELATIVE ${input} ${input}/*/)
  foreach(f ${files})
    if(    IS_DIRECTORY ${input}/${f}
       AND IS_DIRECTORY ${output}/${f}
      )
      if(IS_SYMLINK ${output}/${f})
        get_filename_component(f_to ${output}/${f} REALPATH)
        if(NOT ${f_to} STREQUAL ${input}/${f})
          file(REMOVE ${output}/${f})
          file(MAKE_DIRECTORY ${output}/${f})
          merge_directory(${output}/${f} ${f_to})
          merge_directory(${output}/${f} ${input}/${f})
        endif()
      else()
        merge_directory(${output}/${f} ${input}/${f})
      endif()
    else()
      if(WIN32)
        file(TO_NATIVE_PATH ${input}/${f} target)
        file(TO_NATIVE_PATH ${output}/${f} file)
        execute_process(COMMAND cmd /C mklink ${target} ${file} OUTPUT_QUIET)
      else()
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${input}/${f} ${output}/${f})
      endif()
    endif()
  endforeach()

endfunction()

get_filename_component(output_abs ${OUTPUT} REALPATH)
foreach(input ${INPUTS})
  get_filename_component(input_abs ${input} REALPATH)
  merge_directory(${output_abs} ${input_abs})
endforeach()
