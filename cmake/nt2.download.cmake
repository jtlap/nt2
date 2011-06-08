################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

macro(nt2_download_module module)
  string(TOUPPER ${module} module_U)

  if(NOT NT2_FIND_REPOSITORIES AND DEFINED ENV{NT2_FIND_REPOSITORIES})
    set(NT2_FIND_REPOSITORIES $ENV{NT2_FIND_REPOSITORIES})
  elseif(NOT NT2_FIND_REPOSITORIES)
    set(NT2_FIND_REPOSITORIES git://github.com/MetaScale/nt2-modules.git)
  endif()

  find_package(Git QUIET)
  if(GIT_FOUND)
    set(repo_found 0) 
    foreach(repo ${NT2_FIND_REPOSITORIES})
      if(NOT repo_found)
        message(STATUS "[nt2] looking for module ${module} on ${repo}...")
        execute_process(COMMAND ${GIT_EXECUTABLE} ls-remote --heads ${repo} ${module}
                        OUTPUT_VARIABLE ls_remote_out
                        OUTPUT_STRIP_TRAILING_WHITESPACE
                       )
                     
        if(ls_remote_out)
          set(repo_found 1)
          message(STATUS "[nt2] downloading module ${module} from ${repo}...")
          execute_process(COMMAND ${GIT_EXECUTABLE} clone ${repo} --branch ${module} ${module}
                          WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/modules
                         )
          set(NT2_${module_U}_ROOT ${PROJECT_SOURCE_DIR}/modules/${module})
        endif()
        
      endif()
    endforeach()
  endif()
endmacro()
