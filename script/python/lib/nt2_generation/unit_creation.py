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


"""unit test generation for a functor
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
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from display_utils                   import show
from files_utils                     import write, exist, read
from add_line                        import Add_line
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from unit_base_gen                   import Base_gen
from unit_global_header_gen          import Global_header_gen
from unit_type_header_gen            import Type_header_test_gen
from unit_specific_values_gen        import Specific_values_test_gen
from unit_random_verif_gen           import Random_verif_test_gen
sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)

import re
import shutil
from pprint                          import PrettyPrinter

class Create_tests(Nt2_tb_props) :
    Default_df = {
        'arity' : '1',
        'call_types' : [],
        'ret_arity' : '0',
        'rturn' : {
            'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
        'type_defs' : [],
        'types' : ['real_'],
        }
    def __init__(self, tb_name,
                 fct_list=None,
                 modes=['scalar','simd'],
                 parts=["unit","cover"],
                 platform='sse',
                 show=True,
                 write_files=False,
                 check_on_write=True,
                 backup_on_write=True,
                 verbose=False) :
        self.tb_name =tb_name
        Nt2_tb_props.__init__(self,tb_name)
        if fct_list is None :
            self.fcts = self.get_fcts_list()
        elif isinstance(fct_list,str ) :
            self.fcts = [fct_list]
        else :
            self.fcts = fct_list
        self.parts = parts
        if  isinstance(self.parts,str ) : self.parts = [self.parts]
        self.modes = modes
        if  isinstance(self.modes,str ) : self.modes = [self.modes]
        self.platform=platform
        self.show = show
        self.write_files =write_files
        self.check_on_write = check_on_write
        self.backup_on_write = backup_on_write
        self.verbose=verbose

    def create_one_unit(self, fct_name, mode, part,platform) :

   #     if self.verbose :
        print("%s with %s with %s"%(fct_name,mode,part))
        bg = Base_gen(self.tb_name,fct_name,mode)
        ghg = Global_header_gen(bg,part)
        r = ghg.get_gen_result()
        dl = bg.get_fct_dict_list()
        for rank,d in enumerate(dl) :

            df = d.get('functor',False)
            if not df : df = self.Default_df
            if df.get('no_simd_tests',False) : return []

            types = []
            if mode == 'simd':
                types = bg.recover('simd_types',df,[])
            if len(types) == 0:
                types = bg.recover('types',df,['real_'])

            ret_arity = int(df["ret_arity"])
            d_unit = d.get("unit",{})
            for typ in types :
                thg = Type_header_test_gen(bg,d,typ,rank)
                r+=thg.get_gen_beg()
                if self.verbose : print("part = %s"%part)
                if ("unit"==part) and d_unit.get("specific_values",None) :
                    svt = Specific_values_test_gen(bg,d,typ,ret_arity,platform)
                    s = svt.get_gen_result()
##                    print(s)
##                    raise SystemExit
##                    if not s : return False
                    r += s
                if ("cover" == part) and d_unit.get("verif_test",None) :
                    vtg = Random_verif_test_gen(bg,d,typ,platform)
                    s = vtg.get_gen_result()
##                    print(s)
##                    raise SystemExit
##                    if not s : return False
                    r += s
                r+=thg.get_gen_end()
        return r

    def create_units(self) :
        for fct in self.fcts :
            for mode in self.modes :
                if self.verbose : print("fct=%s,mode=%s"%(fct,mode))
                for part in self.parts :
                    if self.verbose : print("fct=%s,part=%s"%(fct,part))
                    r= self.create_one_unit(fct,mode,part,self.platform)
                    if r is None :
                        print('error for %s' % fct)
                    elif not r or len(r)==0 :
                        print('no regeneration possible for %s %s-tests, please do it manually' % (fct,mode))
                    else :
                        just = "just" if show and not self.write_files else ""
                        if show :
                            print("%s showing text of %s.cpp for %s-test: %s"% (just,fct,mode,part))
                            print("<"+"="*40)
                            PrettyPrinter().pprint(r)
                            print("="*40+">")
                        if self.write_files :
                            print("writing text of %s.cpp for %s-test"% (fct,mode))
                            self.write_unit(fct,mode,part,r)


    def write_unit(self,
                   fct_name,
                   mode,
                   part,
                   s) :
        def test_immutable(p) :
            s= '\n'.join(read(p))
            return s.find('//COMMENTED') != -1

        nfp = Nt2_fct_props(self.tb_name,fct_name,mode)
        p = nfp.get_fct_unit_path(mode,part)
        if exist(os.path.split(p)[0]) :
            if self.verbose : print ('path = %s'%p)
            print("---%s"%exist(p))
            if exist(p) and test_immutable(p) :
                print("%s has been marked as immutable"%p )
                return
            if self.backup_on_write and exist(p) :
                if self.verbose : print("backing up %s" %fct_name)
                i = 1;
                while True :
                    pi = p+'.'+str(i)+'.bak'
                    if not(exist(pi)) : break
                    i += 1
                if self.verbose : print("to %s"% pi)
                shutil.copy(p,pi)
            elif self.verbose : print "writing to %s"%p
            write(p,s,self.check_on_write)
            p1 = os.path.join(os.path.split(p)[0],'CMakeLists.txt')
            addline=Add_line(p1,fct_name)
            addline.update_file("SET\( *SOURCES")
        elif self.verbose :
            print("%s directory\n  does not exist " %os.path.split(p)[0])




if __name__ == "__main__" :
    tb_name = "operator"
    fcts = Nt2_tb_props(tb_name).get_fcts_list()
    fcts = ["splat"]
    ct = Create_tests(tb_name,
                     fcts,
                     modes=['scalar','simd'],
                     parts= ["unit"],
                     show=True,
                     write_files=False,
                     check_on_write=True,
                     backup_on_write=True,
                     verbose=False)
    ct.create_units()
