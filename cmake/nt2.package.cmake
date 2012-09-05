################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(CPACK_PACKAGE_NAME "NT2")
set(CPACK_PACKAGE_VENDOR "Metascale")
set(CPACK_PACKAGE_CONTACT "Metascale <contact@metascale.org>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Numerical Template Toolbox")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.rst")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

string(REGEX REPLACE "^([^.]+)\\.([^.]+)\\.(.+)$", "\\1" CPACK_PACKAGE_VERSION_MAJOR ${NT2_VERSION})
string(REGEX REPLACE "^([^.]+)\\.([^.]+)\\.(.+)$", "\\2" CPACK_PACKAGE_VERSION_MINOR ${NT2_VERSION})
string(REGEX REPLACE "^([^.]+)\\.([^.]+)\\.(.+)$", "\\3" CPACK_PACKAGE_VERSION_PATCH ${NT2_VERSION})

set(CPACK_PACKAGE_FILE_NAME "nt2-${NT2_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY nt2)

# NSIS-specific
set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/doc/html/images\\\\nt2.png")
set(CPACK_NSIS_DISPLAY_NAME "NT2 - Numerical Template Toolbox")
set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\nt2.metascale.org")
set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\nt2.metascale.org")
set(CPACK_NSIS_CONTACT "contact@metascale.org")

set(CPACK_STRIP_FILES 1)
set(CPACK_SOURCE_STRIP_FILES 1)
set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE 1)
