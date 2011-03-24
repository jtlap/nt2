#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
##############################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################


""" py doc read/write
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
import datetime
import shutil
import re
from files_utils                     import write, exist, read
from nt2_base_infos                  import Nt2_base_infos
from pprint                          import PrettyPrinter
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
sys.path.pop(0)
sys.path.pop(0)
  

class Py_doc_io(Nt2_fct_props) :
    def __init__(self, tb_name,fct_name) :
        Nt2_fct_props.__init__(self, tb_name, fct_name)
        self.author = Nt2_base_infos.get_author()
        self.date = datetime.datetime.now().strftime("%d/%m/%Y")
        print("zut2")
        
    def write_pydoc(self,other_name=None,force=False,backup=True) :
        name = self.get_fct_name()+'.py' if other_name==None else other_name
        p = os.path.join(self.get_doc_path(),name)
        if backup and exist(p) : shutil.copy(p,p+'~')
        if exist(p) and not force :
            s = '\n'.join(read(p))
            if re.search("manually",s) :
                print("%s \n  was manually modified, skipping"%p)
                return
        write(p,str(self),check=False,verbose=True)

    def read_pydoc(self) :
        p = os.path.join(self.get_doc_path(),self.get_fct_name()+'.py')
        if not exist(p) :
            print("%s \n  does not exist, please create and edit it "%p)
            raise SystemExit
        else :
            return read(p)

    def __str__(self) :
        s = self.__myformat0(width=150)
        s = '\n'.join(s)
        s = re.sub('\$author\$',self.author,s)
        s = re.sub('\$date\$',self.date,s)
        return s

    def get_dict_list(self) : return self.get_fct_dict_list()
       
    def __myformat0(self,indent=4,width=120) :
        sd = self.get_dict_list()
        rl =['[ ## this file was manually modified by $author$',' '*indent+'{']
        for d in sd :
            d['info'] = 'manually modified'
            begi = indent
            rl = self.__myformat(d,rl,begi,depth=0,indent=indent,width=width)
        rl.append(']')
        return rl
    
    def __myformat(self,d,rl,beg,depth=0,indent=4,width=120) :
        if isinstance(d,list ) :
            if (len(d)>0 and isinstance(d[0],list ) and
                len(d[0])>0 and isinstance(d[0][0],list )) :
                rl[-1]+='['
                for ld in d:
                    s = str(ld)
                    rl.append((' '*beg)+s+',')
##                    print ("==== %s"%s)
##                    if len(rl[-1])+len(s) > width :
##                        s = (((' '*beg)+(',\n'+' '*beg).join(s.split(',')))+',').split('\n')
##                        rl.extend(s)
##                    else :
##                    rl[-1]+=s.lstrip()+',';                
                rl.append((' '*beg)+'],')   
            else :    
                s = str(d)
                if len(rl[-1])+len(s) > width :
                    s = (((' '*beg)+(',\n'+' '*beg).join(s.split(',')))+',').split('\n')
                    rl.extend(s)
                else :
                    rl[-1]+=s.lstrip()+',';                
            return rl
        elif isinstance(d,str ) :
            if len(rl[-1])+len(d) > width :
                d=' '*beg+"'"+d+"',"
                rl.append(d)
            else :
                rl[-1]+=("'"+d+"',").lstrip();
            return rl
        elif isinstance(d,dict ) :
            if depth < 4 :
                for k in sorted(d.keys()) :
                    if isinstance(d[k],dict ) :
                        rl.append("%s '%s' : {"%(' '*beg,k))
                    else :
                        rl.append("%s '%s' : "%(' '*beg,k))
                    self.__myformat(d[k],rl,beg+indent,depth=depth+1,indent=indent,width=width)
                rl.append(' '*beg+'},')
            else :
                for k in sorted(d.keys()) :
                    if isinstance(d[k],dict ) :
                        rl[-1]+=("%s '%s' : {"%(' '*beg,k)).lstrip()
                    else :
                        rl[-1]+=("%s '%s' : "%(' '*beg,k)).lstrip()
                    self.__myformat(d[k],rl,beg+indent,depth=depth+1,indent=indent,width=width)
                rl[-1]+='},'
            return rl

                                    
if __name__ == "__main__" :
    pdi = Py_doc_io('trigonometric','cos')
    print("=====================================")
    print(pdi)
    print("=====================================")
    pdi.write_pydoc('pipo.py')
