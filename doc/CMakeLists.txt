################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.doc)

if(NOT NT2_DOCUMENTATION_ENABLED)
  return()
endif()

set(dependencies)
set(MODULES_LIST)
foreach(module ${NT2_MODULES})
  string(TOUPPER ${module} module_U)

  # Only add module if it's got a documentation
  if(EXISTS ${NT2_${module_U}_ROOT}/doc/CMakeLists.txt)
    set(MODULES_LIST "${MODULES_LIST}[xinclude ${module}.xml]\n")
  endif()
endforeach()

# Generate qbk file containing the list of all modules
configure_file(modules.qbk.in modules.qbk)

set(MANUAL_SRC
    nt2.qbk
    preface.qbk
    developers_manual.qbk
    getting_started.qbk
    modules.qbk
   )

# Generate the xml for the manuals;
# boostbook target forces all modules to be built before
nt2_doc(doc.xml ${MANUAL_SRC} boostbook)

# Convert to Docbook and then HTML; make a doc target for HTML generation
nt2_doc_boostbook(doc)
nt2_doc_html(${NT2_BINARY_DIR}/doc doc)
add_custom_target(doc
                  COMMAND ${CMAKE_COMMAND}
                  -E copy_directory ${NT2_SOURCE_ROOT}/doc/html
                                    ${NT2_BINARY_DIR}/doc/html
                  DEPENDS ${NT2_BINARY_DIR}/doc/html/index.html
                 )
