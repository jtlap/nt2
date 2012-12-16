################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.doc)

set(MANUAL_SRC
  nt2.qbk
    news.qbk
    getting_started.qbk
      started/setup.qbk
      started/tutorial.qbk
    users_manual.qbk
      user/containers.qbk
      user/tutorial.qbk
      user/faq.qbk
    tools.qbk
      tools/cmake.qbk
      tools/build.qbk
    developers_manual.qbk
      dev/module.qbk
      dev/expression.qbk
      dev/architecture.qbk
      dev/tutorial.qbk
      dev/faq.qbk
    appendix.qbk
      appendix/authors.qbk
      appendix/license.qbk
      appendix/bibliography.qbk
      appendix/acknowledgement.qbk
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
