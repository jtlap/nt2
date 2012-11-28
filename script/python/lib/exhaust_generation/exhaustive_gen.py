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


"""generation of an exhaustive test unit
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
##from py_doc        import Py_doc
from unit_base_gen import Base_gen
from generation    import Gen
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_modules                     import Nt2_modules
sys.path.pop(0)

from exhaustive_tpls import Exhaustive_data

from pprint   import PrettyPrinter
import re
import datetime

class Exhaustive_gen(Gen,Exhaustive_data) :
    Default_duet = {
        'mini' : 'Valmin<$typ$>',
        'maxi' : 'Valmax<$typ$>',
        'repfunc' : '',
        'exhaustive_included' : '',
        }
    def __init__(self, base_gen) :
        Exhaustive_data.__init__(self)
        Gen.__init__(self,base_gen)

    def collect_py_doc_global_data(self) :
        super(Exhaustive_gen, self).collect_py_doc_global_data()
        self.due     = self.du.get("exhaustive",{})
        self.duv     = self.du.get("verif_test",{})

    def collect_py_doc_typ_data(self) :
        self.duet = self.due.get(self.typ,self.due.get('default',Exhaustive_gen.Default_duet))
        self.mini = self.replace(self.duet['mini'])
        self.maxi = self.replace(self.duet['maxi'])
        self.repfunc = self.replace(self.duet['repfunc'])
        if not len(self.repfunc) :
            self.duvp = self.duv.get("property_value",{})
            self.repfunc = self.duvp.get("typ",self.duvp.get("default",self.duvp.get("real_","")))
        if isinstance(self.repfunc, list) : self.repfunc=self.repfunc[0]
        self.exhaustive_included = self.replace(self.duet['exhaustive_included'])


    def get_exhaustive_path(self)  : return os.path.join(self.nfp.get_md_path(),'exhaustive')

    def get_fct_exhaustive_main_path(self,mode)  :
        return os.path.join(self.get_exhaustive_path(),mode,self.name+'.cpp')

    def get_fct_exhaustive_include_path(self,mode,typ)  :
        return os.path.join(self.get_exhaustive_path(),mode,self.name+'.'+re.sub('::','_',typ)+'.hpp')

    def dgen_main_and_includes(self,types=None) :
        types = self.types if types is None else listify(types)
        dictres={}
        main = self.get_fct_exhaustive_main_path(self.mode)
        dictres[main]=self.gen_main_file()
        for typ in types :
            path =  self.get_fct_exhaustive_include_path(self.mode,typ)
            dictres[path] = self.gen_include_file(path,typ)
        return dictres

    def create_main_and_includes(self,types=None,wr=False) :
        dictres = self.dgen_main_and_includes(types)
        for path in dictres.keys() :
            print(path)
            self.write_file(path,dictres[path],check=False,backup=True,wr=wr)

if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    bg = Base_gen("trigonometric",'sin','simd')
    bbg = Exhaustive_gen(bg)
##    PrettyPrinter().pprint(bbg.gen_global_header().split('\n'))
##    PrettyPrinter().pprint(bbg.gen_test_func_forwarding().split('\n'))
##    PrettyPrinter().pprint(bbg.gen_test_func('float').split('\n'))
##    PrettyPrinter().pprint(bbg.gen_main_func().split('\n'))
    machin = bbg.create_main_and_includes(wr=True)
