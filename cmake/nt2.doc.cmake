################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
## Be sure BOOST_ROOT is set so we can access the xsl/dtd files
################################################################################
if(NOT BOOST_ROOT)
  set(BOOST_ROOT $ENV{BOOST_ROOT})
endif()

################################################################################
## Find all doc related tools and files
################################################################################
find_program(DOXYGEN_EXECUTABLE doxygen)
find_program(XSLTPROC_EXECUTABLE xsltproc)
find_program(QUICKBOOK_EXECUTABLE quickbook ${BOOST_ROOT}/dist/bin)
find_path(BOOSTBOOK_XSL_DIR docbook.xsl ${BOOST_ROOT}/tools/boostbook/xsl)
find_path(BOOSTBOOK_DTD_DIR boostbook.dtd ${BOOST_ROOT}/tools/boostbook/dtd)
find_path(DOCBOOK_XSL_DIR catalog.xml /usr/share/xml/docbook/stylesheet/docbook-xsl)
find_path(DOCBOOK_DTD_DIR docbookx.dtd /usr/share/xml/docbook/schema/dtd/4.2)

include(CMakeParseArguments OPTIONAL RESULT_VARIABLE CMakeParseArguments_FOUND)

################################################################################
## Report any missing components and setup NT2_DOCUMENTATION_ENABLED as needed
################################################################################
set(NT2_DOCUMENTATION_ENABLED 1)
foreach ( arg DOXYGEN_EXECUTABLE XSLTPROC_EXECUTABLE QUICKBOOK_EXECUTABLE
              BOOSTBOOK_XSL_DIR BOOSTBOOK_DTD_DIR DOCBOOK_XSL_DIR DOCBOOK_DTD_DIR
              CMakeParseArguments_FOUND
        )
  if(NOT ${arg} AND NT2_DOCUMENTATION_ENABLED)
    message(STATUS "[nt2.doc] ${arg} not found, documentation disabled")
    set(NT2_DOCUMENTATION_ENABLED 0)
  endif()
endforeach()

################################################################################
## Past this point, we consider the Documentation as enabled
################################################################################

################################################################################
## Compute the absolute path of a given file
################################################################################
macro(nt2_absolute var file)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
    set(${var} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
  elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${file})
    set(${var} ${CMAKE_CURRENT_BINARY_DIR}/${file})
  else()
    set(${var} ${file})
  endif()
endmacro()

################################################################################
## Build a xlstproc command invocation
################################################################################
macro(nt2_xsltproc output)
  cmake_parse_arguments(ARG "" "COMMENT;WORKING_DIRECTORY" "DEPENDS" ${ARGN})

  add_custom_command( OUTPUT ${output}
                      COMMAND ${CMAKE_COMMAND}
                      "-DXSLTPROC_EXECUTABLE=${XSLTPROC_EXECUTABLE}"
                      "-DCATALOG=${CMAKE_BINARY_DIR}/catalog.xml"
                      "-DOUTPUT=${output}"
                      "-DARGS=\"${ARG_UNPARSED_ARGUMENTS}\""
                      -P "${NT2_SOURCE_ROOT}/cmake/nt2.xsltproc.cmake"
                      DEPENDS ${ARG_DEPENDS}
                      COMMENT ${ARG_COMMENT}
                    )
endmacro()

################################################################################
## Build the HTML from a .docbook
################################################################################
macro(nt2_doc_html target file)
  nt2_absolute(absolute ${file}.docbook)
  get_filename_component(path ${file} PATH)

  nt2_xsltproc(${NT2_BINARY_DIR}/doc/${file}/html/index.html
               ${BOOSTBOOK_XSL_DIR}/xhtml.xsl
               ${absolute}
               DEPENDS ${file}.docbook
               COMMENT "Converting Docbook file ${file}.docbook to XHTML..."
              )

  add_custom_target(${target}
                    COMMAND ${CMAKE_COMMAND}
                    -E copy_directory ${NT2_SOURCE_ROOT}/doc/html
                                      ${NT2_BINARY_DIR}/doc/${file}/html
                    DEPENDS ${NT2_BINARY_DIR}/doc/${file}/html/index.html
                   )
endmacro()

################################################################################
## Process a set of separate XML files as a single Boostbook XML
################################################################################
macro(nt2_doc_boostbook file)
  nt2_absolute(absolute ${file}.xml)

  nt2_xsltproc(${file}.docbook
               #--stringparam boost.header.root file://${CMAKE_CURRENT_SOURCE_DIR}/include
               ${BOOSTBOOK_XSL_DIR}/docbook.xsl
               ${absolute}
               DEPENDS ${ARGN}
               COMMENT "Converting Boostbook file ${file}.xml to Docbook..."
              )
endmacro()

################################################################################
## Produce the main doc target
################################################################################
macro(nt2_doc)
  if(NT2_DOCUMENTATION_ENABLED)
    # Locally build the xml catalog
    configure_file( ${NT2_SOURCE_ROOT}/cmake/boostbook/catalog.xml.in
                    ${NT2_BINARY_DIR}/catalog.xml
                  )

    set(dependencies)
    foreach(module ${NT2_MODULES})
      # Find the canonical place where xml fiels are for a given doc
      set(doc_source ${NT2_BINARY_DIR}/modules/${module}/doc)

      if(IS_DIRECTORY ${doc_source})
        # Glob every xml in there
        file(GLOB xml_files RELATIVE ${NT2_BINARY_DIR} "${doc_source}/*.xml")
        list(APPEND dependencies ${xml_files})
      endif()
    endforeach()

    set(xinclude)
    foreach(file ${dependencies})
      # Generate a chain of [xinclude ${xml_files}] to add to dev.qbk
      set(xinclude "${xinclude}[xinclude ${file}]\n")
    endforeach()

    message(STATUS "${xinclude}")

    # Build root files for the doc
    nt2_doc_generate(manual nt2.qbk)

    # Build the docbook and HTML
    nt2_doc_boostbook(nt2 ${dependencies})
    nt2_doc_html(doc nt2)
  endif()

endmacro()

################################################################################
## Process a qbk file and convert it to BoostBook XML format
################################################################################
macro(nt2_doc_process_qbk file output_dir)
  nt2_absolute(absolute ${file}.qbk)
  file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${absolute})
  get_filename_component(path ${file} PATH)

  # We always build Quickbook files because we cannot reliably identify dependencies
  set(target_name target_${relative})
  string(REPLACE "/" "_" target_name ${target_name})

  # The custom target will :
  #  - copy the qbk in the binary directory
  #  - process it using quickbook
  add_custom_target(${target_name}
                    COMMAND ${CMAKE_COMMAND}  -E copy_if_different
                            ${absolute} ${CMAKE_BINARY_DIR}/${relative}
                    COMMAND ${QUICKBOOK_EXECUTABLE}
                            --input-file ${file}.qbk
                            --include-path ${CMAKE_CURRENT_SOURCE_DIR}/${path}
                            --include-path ${CMAKE_CURRENT_BINARY_DIR}/${path}
                            --output-file ${output_dir}/${file}.xml
                   DEPENDS ${file}.qbk
                   COMMENT "Converting Quickbook file ${file}.qbk to Boostbook..."
                   SOURCES ${file}.qbk
                   )

  add_custom_command(OUTPUT ${output_dir}/${file}.xml
                     DEPENDS ${target_name}
                    )
endmacro()

################################################################################
## Process a raw xml file and move it where everything lives
################################################################################
macro(nt2_doc_process_xml file output_dir)
  nt2_absolute(absolute ${file}.xml)
  file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${absolute})

  # The custom target will copy the xml in the binary directory
  set(target_name target_${relative})
  string(REPLACE "/" "_" target_name ${target_name})
  add_custom_target(${target_name}
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                            ${absolute} ${output_dir}/${file}.xml
                    DEPENDS ${file}.xml
                    COMMENT "Gathering ${file}.xml BoostBook ..."
                    SOURCES ${file}.xml
                   )

  add_custom_command(OUTPUT ${output_dir}/${file}.xml
                     DEPENDS ${target_name}
                    )
endmacro()

################################################################################
## Process a doxyfile file and convert it to BoostBook XML format
################################################################################
macro(nt2_doc_process_doxygen file output_dir)
  nt2_absolute(absolute ${file}.doxyfile)
  file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${absolute})

  if(NOT IS_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen)
  endif()

  file(READ ${absolute} DOXYGEN_CONTENT)
  set(DOXYGEN_CONTENT ${DOXYGEN_CONTENT}
      "QUIET                  = NO\n"
      "GENERATE_LATEX         = NO\n"
      "GENERATE_HTML          = NO\n"
      "GENERATE_XML           = YES\n"
      "XML_OUTPUT             = ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen\n"
     )

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen/doxyfile ${DOXYGEN_CONTENT})

  # We always run Doxygen because we can't reliably identify dependencies
  set(target_name target_${relative})
  string(REPLACE "/" "_" target_name ${target_name})

  add_custom_target(${target_name}
                    COMMAND ${DOXYGEN_EXECUTABLE}
                            ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen/doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    DEPENDS ${file}.doxyfile
                    COMMENT "Running doxygen with XML output on ${file}.dox..."
                    SOURCES ${file}.doxyfile
                   )

  add_custom_command(OUTPUT ${file}.doxygen/index.xml
                     DEPENDS ${target_name}
                    )

  nt2_xsltproc(${file}.doxygen/all.xml
               ${file}.doxygen/combine.xslt
               ${file}.doxygen/index.xml
               DEPENDS ${file}.doxygen/index.xml
               COMMENT "Combining Doxygen XML output..."
              )

  nt2_xsltproc(${output_dir}/${file}.xml
               --stringparam boost.doxygen.header.prefix nt2
               ${BOOSTBOOK_XSL_DIR}/doxygen/doxygen2boostbook.xsl
               ${file}.doxygen/all.xml
               DEPENDS ${file}.doxygen/all.xml
               COMMENT "Converting Doxygen XML to Boostbook (${file}.xml)..."
              )
endmacro()

################################################################################
## Build all xml's requried for a moduel documentation
################################################################################
macro(nt2_doc_generate module)
  # Build the xml final output directory
  set(output_dir "${CMAKE_CURRENT_BINARY_DIR}")

  # Prepare variables holding list of stuff to process
  set(dependencies)
  set(main)

  # For each sources files ...
  foreach(e ${ARGN})
    get_filename_component(ext ${e} EXT)
    get_filename_component(path ${e} PATH)
    get_filename_component(name ${e} NAME_WE)
    if(path)
      set(file_base ${path}/${name})
    else()
      set(file_base ${name})
    endif()

    if(NOT main)
      set(main ${file_base})
    endif()

    # Select the way to process it depending on its extension
    if(ext STREQUAL ".qbk")
      nt2_doc_process_qbk(${file_base} ${output_dir})
    elseif(ext STREQUAL ".doxyfile")
      nt2_doc_process_doxygen(${file_base} ${output_dir})
    elseif(ext STREQUAL ".xml")
      nt2_doc_process_xml(${file_base} ${output_dir})
    else()
      message(FATAL_ERROR "file ${e} is not a Quickbook, Doxygen or Boostbook file")
    endif()

    list(APPEND dependencies ${output_dir}/${file_base}.xml)
  endforeach()

  # Build the local module doc target
  add_custom_target ( ${module}.doc
                      DEPENDS ${dependencies}
                      COMMENT "Processing ${module} documentation ..."
                    )
endmacro()
