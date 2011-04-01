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


"""adding infos to py doc
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
from py_doc_base                     import Py_doc_base
sys.path.pop(0)
sys.path.pop(0)
  

class Add_doc_fields(Py_doc_io) :
    def __init__(self, tb_name,fct_name) :
        Py_doc_base.__init__(self, tb_name, fct_name)
        self.__old_txt = self.read_pydoc()
        self.d = self.get_fct_dict_list(verbose=False)
        self.__new_txt = self.__old_txt
        
    def get_old_txt(self) : return self.__old_txt
    def get_new_txt(self) : return self.__new_txt

    def add_fields(self, force = False):
        d=self.d[0]
        df = d["functor"]
        if not df.get('special',None) or force :
            d["functor"]['special'] = [self.get_tb_name()]
        if not df.get('simd_types',None) or force :
            d["functor"]['simd_types'] = ['real_convert_']
        self.d[0]=d
        PrettyPrinter().pprint (d)
        
    def modify_fields(self, force = False):
        d=self.d[0]
        du = d["unit"]["verif_test"]["property_value"]
        pc = du.get("real_","")[0]
        print(pc)
        def subs(g) :
            g1 = g.group('g1')
            g2 = g.group('g2')
            print(g1)
            print(g2)
            return 'nt2::cephes::%s%s' % (g1,g2)
        pc = re.sub('(?P<g1>nt2::crlibm).*(?P<g2><nt2::rn>).*',subs,pc)
        print("pc = %s" %pc)
        self.d[0]=d
        PrettyPrinter().pprint (d)


    def __str__(self) :
        s = self.myformat0()
        return '\n'.join(s)

    def myprint0(self,indent = 4,width=80) :
        print('[')
        for d in self.d :
            self.myprint(d,indent)
        print(']')
    def myprint(self,d,beg,indent=4,width=80) :
        if isinstance(d,list ) :
            s = str(d)
            if len(s)>width :
                s = (' '*beg)+(',\n'+' '*beg).join(s.split(','))
            else :
                s = ' '*beg+s
       
            print(s)
        elif  isinstance(d,str ) :
            d=' '*beg+"'"+d+"'"
            print(d)
        elif isinstance(d,dict ) :
            for k in d.keys() :
                if isinstance(d[k],dict ) :
                    print("%s %s : {"%(' '*beg,k))
                else :
                    print("%s %s : "%(' '*beg,k))
                self.myprint(d[k],beg+indent)
            print(' '*beg+'}')
        
    def myformat0(self,indent=4,width=120) :
        rl =['[',' '*indent+'{']
        for d in self.d :
            begi = indent
            rl = self.myformat(d,rl,begi,depth=0,indent=indent,width=width)
        rl.append(']')
        return rl
    
    def myformat(self,d,rl,beg,depth=0,indent=4,width=80) :
        if isinstance(d,list ) :
            s = str(d)
            if len(rl[-1])+len(d) > width :
                if len(s)>width :
                    s = ((' '*beg)+(',\n'+' '*beg).join(s.split(','))).split('\n')
                else :
                    s = [' '*beg+s]
                    rl.extend(s)
            else :
                rl[-1]+=s.lstrip();                
            return rl

        elif  isinstance(d,str ) :
            if len(rl[-1])+len(d) > width :
                d=' '*beg+"'"+d+"'"
                rl.append(d)
            else :
                rl[-1]+=("'"+d+"'").lstrip();
            return rl

        elif isinstance(d,dict ) :
            if depth < 4 :
                for k in d.keys() :
                    if isinstance(d[k],dict ) :
                        rl.append("%s '%s' : {"%(' '*beg,k))
                    else :
                        rl.append("%s '%s' : "%(' '*beg,k))
                    self.myformat(d[k],rl,beg+indent,depth=depth+1,indent=indent,width=width)
                rl.append(' '*beg+'},')
            else :
                for k in d.keys() :
                    if isinstance(d[k],dict ) :
                        rl[-1]+=("%s '%s' : {"%(' '*beg,k)).lstrip()
                    else :
                        rl[-1]+=("%s '%s' : "%(' '*beg,k)).lstrip()
                    self.myformat(d[k],rl,beg+indent,depth=depth+1,indent=indent,width=width)
                    rl[-1]+=', '
                rl[-1]+='},'
            return rl

                                    
if __name__ == "__main__" :
    adf = Add_doc_fields('trigonometric','cos')
##    adf.show()
##    adf.add_fields()
    adf.modify_fields()
    print("=====================================")
    print(adf)
    print("=====================================")
##      adf.myprint0()
##    adf.show()
    print(adf)
