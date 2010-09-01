#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for creating guards for C, C++ header files
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import os
import re
import logging
from re_list  import sub_list

class Guard :
    """create nt2 guards for a C, C++ include file
    """

    begin_text_template = [
        "#ifndef <path>_INCLUDED",
        "#define <path>_INCLUDED",
        ]
    end_text_template = [
        "#endif",
        ""
        ]

    def __init__(self, path, name,
                 ext        = '.hpp',
                 verbose    = False,
                 guard_begin = None,
                 guard_end  = None
                 ) :
        self.logger = logging.getLogger("nt2.Headersguards.Guard")
        self.__path = os.path.expanduser(path)
        if self.__path[-1] != '/':
            self.__path += '/'
        self.__name = name
        self.__ext  = ext
        self.__header= None
        if self.__ext[0] != '.':  self.__ext = '.' + self.__ext
        self.__total_path = self.mk_total_path()
        if guard_begin is None :
            self.__guard_begin = Guard.begin_text_template
        else :
            self.__guard_begin = guard_begin 
        if guard_end is None :
            self.__guard_end = Guard.end_text_template
        else :
            self.__guard_end = guard_end
        self.mk_guard()

    def __str__(self) :
        return '\n'.join(self.__guard_begin+["  ..."]+self.__guard_end)

    def get_guard_begin(self) : return self.__guard_begin
    def get_guard_end(self) : return self.__guard_end
    def get_total_path(self) : return self.__total_path
    def get_ext(self) : return self.__ext

    def mk_total_path(self) :
        return self.__path + self.__name + self.__ext
    
    def mk_guard(self) :
        """create a file guard in two parts"""
        path  = re.sub('[^(A-Z|0-9)]','_',self.__total_path.upper())        
        self.__guard_begin = sub_list('<path>',path,self.__guard_begin)
#        self.__guard ={ "begin" : self.__guard_begin, "end" :self.__guard_end}
        
    def __call__(self) :
        return self.__guard

if __name__ == "__main__":
    import nt2_logs
    NT2_LOGS = nt2_logs.Nt2_logs()
    print Guard('./','ertyu')

