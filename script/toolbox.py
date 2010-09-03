#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for creating nt2 toolboxes templates
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import os
import sys
import string
import re
import logging
from file_utils    import write, exist, mkdir
from headerfiles   import Headers
from nt2_base      import Nt2


class Toolbox(Nt2) :
    """create prerequisites for defining an nt2 toolbox
    """

    def __init__(self, tool_box_name,
                 mode = 'create',
                 p2nt2 = None,
                 style = 'usr') :
        """creation or recovery of a toolbox
         <tool_box_name> is the name of the toolbox

         <mode> is the opening mode. Proper modes are create(default) or modify

             create : creates a new toolbox tree under .../nt2/toolbox/
                  with the given <tool_box_name> provided that a 
                  directory of this name not existed previously (default)
             modify : creates a new toolbox tree or allow access to an
                  existing one to add or suppress functors extensions

          <p2nt2> is the path to nt2. The path defaults to the computation 
                  furnished by the Nt2 class
          <style> determines if the functors defined in the toolbox functors
                  will reside in the namespace nt2 ('sys') or in the namespace
                  <tool_box_name> ('usr'). It is only needed when mode is  
                  'create' and is 'usr' by default. The other modes recover
                  the creation parameter from existing data: in the present
                  implementation, once created the toolbox mode cannot be
                  modified.
        """
        Mode = [ 'create', 'modify', 'update', 'check' ]
        Style = ['usr','sys']
        Nt2.__init__(self,'toolbox')
        self.__status = True
        self.logger = logging.getLogger("nt2.toolbox.Toolbox")
        if p2nt2 is None : p2nt2 = self.get_path2nt2()
        self.__tb_name     = tool_box_name
        self.__tb_pathfnt2 = os.path.join(self.get_pathfnt2(),self.__tb_name)
        self.__tb          = os.path.join(self.get_path2nt2(),self.__tb_pathfnt2)
        self.__tb_path2mode= os.path.join(self.get_path2nt2(),self.get_pathfnt2())
        self.__tb_style = style if style == "sys" else "usr"
        self.__tb_namespace = "functors" if self.__tb_style == "sys" else self.__tb_name 
##          print "----------------------------"
##        print self.get_pathfnt2()
##        print self.get_path2nt2()
##        print self.__tb_pathfnt2
##        print self.__tb
##        print self.__tb_path2mode
##          print "----------------------------"
        
        self.__test_status = True
        self.__mode = mode
        if mode in Mode :
            self.logger.info(
                "\nopening toolbox %s with mode '"% self.__tb_name +
                mode+"'\nin directory\n" +
                self.__tb
                )
            action = getattr(self,mode+'_arbo')
            action()
        else:
            self.logger.error(
                "\nopening with unknown mode: "+mode+"\n"+
                " raising SystemExit\n"
                )
            raise SystemExit
            
    def get_tb_name(self) : return self.__tb_name
    def get_tb_pathfnt2(self) : return self.__tb_pathfnt2
    def get_tb(self) : return self.__tb 
    def get_tb_path2mode(self) : return self.__tb_path2mode
    def get_status(self) : return self.__status
    def get_tb_style (self) : return self.__tb_style
    def get_tb_namespace(self) : return self.__tb_namespace
    def get_tb_mode(self) : return self.__mode
    
    def __str__(self) :
        if not self.check_arbo() :
            l=[ ("Toolbox %s " % self.__tb_name),
                ("Created on %s" % self.__tb)]
        else :
            l=[ ("Non existing Toolbox %s " % self.__tb_name),
                ("To be created on %s" % self.__tb)]
        return '\n'.join(l)

    def __mkdir(self,base,local="",*var) :
        d = self.get_path2nt2()+base+local+'/'
        mkdir(d)

    def __mkdir_if(self,base,local="",*var) :
        d = self.get_path2nt2()+base+local+'/'
        if not exist(d) : mkdir(d)

    def __test (self,base,local,*var) :
        d = self.get_path2nt2()+base+local+'/'
        test = exist(d)
        self.logger.info(
            "\ndirectory\n %s \n%s exists\n" % \
            (d, ('already' if test else 'DOES NOT'))
            )
        self.__test_status &= test
        
    def traversal(self,base,arbo,func,*var):
        "base is the path from nt2 and arbo the current leaf"
        if type(arbo) is str :
            func(base,arbo)
        elif type(arbo) is list :
            for a in arbo:
                self.traversal(base,a,func,arbo)
        elif type(arbo) is dict :
            for k in arbo:               
                func(base,k,arbo)
                self.traversal(base+k+'/',arbo[k],func,arbo)
        else:
            self.logger.warning(
                "\nWarning: incorrect type %s, in tree descent\n" % type(arbo) +
                "with value %s\n" % str(arbo) +
                "\n"
            )
    
    def check_arbo(self) :
        "check if tree if full"
        if not os.path.exists(self.__tb) :
            return True
        else :
            self.__test_status = True;
            self.traversal(self.__tb_pathfnt2+'/',self.get_arbo(),self.__test)            
            return self.__test_status
        
    def modify_arbo(self) :
        """allow any modification on an existing toolbox tree"""
        if not os.path.exists(self.__tb) :
            self.__status = False
            self.logger.error(
                "\ntoolbox %s does not already exists\n" % self.__tb_name +
                "in path: %s\n" % self.__tb +
                "please create it before modifying\n"
                )
            raise SystemExit
        self.__tb_style = self.read_style()
        return self.__status
    
    def create_arbo(self):
        """ create a toolbox tree only if it does not exist"""
        if os.path.exists(self.__tb) :
            self.__status = False
            self.logger.error(
                "\ntoolbox %s already exists\n" % self.__tb_name +
                "in path: %s\n" % self.__tb +
                "please use another toolbox name\n" +
                "or delete the old one before creating the new one\n"
                )
            raise SystemExit
        else:
            mkdir(self.__tb)
            self.traversal(self.__tb_pathfnt2+'/',self.get_arbo(),self.__mkdir)
            self.create_toolbox_include_template()
            self.create_include_functors_template()
            self.create_toolbox_macros_template(check=True)
            self.create_toolbox_py_datas()
        return self.__status

    def update_arbo(self):
        """ create or update a toolbox tree"""
        if not os.path.exists(self.__tb) :
            return self.create_arbo()
        else :
            self.__tb_style = self.read_style()
            self.traversal(self.__tb_pathfnt2+'/',self.get_arbo(),self.__mkdir_if)
            self.create_toolbox_include_template(check=True)
            self.create_include_functors_template(check=True)
            self.create_toolbox_macros_template(check=True)
        return self.__status
        
    def create_include_functors_template(self,check=False):
        """the created file will contain the include list of functors
        immediately available from the toolbox.
        """
        self.logger.warning(
            "\ncreating include template for %s\n" % self.__tb_name
            )
        h = Headers(self.__tb_pathfnt2,'/'+self.__tb_name)
        h.write_header(path=self.get_path2nt2(),check=check)

    def create_toolbox_include_template(self,check=False):
        """the created file is the main include file for the toolboxes users.
        """
        self.logger.warning(
            "\ncreating toolbox include template for %s\n" % self.__tb_name
            )
        inner_text = [
            "#include <nt2/nt2.hpp>",
            "#include <nt2/toolbox/" + self.__tb_name + "/"+ \
             self.__tb_name + ".hpp>",
            ""
            ]
        h = Headers(self.get_pathfnt2(),self.__tb_name,
                    inner=inner_text)
        h.write_header(path=self.get_path2nt2(),check=check)

    def create_toolbox_macros_template(self,check=False):
        """the created file  include.hpp contains the BASE_<tb>... MACROS
        under toolbox/<tb>.
        """
        
        self.logger.warning(
            "\ncreating toolbox include template for %s\n" % self.__tb_name
            )
        inner_text = [
            "#include <nt2/sdk/details/preprocessor.hpp>",
            "",
            "#define NT2_$tb_nameupper$_BASE() nt2/toolbox/$tb_name$/function/scalar/",
            "#define NT2_$tb_nameupper$_RELATIVE() nt2/toolbox/$tb_name$/function/",
            "",
            "#if defined(NT2_SIMD_DETECTED)",
            "#define NT2_$tb_nameupper$_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_$tb_nameupper$_RELATIVE, F)",
            "#else",
            "#define NT2_$tb_nameupper$_INCLUDE(F) NT2_PP_INCLUDE(NT2_$tb_nameupper$_BASE, F)",
            "#endif",
            ""
            ]
        r=[]
        for l in inner_text :
            z=re.sub('\$tb_nameupper\$',self.__tb_name.upper(),l)
            z=re.sub('\$tb_name\$',self.__tb_name,z)
            r.append(z)
        h = Headers(os.path.join(self.get_pathfnt2(),self.__tb_name),"/include",inner=r)
        h.write_header(path=self.get_path2nt2(),check=check)

    def create_toolbox_py_datas(self,check=True):
        """this file contains python infos for pursuing the toolbox
           completion
        """
        
        self.logger.warning(
            "\ncreating toolbox py datas for %s\n" % self.__tb_name
            )
        inner_text = [
            "datas = {",
            "'style' : '%s'" % self.__tb_style,
            "}"
            ]
        h = Headers(os.path.join(self.get_pathfnt2(),self.__tb_name),"/py_data",
                    inner=inner_text, ext='.py')
        h.write_header(path=self.get_path2nt2(),flag='inner',check=check)
        
    def read_style(self) :
        dirname = os.path.join(self.get_path2nt2(),self.get_pathfnt2(),self.__tb_name)
        sys.path.insert(0,dirname)
        from py_data import datas
        s = datas['style']
        sys.path.pop(0)
        return s
        
if __name__ == "__main__":
    import nt2_logs
    NT2_LOGS = nt2_logs.Nt2_logs()
    if len(sys.argv)==1:
        name = "zorro"
        tb=Toolbox(name,"create")
##        print tb
##        print tb.check_arbo()
    else:
        name = sys.argv[1]
        Toolbox(name)

