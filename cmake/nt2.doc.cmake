################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# Be sure BOOST_ROOT is set so we can access the xsl/dtd files
if(NOT BOOST_ROOT)
  set(BOOST_ROOT $ENV{BOOST_ROOT})
endif()

# Find all doc related tools and files
find_package(Doxygen QUIET)
find_program(XSLTPROC_EXECUTABLE xsltproc)
find_program(QUICKBOOK_EXECUTABLE quickbook ${BOOST_ROOT}/dist/bin)
find_path(BOOSTBOOK_XSL_DIR docbook.xsl ${BOOST_ROOT}/tools/boostbook/xsl)
find_path(BOOSTBOOK_DTD_DIR boostbook.dtd ${BOOST_ROOT}/tools/boostbook/dtd)
find_path(DOCBOOK_XSL_DIR catalog.xml /usr/share/xml/docbook/stylesheet/docbook-xsl)
find_path(DOCBOOK_DTD_DIR docbookx.dtd /usr/share/xml/docbook/schema/dtd/4.2)

include(CMakeParseArguments OPTIONAL RESULT_VARIABLE CMakeParseArguments_FOUND)

# Report any missing components and setup NT2_DOCUMENTATION_ENABLED as needed
set(NT2_DOCUMENTATION_ENABLED 1 CACHE BOOL "Whether to build NT2 documentation")
if(not NT2_DOCUMENTATION_ENABLED)
  return()
endif()
foreach(arg NT2_SOURCE_ROOT NT2_BINARY_DIR
            DOXYGEN_EXECUTABLE DOXYGEN_DOT_EXECUTABLE
            XSLTPROC_EXECUTABLE QUICKBOOK_EXECUTABLE
            BOOSTBOOK_XSL_DIR BOOSTBOOK_DTD_DIR DOCBOOK_XSL_DIR DOCBOOK_DTD_DIR
            CMakeParseArguments_FOUND
       )
  if(NOT ${arg})
    message(STATUS "[nt2.doc] ${arg} not found, documentation disabled")
    set(NT2_DOCUMENTATION_ENABLED 0 CACHE BOOL "Whether to build NT2 documentation" FORCE)
    return()
  endif()
endforeach()

# Initialize catalog file, document that describes where XML namespaces are on the disk
configure_file(${NT2_SOURCE_ROOT}/cmake/boostbook/catalog.xml.in
               ${NT2_BINARY_DIR}/doc/catalog.xml
              )
set(NT2_DOC_QBK_MACRO_FILE ${NT2_SOURCE_ROOT}/doc/macros.qbk)

# Search for file in current source or binary directory (source preferred)
macro(nt2_absolute var file)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
    set(${var} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
  elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${file})
    set(${var} ${CMAKE_CURRENT_BINARY_DIR}/${file})
  else()
    set(${var} ${file})
  endif()
endmacro()

# Generate a custom command that calls xlstproc.
# Cannot call xsltproc directly due to necessity of setting up the environment.
macro(nt2_xsltproc output)
  cmake_parse_arguments(ARG "" "COMMENT;WORKING_DIRECTORY" "DEPENDS" ${ARGN})

  add_custom_command(OUTPUT ${output}
                     COMMAND ${CMAKE_COMMAND}
                     "-DXSLTPROC_EXECUTABLE=${XSLTPROC_EXECUTABLE}"
                     "-DCATALOG=${NT2_BINARY_DIR}/doc/catalog.xml"
                     "-DOUTPUT=${output}"
                     "-DARGS=\"${ARG_UNPARSED_ARGUMENTS}\""
                     -P "${NT2_SOURCE_ROOT}/cmake/nt2.xsltproc.cmake"
                     DEPENDS ${ARG_DEPENDS}
                     COMMENT ${ARG_COMMENT}
                    )
endmacro()

# Build HTML from Docbook
macro(nt2_doc_html output_dir file)
  nt2_absolute(absolute ${file}.docbook)
  get_filename_component(path ${file} PATH)

  nt2_xsltproc(${output_dir}/html/index.html
               ${BOOSTBOOK_XSL_DIR}/xhtml.xsl
               ${absolute}
               DEPENDS ${file}.docbook ${ARGN}
               COMMENT "Converting Docbook file ${file}.docbook to XHTML..."
              )
endmacro()

# Convert a Boostbook file to Docbook
macro(nt2_doc_boostbook file)
  nt2_absolute(absolute ${file}.xml)

  nt2_xsltproc(${file}.docbook
               ${BOOSTBOOK_XSL_DIR}/docbook.xsl
               ${absolute}
               DEPENDS ${file}.xml ${ARGN}
               COMMENT "Converting Boostbook file ${file}.xml to Docbook..."
              )
endmacro()

# Convert a Quickbook file to Boostbook
macro(nt2_doc_qbk file)
  nt2_absolute(absolute ${file}.qbk)
  file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${absolute})
  get_filename_component(path ${file} PATH)

  # We always build Quickbook files because we cannot reliably identify dependencies
  set(target_name target_${relative})
  string(REPLACE "/" "_" target_name ${target_name})
  add_custom_target(${target_name}
                    COMMAND ${CMAKE_COMMAND}
                            -DINPUT=${absolute} -DOUTPUT=${CMAKE_BINARY_DIR}/${relative}
                            -DMACRO_FILE=${NT2_DOC_QBK_MACRO_FILE}
                            -P ${NT2_SOURCE_ROOT}/cmake/nt2.quickbook-insert-macros.cmake
                    COMMAND ${QUICKBOOK_EXECUTABLE}
                            --input-file ${file}.qbk
                            --include-path ${CMAKE_CURRENT_SOURCE_DIR}/${path}
                            --include-path ${CMAKE_CURRENT_BINARY_DIR}/${path}
                            --output-file ${file}.xml
                    DEPENDS ${file}.qbk ${ARGN}
                    COMMENT "Converting Quickbook file ${file}.qbk to Boostbook..."
                    SOURCES ${file}.qbk
                   )

  add_custom_command(OUTPUT ${file}.xml
                     DEPENDS ${target_name}
                    )
endmacro()

# Run Doxygen and convert output to Boostbook
macro(nt2_doc_doxygen file)
  nt2_absolute(absolute ${file}.doxyfile)
  file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${absolute})

  if(NOT IS_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen)
  endif()

  get_directory_property(INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)
  set(DXY_PATH)
  foreach(include ${INCLUDE_DIRECTORIES})
    if(EXISTS ${include} OR ${include} MATCHES ${NT2_BINARY_DIR})
      set(DXY_PATH "${DXY_PATH}INCLUDE_PATH += ${include}\n")
    endif()
  endforeach()
  string(TOUPPER ${NT2_CURRENT_MODULE} NT2_CURRENT_MODULE_U)

  file(READ ${absolute} DOXYGEN_CONTENT)
  # Add proper BOOST path to this Doxygen for PP purpose
  set(DXY_PP     "SEARCH_INCLUDES=YES\nENABLE_PREPROCESSING=YES\nMACRO_EXPANSION=YES\n")
  set(DXY_PDEF   "PREDEFINED=NT2_DOXYGEN_ONLY\n")
  set(DXY_EX)
  if(EXISTS ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/examples)
    set(DXY_EX     "EXAMPLE_PATH = ${NT2_${NT2_CURRENT_MODULE_U}_ROOT}/examples\n")
  endif()
  set(DXY_TARGET "GENERATE_LATEX=NO\nGENERATE_HTML=NO\nGENERATE_XML=YES\n")
  set(DXY_XML    "XML_OUTPUT = ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen\n")
  set(DOXYGEN_CONTENT
      "${DOXYGEN_CONTENT}${DXY_EX}${DXY_PATH}${DXY_PP}${DXY_PDEF}${DXY_TARGET}${DXY_XML}"
     )

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen/doxyfile ${DOXYGEN_CONTENT})

  # We always run Doxygen because we can't reliably identify dependencies
  set(target_name target_${relative})
  string(REPLACE "/" "_" target_name ${target_name})

  add_custom_target(${target_name}
                    COMMAND ${DOXYGEN_EXECUTABLE}
                            ${CMAKE_CURRENT_BINARY_DIR}/${file}.doxygen/doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    DEPENDS ${file}.doxyfile ${ARGN}
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

  nt2_xsltproc(${file}.xml
               --stringparam boost.doxygen.header.prefix nt2
               ${BOOSTBOOK_XSL_DIR}/doxygen/doxygen2boostbook.xsl
               ${file}.doxygen/all.xml
               DEPENDS ${file}.doxygen/all.xml
               COMMENT "Converting Doxygen XML to Boostbook (${file}.xml)..."
              )
endmacro()

# Convert all files to a single Boostbook XML
macro(nt2_doc output_file)
  set(dependencies)
  set(main)

  # For each source file...
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
      nt2_doc_qbk(${file_base})
      list(APPEND dependencies ${file_base}.xml)
    elseif(ext STREQUAL ".doxyfile")
      nt2_doc_doxygen(${file_base})
      list(APPEND dependencies ${file_base}.xml)
    elseif(ext STREQUAL ".xml")
      list(APPEND dependencies ${file_base}.xml)
    else()
      list(APPEND dependencies ${e})
    endif()
  endforeach()

  # Do XInclude processing, then copy result to /doc with name of the module
  if(NOT IS_DIRECTORY ${NT2_BINARY_DIR}/doc)
    file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/doc)
  endif()

  nt2_xsltproc(${output_file}
               ${NT2_SOURCE_ROOT}/cmake/boostbook/copy.xsl
               ${main}.xml
               DEPENDS ${dependencies}
               COMMENT "XInclude processing of file ${main}.xml..."
              )
endmacro()

macro(nt2_module_doc module)
  set(output_file ${NT2_BINARY_DIR}/doc/${module}.xml)
  nt2_doc(${output_file} ${ARGN})

  add_custom_target(${module}.boostbook
                    DEPENDS ${output_file}
                   )
  nt2_module_target_parent(${module}.boostbook)

  if(NOT NT2_SOURCE_DIR)
    nt2_doc_boostbook(${module})
    nt2_doc_html(${NT2_BINARY_DIR}/doc ${module})
    add_custom_target(doc
                      COMMAND ${CMAKE_COMMAND}
                      -E copy_directory ${NT2_SOURCE_ROOT}/doc/html
                                        ${NT2_BINARY_DIR}/doc/html
                      DEPENDS ${NT2_BINARY_DIR}/doc/html/index.html
                     )
  endif()
endmacro()
