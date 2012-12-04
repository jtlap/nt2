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
from __future__         import print_function

"""Utilities to get nt2 fct properties from py file
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from files_utils       import read, exist, write
sys.path.pop(0)

import re
from pprint            import PrettyPrinter
from nt2_archis_struct import Nt2_archis_struct
from nt2_fct_internals import Nt2_fct_internals
from nt2_tb_props      import Nt2_tb_props

class Nt2_fct_props(Nt2_tb_props) :
    """ fct properties recovery from implementation  """

    def __init__(self, tb_name, fct_name, mode="scalar", submode="") :
        Nt2_tb_props.__init__(self, tb_name)
        self.__fct_name = fct_name
        self.__mode = mode
        self.__fct_arities = self.__read_arities()
        self.__fct_ret_arity = self.__read_ret_arity()
##        self.__fct_dict = self.__read_fct_info_dict()


    def get_fct_name(self) : return self.__fct_name
    def get_fct_text(self) : return read(self.get_fct_impl_path(self.__mode)) ## submode must be also used here
    def get_fct_def_text(self) : return read(self.get_fct_def_path())
    def get_fct_dict_list(self,verbose=False) :
        s = self.__read_fct_info_dict(verbose)
        return s if isinstance(s,list) else [s]
    def get_abs_path(self,to)   : return os.path.join(self.get_nt2_path(),to)
    def get_fct_doc_path(self)  :
        return os.path.join(self.get_doc_path(),self.get_fct_name()+'.py')
    def get_fct_def_path(self)  :
        return os.path.join(self.get_def_path(),self.get_fct_name()+'.hpp')
    def get_fct_impl_path(self,*modes)  :
        if isinstance(modes[0],list) : modes = modes[0]
        m = ''
        for mm in modes : m = os.path.join(m,mm)
        return os.path.join(self.get_def_path(),m,self.get_fct_name()+'.hpp')
    def get_fct_unit_path(self,mode,part)  :
        return os.path.join(self.get_unit_path(part),mode,self.get_fct_name()+'.cpp')
    def get_fct_bench_path(self,mode)  :
        return os.path.join(self.get_bench_path(),mode,self.get_fct_name()+'.cpp')
    def get_fct_exhaustive_path(self,mode)  :
        return os.path.join(self.get_exhaustive_path(),mode,self.get_fct_name()+'.cpp')


    def get_fct_arities(self) : return self.__read_arities()#self.__fct_arities
    def get_fct_ret_arity(self) : return self.__fct_ret_arity
    def get_fct_returns(self, typ=None, mode='scalar') :
#        PrettyPrinter().pprint(self.get_fct_text())
        return self.__get_striped_returns(self.get_fct_text())
    def get_fct_types(self) :
        return Nt2_fct_internals.get_calls(self.get_fct_text()).keys()

 #       return "typename typedef boost::result_of<nt2::meta::floating(T)>::type"    ##TO DO
    def get_fct_call_types(self) : return []  ##TO DO
    def get_fct_type_defs(self) : return []   ##TO DO



    def is_subsidiary(self,*modes) :
        path = self.get_fct_impl_path(list(modes))
        if not exist(path) : return True
        s = ' '.join(read(path))
        pattern = "#include *<nt2/toolbox/%s/function/simd/.*%s\.hpp> *"
        return bool(re.match(pattern %(self.get_tb_name(),self.get_fct_name()),s))

    def is_empty(self,*modes) :
        path = self.get_fct_impl_path(list(modes))
        if not exist(path) : return True
        for s in read(path) :
            if (len(s) != 0 and s[0] != "#") : return False
            if (len(s)>1 and (s[0]!="/" or s[1]!="/") ) : return False
        return True

    def is_unimplemented(self) :
        s = ' '.join(read(self.get_fct_def_path()))
        return bool(re.search('/// Still unimplemented',s))

    def is_already_revised(self) :
        s = ' '.join(read(self.get_fct_def_path()))
        return bool(re.search('/// Revised by ',s))

## ################################################################
## private section
## ################################################################

    def __read_fct_info_dict(self,verbose = False) :
        p = self.get_fct_doc_path()
##        print("p = %s" % p)
##        print("self.get_doc_path() %s" % self.get_doc_path())
        if not exist(p) :
            print('FATAL ERROR')
            print("%s does not exist: please create it before use" % p )
            print("You can use existing py doc files as model")
            raise SystemExit
##            self.__create_fct_info_dict(p,error='warn')
        s = '\n'.join(read(p))
        if verbose :
            print("py doc file for %s is:" % self.get_fct_name())
            print("=============================================")
            print(s)
            print("=============================================")
        exec("d = "+s)
        return d

    def __read_arities(self) :
        p = self.get_fct_def_path()
        arities = []
        if exist(p) :
            s = read(p)
            #            PrettyPrinter().pprint(s)
            for l in s :
                m = re.search('\s*NT2_.*FUNCTION_IMPLEMENTATION',l)
                if m :
                    m = re.search('([0-9]+)\)',l)
                    if m :
                        arities.append(int(m.groups()[0]))
        return arities

    def __read_ret_arity(self) :
        p = self.get_fct_impl_path('scalar')
        if exist(p) :
            s = '/n'.join(read(p))
            return '2' if re.search('boost::fusion',s) else '0'
        else :
            return '0'

    @classmethod
    def __get_striped_returns(self,txt, typ='.*') :
        d1 = Nt2_fct_internals.get_returns(txt,typ)
        d = {}
        for t in d1.keys() :
            r =  ' '.join(d1[t])
            m = re.match(".*struct result<.*?: *(.*){",r)
            if m :
                tmp = re.sub("A\d",'T',m.group(1))+'::type'
                tmp = re.sub(' ','',tmp)
                tmp = re.sub('meta','nt2::meta',tmp)
                d[t] = 'typename '+tmp
            else :
                d[t]= 'T'
        return d


if __name__ == "__main__" :
    nfp = Nt2_fct_props("ieee","successor")
    print(nfp.get_fct_def_path())
    print(nfp.get_fct_impl_path('scalar'))
    print(nfp.get_fct_impl_path('simd','common'))
    print(nfp.get_fct_impl_path('simd','sse','sse2'))
    print(nfp.get_fct_impl_path(['simd','sse','sse2']))
    print(nfp.get_fct_unit_path('scalar'))
    print(nfp.get_fct_unit_path('simd'))
    print(nfp.get_fct_bench_path('scalar'))
    print(nfp.get_fct_bench_path('simd'))
    print(nfp.get_fct_doc_path())
    print(nfp.get_fct_arities())
    print(nfp.get_fct_ret_arity())
##    PrettyPrinter().pprint(nfp.get_fct_returns())  ## broken
##    print(nfp.get_fct_call_types())                ## broken
    print(nfp.is_subsidiary('simd','sse','sse2'))
    print(nfp.is_subsidiary('simd','sse','sse4.1'))
    print(nfp.is_empty('simd','sse','sse4.1'))
    print(nfp.is_unimplemented())
    print(nfp.is_already_revised())

