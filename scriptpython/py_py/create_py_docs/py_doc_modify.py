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


"""adding or replacing infos to py doc
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
from py_doc_io                       import Py_doc_io
sys.path.pop(0)
sys.path.pop(0)
  

class Py_doc_modify(Py_doc_io) :
    def __init__(self, tb_name,fct_name) :
        Py_doc_io.__init__(self, tb_name, fct_name)
        self.d = self.get_fct_dict_list(verbose=False)

    def add_field(self,chain,value) :
        for i in range(len(self.d)) :
            cmd = 'self.d[%s]%s'%(str(i),chain)
            try :
                exec('z ='+ cmd)
                continue
            except :
                pass
            exec('self.d[%s]%s = %s'%(str(i),chain,value))  

    def modify_field(self,chain,value) :
        for i in range(len(self.d)) :
            cmd = 'self.d[%s]%s'%(str(i),chain)
            try :
                exec('z ='+ cmd)
            except :
                continue
            exec('self.d[%s]%s = %s'%(str(i),chain,value))  
                  
    def add_or_modify_field(self,chain,value) :
        for i in range(len(self.d)) :
            exec('self.d[%s]%s = %s'%(str(i),chain,value))  

    def rm_field(self,chain) :
        for i in range(len(self.d)) :
            exec('del self.d[%s]%s'%(str(i),chain))
            
    def transfer_field(self,fromchain,tochain) :
        for i in range(len(self.d)) :
            cmd = 'self.d[%s]%s'%(str(i),fromchain)
            try :
                exec('z ='+ cmd)
            except :
                continue
            exec('self.d[%s]%s = self.d[%s]%s'%(str(i),tochain,str(i),fromchain))
            exec('del self.d[%s]%s'%(str(i),fromchain))  

    def add_or_modify_fields(self):
        self.add_or_modify_field('["functor"]["special"]',[self.get_tb_name()])
        self.add_or_modify_field('["functor"]["simd_types"]',['real_convert_'])

    def replace_field(self,chain,value,sub) :
        for i in range(len(self.d)) :
            try :
                exec('zz=self.d[%s]%s'%(str(i),chain))
            except :
                continue
            for j in range(len(zz)) :
                if isinstance(zz[j],str) :
                    zz[j] = re.sub(value,sub,zz[j])
                else :
                   for k in range(len(zz[j])) :
                         zz[j][k] = re.sub(value,sub,zz[j][k])
            exec('self.d[%s]%s = %s'%(str(i),chain,zz))  
            
        
    def get_dict_list(self) : return self.d

    def put_field(self,chain) :
        for i in range(len(self.d)) :
            try :
                exec('z = self.d[i]%s'%chain)
                exec('z = self.d[i]%s["default"]'%chain)
            except :
                arity = int(self.d[i]["functor"]["arity"])
                print(arity)
                params = ','.join(["a%s"%str(j) for j in range(arity)])
                print(params)
                value = "{'default' : ['nt2::%s(%s)'],}"%(self.get_fct_name(),params)
                exec('z = self.d[i]%s=%s'%(chain,value))

if __name__ == "__main__" :
    tb_name = "swar"
    ntp = Nt2_tb_props(tb_name)
    fcts = ntp.get_fcts_list()
##    fcts = ["acos"]
    for fct in sorted(fcts) :
        if not(fct in ['predecessor','successor']):
            print("==%s"%fct)
            adf = Py_doc_modify(tb_name,fct)
##        adf.replace_field('["unit"]["verif_test"]["property_value"]["real_"]','crlibm','cephes')
##        adf.replace_field('["unit"]["verif_test"]["property_value"]["real_"]','<nt2::rn>','')
##        adf.replace_field('["unit"]["global_header"]["included"]','crlibm','cephes')
##        adf.transfer_field('["unit"]["specific_values"]["signed_int_   "]','["unit"]["specific_values"]["signed_int_"]')
##            adf.add_or_modify_field('["unit"]["global_header"]["no_ulp"]','"True"')
##            adf.add_or_modify_field('["functor"]["simd_types"]',['real_'])
          
##        adf.replace_field('["unit"]["verif_test"]["property_value"]["real_"]','pi\(a0','l(nt2::long_pi*a0')
##        adf.replace_field('["unit"]["verif_test"]["property_value"]["real_"]','nt2::cephes','')
##            adf.replace_field('["unit"]["global_header"]["no_ulp"]','False',False)
##        adf.put_field('["unit"]["verif_test"]["property_call"]')
            print(adf)
            adf.write_pydoc(force=True)
