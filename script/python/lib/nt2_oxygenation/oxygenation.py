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
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
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
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from py_doc        import Py_doc
sys.path.pop(0)

import re
import shutil
from pprint                          import PrettyPrinter

class Oxgen(Py_doc,Substitute) :
    def __init__(self, base_gen) :
        Py_doc.__init__(self,bg=base_gen)
        self.fct    = self.bg.get_fct_name()
        self.tb_name = self.bg.get_tb_name()
        self.mode    = self.bg.get_fct_mode()
        self.nfp =  Nt2_fct_props(self.tb_name,self.name,self.mode)
        self.types   = self.get_types()
##        self.collect_py_doc_global_data()
        self.collect_functor_data()
        
    def collect_functor_data(self) :
        self.df      = self.d.get("functor",{})       

class Nt2_oxygenation(Oxgen) :
    def __init__(self, base_gen) :
        Oxgen.__init__(self,base_gen)
##        self.save = True
##        self.p = None
##        self.fct = None
        self.namespace = "boost::simd" if self.is_boost() else "nt2" 
        
    def path(self) : return self.p
    
    def is_immutable(self,txt) :
        return txt.find('//COMMENTED') != -1
    
    def doxyfy(self) :
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
        self.txt_list = self.make_functor_ox()
        self.txt      = '\n'.join(self.txt_list)
##        show(self.txt_list)
        self.txt_list = self.make_tag_ox()
        self.txt      = '\n'.join(self.txt_list) 
##        show(self.txt_list)
        return self.txt_list
    
    def is_boost(self) :
        return self.tb_name.find('.') != -1

    def list_aliases(self) :
        pattern = re.compile("\(tag::"+self.fct+'_\s*,(.*),.*\)$')
        aliases=[]
        for l in self.txt_list :
            if l.find("(tag::"+self.fct+'_') != -1 :
                m = pattern.search(l)
                if m :
                    s = (m.group(1)).strip()
                    if s != self.fct :
                        aliases.append(s)
        return aliases
     
    def get_file_location(self) :
        self.p = self.nfp.get_def_path()
        self.fich = os.path.join(self.p,self.fct+'.hpp')
        if not exist(self.fich) :
            print("file: %s does not exist"%self.fich)
            self.p = self.nfp.get_redef_path()
            self.fich = os.path.join(self.get_redef_path(),self.fct+'.hpp')
        if not exist(self.fich) :
            print("and file: %s neither exist"%self.fich)
            self.p=None
    
    def make_tag_ox(self) :
        Tag_ox = [
            "/*!",
            " * \internal tag \endinternal",
            " * \\file",
            " * \\brief $action$ the tag $fct$_ of functor $fct$ ",
            " *        in namespace $namespace$::tag",
            " * \internal end_tag \endinternal",
            " */"
            ]
        self.action = "Define" if self.txt.find("boost::simd::"+self.fct) == -1 else "Bring"
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
        tag_ox = self.indent(Tag_ox,l)
        tag_ox = self.prepare(tag_ox)
        ll.extend(tag_ox)
        ll.extend(self.txt_list[j:])
        del self.action
        return ll

    def get_description(self) :
       desc = self.df.get("description",
                          ["TODO Put description here"])
##                           "this can be done by editing %s.py"%self.fct,
##                           "and adding a description section in the ",
##                           "functor part of the python dictionnary"])
       if isinstance(desc,str) :
           desc = desc.split('\n')
       desc = [ " * "+l for l in desc]    
       if isinstance(desc,list) :
           desc = '\n'.join(desc)
       return desc


    def strlist(self,tpl,n=1,sep = ", ",arity=1) :
        """ generation of parameter strings
        """
        s = tpl % (n*(0,))
        tpl =sep+tpl
        for i in range(1,arity) :
            s += tpl % (n*(i,))
        return s
  
    def compose_call(self) :
        ## up to now suppose all parameters have same type
        arity = int(self.df.get("arity",'1'))
        is_template = self.df.get("template",False)
        tpl = "class T," if is_template  else ""
        tpl_list =  self.strlist('class A%d',sep=',',arity=1)
        tpl_str  = "template <" + tpl + tpl_list +">"
        type_list =  self.strlist('A0',sep=',',arity=int(arity),n=0)
        result_str = "  meta::call<tag::"+self.fct+'_('+type_list+')>::type'
        param_list =  self.strlist('const A0 & a%d',sep=',',arity=int(arity),n=1)
        param_str  =  "  "+self.fct+"("+param_list+");"
        res = [ tpl_str,result_str,param_str]
        return '\n'.join(self.starize(self.indent(res,2)))
   
    def compose_parameters(self) :
        arity = int(self.df.get("arity",'1'))
        is_template = self.df.get("template",False)
        res = []
        for i in range(0,arity) :
            res.append("\\\\param a%s is the %s parameter of %s"%(str(i),self.ordinal(i+1),self.fct))
        res.append("\\\\return a value of the common type of the parameters")
        return '\n'.join(self.starize(res))+'\n'

    
    def make_functor_ox(self) :
        Functor_ox = [
            "",
            "/*!",
            " * \\internal functor \\endinternal",
            " * \\ingroup $tb_name$",
            " * \\defgroup euler_beta Euler beta function",
            " *",
            " * \\par Description",
            "$description$",
            " *",
            " * \\par Header file",
            " * ",
            " * \\code",
            " * #include <nt2/include/functions/$fct$.hpp>",
            " * \\endcode",
            " * ",
            " * $alias$",
            " * ",
            " * \\synopsis",
            " *",
            " * \\code",
            " * namespace $namespace$",
            " * {",
            "$call$",
            " * }",
            " * \\endcode",
            " *",
            "$parameters$"
            " *  ",
            " * \\internal end_functor \endinternal",
            "**/",
            "",
            ]
        aliases=self.list_aliases()
        self.alias = "\\\\alias "+', '.join(aliases) if len(aliases) else "" 
        self.description = self.get_description()
        self.parameters  = self.compose_parameters()
        self.call        = self.compose_call()
        j=0
        for ss in self.txt_list :
            if not len(ss) or (ss[0] in '/#') :
                j+=1
            else :
                break
        l = len(self.txt_list[j-1])-len(self.txt_list[j-1].lstrip())
        functor_ox = self.indent(Functor_ox,l)
        functor_ox = self.prepare(functor_ox)
        del self.parameters
        del self.call
        del self.description
        del self.alias
        ll = self.txt_list[:j]
        ll.extend(functor_ox)
        ll.extend(self.txt_list[j:])
        return ll            
    
    def prepare(self,txt) :
        if isinstance(txt, list) :
            txt = '\n'.join(txt)
        return self.replace(txt).split('\n')

    def indent(self,txt,l) :
        return [' '*l+t for t in txt]

    def starize(self,txt) :
        return [' * '+t for t in txt]
    
    def ordinal(self,i) :
      if i==0   : return "zeroth"
      elif i==1 : return "first"
      elif i==2 : return "second"
      elif i==3 : return "third"
      elif i==4 : return "fourth"
      elif i==5 : return "fith"
      else :      return str(i)+"th"
      
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
