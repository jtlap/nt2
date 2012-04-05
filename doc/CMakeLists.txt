################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.doc)

if(NT2_DOCUMENTATION_ENABLED)
  # Locally build the xml catalog
  configure_file( ${NT2_SOURCE_ROOT}/cmake/boostbook/catalog.xml.in
                  ${NT2_BINARY_DIR}/catalog.xml
                )

  set(dependencies)
  set(xinclude)
  foreach(module ${NT2_MODULES})
    # Find the canonical place where xml files are for a given doc
    set(doc_source ${NT2_SOURCE_DIR}/modules/${module}/doc)
    set(doc_output ${NT2_BINARY_DIR}/modules/${module}/doc)

    if(IS_DIRECTORY ${doc_source})
      # Glob every xml in there
      set(dependencies "${doc_output}/${module}.xml;${dependencies}")
      set(xinclude "${xinclude}[xinclude ${doc_output}/${module}.xml]\n")
    endif()
  endforeach()

  message(STATUS "${xinclude}")

  set ( MANUAL_SRC
        nt2.qbk
        preface.qbk
        developers_manual.qbk
        getting_started.qbk
      )

  nt2_doc_generate(manual ${MANUAL_SRC})

  # Build the docbook and HTML
  nt2_doc_boostbook(nt2 nt2.xml ${dependencies})
  nt2_doc_html(doc nt2)
endif()
