#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for creating doc files
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import sys
import os
import logging
import re
from nt2_env     import nt2_py_dir
from file_utils  import write, read
class Doc :
    """ allows to put doc files templates """
    Modes = ['add','create','update']
    Special = ['core','sdk']
    def __init__(self,path,tb) :
        self.logger = logging.getLogger("Doc")
        self.__path = os.getcwd() if path is None else os.path.expanduser(path)
        self.__mode = Doc.Modes[0]
        self.__tmpl = "just_doc.tpl"
        self.__tb   = tb
        if tb not in Doc.Special : tb = 'toolbox/'+tb
    def __str__(self) :
        return str(Sse.Variants)

    def mk_doc(self,names,path=None,mode='add',tmpl=None) :
        "making different files"
        if path is None : path=self.__path
        if tmpl is None : tmpl=self.__tmpl
        print "names %s"%names
        if mode in Doc.Modes :
            self.__mode = mode
        else :
            print "unknown mode : %s for doc creation" % mode
            print "creation aborted"
            return
##        self.logger.info(
##            "\ncreating doc %s %s template for %s\n" % \
##            (self.name, name[3:],self.get_tb_name()) +
##            "in %s\n " % path
##            )
        tplfilename = os.path.join(nt2_py_dir(),tmpl)
        text = self.__treat(read(tplfilename))
        self.write_docs(names, path)

    def write_docs(self,names,path):
        if type(names) is str :
            self.write_doc(names,path)
        else :
            for name in names :
                self.write_doc(name,path) 
            
    def write_doc(self,name,path):
        dest = path+'/'+name+'.rst'
        if (self.__mode =='add' and exist(dest)) : return
        self.name = name
        self.tb_name = self.__tb
        text = self.__treat(read(self.__tmpl))
        self.logger.info( "doc written to:\n %s\n" % dest)
        write(dest,text,False)
        del self.tb_name
        del self.name
        
    def get_path(self) : return self.__path
    
    def __treat(self,s) :
        """__treat substitutes all $self.<id>$ chains in the
           string s with the value of the variable self.<id> if it
           exist else leaves it as is"""
        if type(s) is str :
            for k,v in self.__dict__.items() :
                s = re.sub('\$self.'+k+'\$',str(v),s)
            return s        
        elif type(s) is list :
            l= [] 
            for ss in s :
                l.append(self.__treat(ss))
            return l


if __name__ == "__main__":
    import nt2_logs
    NT2_LOGS = nt2_logs.Nt2_logs()
    if len(sys.argv)==1 :
##        print "usage :"
##        print "create_doc_file.py <docname> <dirname>"
        docname = "arithmetic"
        dirname = "~/DevC++/dev_lasmea/docnt4/nt2-cleanup/doc/source/sdk/meta/generator"
        d = Doc( tb ='sdk', path=dirname)
        print "dirname %s" % d.get_path()
        print "docname %s" % docname
        d.mk_doc(docname,mode='update')
##    else :
##        docname = sys.argv[1]
##        dirname = sys.argv[2]
##        d = Doc( tb ='core', dirname)
##        print "dirname %s" % d.get_path()
##        print "docname %s" % docname
