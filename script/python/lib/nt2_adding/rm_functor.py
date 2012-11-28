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


"""utilities to remove a functor from a toolbox
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

import re
import shutil
from display_utils                   import show
from files_utils                     import write, exist, read
from nt2_base_struct                 import Nt2_base_struct
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from pprint                          import PrettyPrinter
from unit_base_gen                   import Base_gen
from unit_global_header_gen          import Global_header_gen
from unit_type_header_gen            import Type_header_test_gen
from unit_specific_values_gen        import Specific_values_test_gen
from unit_random_verif_gen           import Random_verif_test_gen
from nt2_tb_struct                   import Nt2_tb_struct
from nt2_archis_struct               import Nt2_archis_struct
from headerfiles                     import Headers

sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)


class Rm_functor(Base_gen,Nt2_tb_struct) :
    def __init__(self,tb_name,fct_name,no_simd=False) :
        Base_gen.__init__(self, tb_name, fct_name, 'scalar')
        Nt2_tb_struct.__init__(self)
        self.tb_files  = self.get_rel_tb_unique_files(tb_name)
        self.fct_files = self.get_rel_tb_fcts_files(tb_name,fct_name)
        self.unique_files = self.get_rel_tb_unique_files(tb_name)
        self.no_simd = no_simd

    def rm_files(self) :
        for fil in self.fct_files :
            if fil[:6]=='../../':
                self.remove_file(fil)
            else :
                for pattern in self.Required_tree :
                    if  pattern ==fil[0:len(pattern)] :
                        print("--->%s ## %s"%('remove_file',fil))
                        if fil !="doc/%s.py"%self.get_fct_name() : ## don't remove <fct_name>.py file
                            self.remove_file(fil)
                        break
        print("--->%s ## %s"%('regress_benches_and_units',fil))
        self.regress_benches_and_units()
        print("--->%s ## %s"%('regress_global_includes',fil))
        self.regress_global_includes()

    def regress_benches_and_units(self,option="update") :
        """ the files to be modified are:
           ./bench/scalar/CMakeLists.txt
            ./bench/simd/CMakeLists.txt
            ./unit/scalar/CMakeLists.txt
            ./unit/simd/CMakeLists.txt
        ./bench/CMakeLists.txt and ./unit/CMakeLists.txt,
        are not to be modified after creation
        TO DO add action for "create"
        """
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        l = [os.path.join("bench","scalar"),
             os.path.join("bench","simd"),
             os.path.join("unit","scalar"),
             os.path.join("unit","simd")]
        for p in l :
            path = os.path.join(self.get_tb_path(),os.path.join(p,'CMakeLists.txt'))
            txt_orig = read(path)
            txt = "  %s.cpp"%fct_name
            done, new_txt = self.remove_line(txt_orig,txt)
            if not done :
                print("Warning : line\n  %s\nws not found in CMakelist.txt file"%txt )
            else :
                self.finalize(path,new_txt,"update")


    def regress_global_includes(self,option="update") :
        """ the files to be updated is: ./$tb_name$.hpp
        ../$tb_name$.hpp' and ./include.hpp, are not to be modified after creation
        TO DO add action for "create"
        """
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        path = os.path.join(self.get_tb_path(),tb_name+'.hpp')
        txt_orig = read(path)
        txt = "#include <nt2/toolbox/%s/include/%s.hpp>"%(tb_name,fct_name)
        done, new_txt = self.remove_line(txt_orig,txt)
        if not done :
            print("Warning : line\n  %s\nis not found in include file"%txt )
        else :
            self.finalize(path,new_txt,"update")

    def remove_file(self,fil,option="remove") :
        """ create the include files in the global include files directory
        of nt2 if the toolbox is of 'sys' style and pattern is '../../include'
            also create the local toolbox functor include file if pattern is
            'include'
        """
        path = os.path.join(self.get_tb_path(),fil)
        self.finalize(path,"",option)


    def finalize(self,path,new_txt,option) :
        verbose = False
        print("======================")
        if option == "remove" :
            if not exist(path) :
                if verbose : print("file\n  %s\n does not exist"%path)
            else :
                if verbose : print("file\n  %s\nwill be removed"%path)
                self.remove(path)
                if verbose : print("file\n  %s\nis now created"%path)
        elif option == "update" :
            if exist(path) :
                if verbose : print("file\n  %s\nwill be regressed")
                self.regress(path,new_txt)
                if verbose : print("file\n  %s\nis now regressed"%path)
            else :
                if verbose : print("file\n  %s\n does not exist"%path)
        else :
            if verbose : print("I do not know what to do with: \n  %s\nplease help me!"%path)
        print("----------------------")


    def remove(self,path) :
        """ file path  exists on entry
        is removed on exit, but replace by path+'~'
        """
        print("remove %s"%path)
        shutil.move(path,path+'#')


    def regress(self,path,txt) :
        """ file path does exist on entry
        is regressed on exit, old version is in path+'~' file
        """
        print("regress %s"%path)
        shutil.move(path,path+'#')
        write(path,txt,False)

    def remove_line(self,text, line2rmv) :
        if line2rmv in text :
            text.remove(line2rmv)
            return (True,text)
        else :
            return (False,text)

if __name__ == "__main__" :
    tb_name = "arithmetic"
    fcts = ["sadd"]
    for fct_name in fcts :
        print fct_name
        afs = Rm_functor(tb_name,fct_name,no_simd=False)
        afs.rm_files()


