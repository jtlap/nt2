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


"""oxygenation of functors in a module
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
from string import find

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from display_utils                   import show
from files_utils                     import write, exist, read
from write_utils                     import Write_file
from substitute_utils                import Substitute
from add_line                        import Add_line
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from unit_base_gen                   import Base_gen
sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)

import re
import shutil
from pprint                          import PrettyPrinter


class Nt2_oxygenation(Nt2_tb_props,Substitute) :
    def __init__(self, tb_name, 
                 fct_list=None,
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
        self.wr = Write_file(show,
            write_files,
            check_on_write,
            backup_on_write,
            verbose
            )
        self.save = True
        self.p = None
        self.fct = None
        
    def doxyfy(self) :
        for fct in self.fcts :
            new_txt = self.doxyfy_one(fct)
            self.wr.write(self.p,self.fct,new_txt)
##            for n in new_txt : print(n)

    def is_immutable(self,txt) :
        return txt.find('//COMMENTED') != -1
    
    def doxyfy_one(self,fct) :
        self.fct=fct
        self.get_file_location()
        if self.p is None :
            self.save =False
            return
        else :
            self.txt_list = read(self.fich)
            self.txt ='\n'.join(self.txt_list)
            if self.is_immutable(self.txt) :
                print("%s has been marked as immutable"%self.txt )
                return False
            if find('\*!',self.txt) != -1 :
                print("%s file was already oxygenated"%self.fct)
                self.save =False
                return 
        self.txt_list = self.make_file_ox()
        self.txt      = '\n'.join(self.txt_list)
##        show(self.txt_list)
        self.txt_list = self.make_fct_ox()
        self.txt      = '\n'.join(self.txt_list)
##        show(self.txt_list)
        return self.txt_list
    
    def is_boost(self) :
        return self.tb_name.find('.') != -1

    def get_file_location(self) :
        self.p = self.get_def_path()
        self.fich = os.path.join(self.p,self.fct+'.hpp')
        if not exist(self.fich) :
            print("file: %s does not exist"%self.fich)
            self.p = self.get_redef_path()
            self.fich = os.path.join(self.get_redef_path(),self.fct+'.hpp')
        if not exist(self.fich) :
            print("and file: %s neither exist"%self.fich)
            self.p=None
    
        
    def make_file_ox(self) :
        File_ox = [
            "/*!",
            " * \\file",
            " * \\brief $action$ the tag $fct$_ of functor $fct$ ",
            " *        in namespace $namespace$",
            " */"
            ]
        self.action = "Define" if self.txt.find("boost::simd::"+self.fct) == -1 else "Bring"
        self.namespace = "boost::simd::tag" if self.is_boost() else "nt2::tag" 
        file_ox = self.prepare(File_ox)
        del self.namespace
        del self.action
        j=0
        for ss in self.txt_list :
            if len(ss) and (ss[0] == '/') :
                j+=1
            else :
                break
        j+=2
        ll = self.txt_list[:j]
        ll.extend(file_ox)
        ll.extend(self.txt_list[j:])
        return ll

    def make_fct_ox(self) :
        Fct_ox = [
            "//============================================================================",
            "/*!",
            " * \ingroup functions",
            " * The function $fct$ computes",
            " *",
            " *",
            " *",
            " * \semantic",
            " *",
            " *",
            " *",
            " * \code",
            " * ",
            " * \endcode",
            " *",
            " * ",
            " *",
            " * \code",
            " * ",
            " * \endcode",
            " *",
            " * \usage:",
            " *",
            " * \include $fct$.cpp",
            " */",
            "//============================================================================",
            ]
        pattern = re.compile("namespace\s*tag")
        pattern1= re.compile("namespace\s*tag\s*{")
        for i,s in enumerate(self.txt_list):
            if pattern1.search(s) :
                j = i+1
                break
            elif pattern.search(s) :
                j = i+2
                break
        l = len(self.txt_list[j-1])-len(self.txt_list[j-1].lstrip())+2
        ll = self.txt_list[:j]
        fct_ox = self.indent(Fct_ox,l)
        fct_ox = self.prepare(fct_ox)
        ll.extend(fct_ox)
        ll.extend(self.txt_list[j:])
        return ll

    
    def prepare(self,txt) :
        if isinstance(txt, list) :
            txt = '\n'.join(txt)
        return self.replace(txt).split('\n')

    def indent(self,txt,l) :
        return [' '*l+t for t in txt]

    

           
##    def create_units(self) :
##        for fct in self.fcts :
##            for mode in self.modes :
##                if self.verbose : print("fct=%s,mode=%s"%(fct,mode))
##                for part in self.parts :
##                    if self.verbose : print("fct=%s,part=%s"%(fct,part))
##                    r= self.create_one_unit(fct,mode,part,self.platform)
##                    if r is None :
##                        print('error for %s' % fct)
##                    elif not r or len(r)==0 :
##                        print('no regeneration possible for %s %s-tests, please do it manually' % (fct,mode))
##                    etxt_liste :
##                        just = "just" if show and not self.write_files etxt_liste ""
##                        if show : 
##                            print("%s showing text of %s.cpp for %s-test: %s"% (just,fct,mode,part))
##                            print("<"+"="*40)
##                            PrettyPrinter().pprint(r)            
##                            print("="*40+">")
##                        if self.write_files :
##                            print("writing text of %s.cpp for %s-test"% (fct,mode))
##                            self.write_unit(fct,mode,part,r)


##    def write_unit(self,
##                   fct_name,
##                   mode,
##                   part,
##                   s) :
##        def test_immutable(p) :
##            s= '\n'.join(read(p))
##            return s.find('//COMMENTED') != -1
            
##        nfp = Nt2_fct_props(self.tb_name,fct_name,mode)
##        p = nfp.get_fct_unit_path(mode,part)
##        if exist(os.path.split(p)[0]) :
##            if self.verbose : print ('path = %s'%p)
##            print("---%s"%exist(p))
##            if exist(p) and test_immutable(p) :
##                print("%s has been marked as immutable"%p )
##                return
##            if self.backup_on_write and exist(p) :
##                if self.verbose : print("backing up %s" %fct_name)
##                i = 1;
##                while True :
##                    pi = p+'.'+str(i)+'.bak'
##                    if not(exist(pi)) : break
##                    i += 1
##                if self.verbose : print("to %s"% pi)
##                shutil.copy(p,pi)
##            elif self.verbose : print "writing to %s"%p
##            write(p,s,self.check_on_write)
##            p1 = os.path.join(os.path.split(p)[0],'CMakeLists.txt')
##            addline=Add_line(p1,fct_name)
##            addline.update_file("SET\( *SOURCES")
##        elif self.verbose : 
##            print("%s directory\n  does not exist " %os.path.split(p)[0])

 

        
##if __name__ == "__main__" :
##    tb_name = "operator"
##    fcts = Nt2_tb_props(tb_name).get_fcts_list()
##    fcts = ["splat"]
##    ct = Create_tests(tb_name,
##                     fcts,
##                     modes=['scalar','simd'],
##                     parts= ["unit"],
##                     show=True,
##                     write_files=Fatxt_liste,
##                     check_on_write=True,
##                     backup_on_write=True,
##                     verbose=Fatxt_liste) 
##    ct.create_units()
