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


"""class to trade with py_docs files
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Lapreste Jean-Thierry"
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from unit_base_gen import Base_gen
sys.path.pop(0)
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from substitute_utils import stringize, listify
sys.path.pop(0)

from pprint   import PrettyPrinter

import re
import datetime

class Py_doc() :
    def __init__(self,
                 tb_name=None,
                 fct_name=None,
                 mode=None,
                 d=None,
                 bg=None,
                 index=0,
                 arity=None,
                 repfunc=None,
                 repinclude=None) :
        self.bg = bg if tb_name is None else  Base_gen(tb_name,fct_name,mode)
        self.name = self.bg.get_fct_name()
        self.tb_name = self.bg.get_tb_name()
        self.mode = self.bg.get_fct_mode()
        self.d = self.__get_dict(d,index,arity)
        self.typs = self.get_types()
        self.types_str =stringize(self.typs)

##        self.repfunc = self.bg.get_fct_name()+'_rn' if repfunc is None else repfunc
##        self.repinclude = "#include <nt2/toolbox/crlibm/functions/"+self.repfunc+'.hpp>' if repinclude is None else repinclude
        self.prefix = "nt2" if self.bg.get_tb_name().find('.')==-1 else '::'.join(self.bg.get_tb_name().split('.')[0:-1])

    def __get_dict(self,d,index,arity) :
        """ if d is not None return simply d
            else if arity is None index must be in the correct range
            and the index directory in the base gen list is returned
            else the routine lookfor an arity n entry in the list and
            return it
            """
        if d is None :
            dl = self.bg.get_fct_dict_list()
            if arity is None :
                if index is None or not isinstance(index,int):
                    print("Insufficient informations to choose dictionary")
                    print("Aborting")
                    raise SystemExit
                elif index >= len(dl) or index < 0:
                    print("A dictionnary of index %s does not exist"%arity)
                    print("Aborting")
                    raise SystemExit
                else :
                    return dl[index]
            else :
                for di in dl :
                    if int(di["functor"]["arity"])==arity :
                        return di
            if d is None :
                print("A dictionnary of arity %s does not exist"%arity)
                print("Aborting")
                raise SystemExit
        else :
            return d

    def arity_n_dict(self,arity=1) :
        dl = self.bg.get_fct_dict_list()
        for di in dl :
            if int(di["functor"]["arity"])==arity :
                return di
        return None

    def get_gen_result(self) : return  self.__gen_result

    def get_includes(self) :
        du = self.d.get("unit",{})
        self.included = listify(du['global_header'].get("included",[]))
        self.cover_included = listify(du['global_header'].get("cover_included",[]))
##        self.exhaustive_included = listify(self.due.get("exhaustive_included",[]))
##        print("self.included %s"%self.included)
##        print("self.cover_included %s"%self.cover_included)
##        print("self.exhaustive_included %s"%self.exhaustive_included)

    def expand_types(self,tt) :
        expand_dict = {
            'real_' : ['float'],
            'signed_int_' : ['nt2::int32_t','nt2::int16_t','nt2::int8_t'],
            'unsigned_int_' : ['nt2::uint32_t','nt2::uint16_t','nt2::uint8_t'],
            'int_convert_'  : ['nt2::int32_t'],
            'uint_convert_'  : ['nt2::uint32_t'],
            }
        r = []
        for t in tt :
            r.extend(expand_dict.get(t,[t]))
        return r

    def get_original_types(self) :
        t = self.d["functor"].get("simd_types",None)
        if t is None or self.mode =='scalar' : t = self.d["functor"].get("types",None)
        return t

    def get_types(self) :
        return self.expand_types(self.get_original_types())


if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    pyd = Py_doc("trigonometric",'sin','simd')
    print(pyd.get_types())

