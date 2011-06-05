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

def create_one_unit(tb_name,
                    fct_name,
                    mode,
                    part) :
    print("%s with %s with %s"%(fct_name,mode,part))
    bg = Base_gen(tb_name,fct_name,mode)
    ghg = Global_header_gen(bg,part)
    r = ghg.get_gen_result()
    if True:
        dl = bg.get_fct_dict_list()
        for rank,d in enumerate(dl) :
            origin ="types" if mode == 'scalar' else 'simd_types'
            if d["functor"].get('no_simd_tests',False) : return []
            types = bg.recover(origin,d["functor"],["real_"])
            ret_arity = int(d["functor"]["ret_arity"])
            d_unit = d["unit"]
            for typ in types :
                thg = Type_header_test_gen(bg,d,typ,rank)
                r+=thg.get_gen_beg()
                print("part = %s"%part)
                if ("unit"==part) and d_unit.get("specific_values",None) :
                    svt = Specific_values_test_gen(bg,d,typ,ret_arity,mode)
                    r += svt.get_gen_result()
                if ("cover" == part) and d_unit.get("verif_test",None) :
                    vtg = Random_verif_test_gen(bg,d,typ,mode)
                    r += vtg.get_gen_result()
                r+=thg.get_gen_end()
        return r


##def insert_after(token, txt, line2add) :
##    """ insertion of a line after a line
##    containing a token in a list of lines
##    """
##    pattern = re.compile(line2add)
##    def find_index(p) :
##        for i,l in enumerate(txt) :
##            if p.match(l) : return i+1
##        return 0
##    if find_index(pattern) :
##        return (False,txt)
##    else :
##        #### match for token
##        pattern = re.compile(token)
##        i = find_index(pattern)
##        if i != 0 : txt.insert(i,line2add)
##        return (True,txt)

##def update_cmakelist(p,fct_name) :
##    txt_orig = read(p)
##    txt = "  %s.cpp"%fct_name
##    done, new_txt = insert_after("SET\( SOURCES",txt_orig,txt)
##    print("----------------------------------------------------------")
##    print("new_txt %s"%new_txt)
##    print("----------------------------------------------------------")
   
##    if not done :
##        print("Warning : line\n  %s\nis already in CMakelists.txt file"%txt ) 
##    else :
##        if exist(p) :
##            print("file\n  %s\nwill be updated"%p)
##            write(p,new_txt,False)
##            print("file\n  %s\nis now updated"%p)
##        else :
##            print("file\n  %s\n does not exist"%p)         


def write_unit(tb_name,fct_name,mode,part,s,check=False,backup=True) :
    nfp = Nt2_fct_props(tb_name,fct_name,mode)
    p = nfp.get_fct_unit_path(mode,part)
    print ('p = %s'%p)
    if backup and exist(p) :
        print("p=%s" %p)
        i = 1;
        while True :
            pi = p+'.'+str(i)+'.bak'
            if not(exist(pi)) : break
            i += 1
        print("backing to %s"% pi)
        shutil.copy(p,pi)
    print "writing to %s"%p
    write(p,s,check)
    p1 = os.path.join(os.path.split(p)[0],'CMakeLists.txt')
    print("p1= %s"%p1)
    addline=Add_line(p1,fct_name)
    addline.update_file("SET\( SOURCES")
 
def create_unit(tb_name, fct_list=None,
                modes=['scalar','simd'],
                parts=["unit","cover"],
                show=True,
                write_files=False,
                check_on_write=True,
                backup_on_write=True) :
    if fct_list is None :
        fcts = Nt2_tb_props(tb_name).get_fcts_list()
    elif isinstance(fct_list,str ) :
        fcts = [fct_list]
    else :
        fcts = fct_list
    if  isinstance(parts,str ) : parts = [parts]
    if  isinstance(modes,str ) : modes = [modes]    
    for fct in fcts :
        for mode in modes :
            print("fct=%s,mode=%s"%(fct,mode))
            for part in parts :
                print("fct=%s,part=%s"%(fct,part))
                r= create_one_unit(tb_name,fct,mode,part)
                if r is None :
                    print('error for %s' % fct)
                elif len(r)==0 :
                    print('no regeneration possible for %s %s-tests, please do it manually' % (fct,mode))
                else :
                    just = "just" if show and not write_files else ""
                    if show : 
                        print("%s showing text of %s.cpp for %s-test: %s"% (just,fct,mode,part))
                        print("<"+"="*40)
                        PrettyPrinter().pprint(r)            
                        print("="*40+">")
                    if write_files :
                        print("writing text of %s.cpp for %s-test"% (fct,mode))
                        write_unit(tb_name,fct,mode,part,r,
                                   check=check_on_write,
                                   backup=backup_on_write)

        
if __name__ == "__main__" :
    tb_name = "bitwise"
    fcts = Nt2_tb_props(tb_name).get_fcts_list()
    parts = ["unit","cover"]
    fcts = ["selsub","bitwise_notor"]
    create_unit(tb_name,fct_list=fcts,show=True)
