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
    set(NT2_FIND_REPOSITORIES git://github.com/NumScale/nt2-modules.git)
  endif()

  find_package(Git QUIET)
  if(GIT_FOUND)

    string(REPLACE "." "/" module_path ${module})
    string(REPLACE "." ";" module_path_list ${module})

    set(module_ ${module})
    set(module_path_ ${module_path})

    set(repo_found 0)
    foreach(mod_comp ${module_path_list})
      foreach(repo ${NT2_FIND_REPOSITORIES})
        if(NOT repo_found)
          message(STATUS "[nt2] looking for module ${module} on ${repo}...")
          execute_process(COMMAND ${GIT_EXECUTABLE} ls-remote --heads ${repo} ${module_}
                          OUTPUT_VARIABLE ls_remote_out
                          OUTPUT_STRIP_TRAILING_WHITESPACE
                         )

          if(ls_remote_out)
            set(repo_found 1)
            message(STATUS "[nt2] downloading module ${module} from ${repo}...")

            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/${module_path_})
              file(RENAME ${PROJECT_SOURCE_DIR}/modules/${module_path_} ${PROJECT_SOURCE_DIR}/modules/__${module_path_})
            endif()
            execute_process(COMMAND ${GIT_EXECUTABLE} clone ${repo} --branch ${module_} ${module_path_}
                            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/modules
                           )
            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/modules/__${module_path_})
              file(GLOB files RELATIVE ${PROJECT_SOURCE_DIR}/modules/__${module_path_} ${PROJECT_SOURCE_DIR}/modules/__${module_path_}/*)
              foreach(file ${files})
                file(RENAME ${PROJECT_SOURCE_DIR}/modules/__${module_path_}/${file} ${PROJECT_SOURCE_DIR}/modules/${module_path_}/${file})
              endforeach()
              file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/modules/__${module_path_})
            endif()

            set(NT2_${module_U}_ROOT ${PROJECT_SOURCE_DIR}/modules/${module_path})
          endif()

        endif()
      endforeach()

      string(REGEX REPLACE "^(.+)+\\.[^.]+$" "\\1" module_ ${module_})
      string(REGEX REPLACE "^(.+)+/[^/]+$" "\\1" module_path_ ${module_path_})

    endforeach()
  endif()
endmacro()
