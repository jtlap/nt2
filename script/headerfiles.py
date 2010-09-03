#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for automatic generation of some nt2 header files
"""

import os
import logging
from file_utils   import write, exist
from nt2_base     import Nt2
from nt2_env      import nt2_dir
from banner       import Banner
from headerguards import Guard

class Headers(Banner,Guard) :
    """create nt2 guards for an include file
    to be written subsequentely
    given path name and
     (facultative)
    extension
    inner list of lines
    banner text
    guard begin and guard end
    
    - path is the path to the file from a selected directory (nt2)
      as nt2/toolbox/my_funcs/function/ 
    - name is the file name with no extension
    - extension may not include the .
    '.hpp' is the default file name extension

    Default usage is h=Headers(path, name)"""
    
    inner_text = [
        "",
        "//<include> please don't modify between these tags",
        "//<\include>",
        ""
        ]
  
    def __init__(self, path, name,
                 ext = '.hpp',
                 inner = None,
                 banner = None,
                 guard_begin = None,
                 guard_end = None,
                 year = None
                 ) :
        Banner.__init__(self, year, banner)
#        print " ---- path %s " % path
        Guard.__init__(self,path,name,ext,guard_begin,guard_end)
        self.__inner = Headers.inner_text if (inner is None) else inner

    def __str__(self) :
        return '\n'.join(self.get_banner()+
                         self.get_guard_begin()+
                         self.__inner+
                         self.get_guard_end())
        
    def write_header(self,path=None,check=True,flag=None):
        print "self.total %s"%self.get_total_path()
        print "path %s"%path

        path2headerfile = os.path.join(nt2_dir() if path is None else path,self.get_total_path())
        print "path2headerfile %s " % path2headerfile
        if flag is None :
            l = self.get_banner()+self.get_guard_begin()+self.__inner+self.get_guard_end()
        elif flag == 'inner' :
            l = self.__inner
        self.logger.info( "header written to:\n %s\n" % path2headerfile)
        write(path2headerfile,l,check)
    
if __name__ == "__main__":
    import nt2_logs
    NT2_LOGS = nt2_logs.Nt2_logs()
    name = "zuttique"
    path = "nt2/toolbox/t_pipo"
    inner_text = [
        "//<INCLUDE> PLEASE DON'T MODIFY BETWEEN THESE TAGS",
        "//<\INCLUDE>",
        ]
    h = Headers(path,name,inner=inner_text)
    print h
    h.write_header()  



