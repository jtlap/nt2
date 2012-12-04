#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for automatic generation of some nt2 header files
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2004/05/05 21:57:19 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

__all__ = ["sub_list", "sub_if_match_list"]
import re


def sub_list(pattern, repl, stringlist, count=0):
    "apply re.sub to all elements of a list"
    outlist=[]
    if type(pattern) is str :
      pattern = re.compile(pattern)
    for string in stringlist :
        outlist.append(re.sub(pattern, repl, string, count))
    return outlist

##def search_list(pattern, stringlist, flags=None):
##    "apply re.search to all elements of a list"
##    outlist=[]
##    if type(pattern) is str :
##      pattern = re.compile(pattern)
##    for string in stringlist :
##        outlist.append(re.sub(pattern, repl, string, flags))
##    return outlist

def sub_if_match_list(start, pattern, repl, stringlist, count=0, flags=None):
    "apply re.sub to all elements of a list that begin with start"
    outlist=[]
    if type(pattern) is str : pattern = re.compile(pattern)
    if type(start) is str : start = re.compile(start)
    for string in stringlist :
        if re.match(start,string) :
            outlist.append(re.sub(pattern, repl, string, count))
        else :
            outlist.append(string)
    return outlist

if __name__ == "__main__":
    from display_utils import show
    inner_text = [
        "",
        "SET( SOURCES",
        "# List of files for toolbox %s"% "gmp",
        "   )",
        "",
        "##****************************************************************************",
        "# For each filename",
        "##****************************************************************************",
        "FOREACH( EXAMPLE ${SOURCES})",
        "  ##**************************************************************************",
        "  ## Build the executable filename from the example source filename",
        "  ##**************************************************************************",
        '  STRING(REGEX REPLACE ".cpp" ".%s.scalar.bench" EXECUTABLE "${EXAMPLE}")'%("gmp",),
        '  STRING(REGEX REPLACE ".cpp" "-%s.scalar.bench" TEST "${EXAMPLE}")'%("gmp",),
        "",
        "  ##**************************************************************************",
        "  ## Add as a target",
        "  ##**************************************************************************",
        "  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})",
        "  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)",
        "  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})",
        "ENDFOREACH()",
        ]
    l=sub_if_match_list(" *##", "\*", "#", inner_text)
    show(l)

