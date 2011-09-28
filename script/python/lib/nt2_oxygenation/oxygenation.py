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
        
    def get_description(self) :
        desc = self.df.get("description",
                           ["TODO Put description here"])
##                           "this can be done by editing %s.py"%self.fct,
##                           "and adding a description section in the ",
##                           "functor part of the python dictionnary"])
        if isinstance(desc,str) : desc = desc.split('\n')
        desc = [ " * "+l for l in desc]    
        if isinstance(desc,list) : desc = '\n'.join(desc)
        return desc
        
class Nt2_oxygenation(Oxgen) :
    def __init__(self, base_gen,strip=True) :
        Oxgen.__init__(self,base_gen)
        self.strip = strip
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
                self.save = False
                return
            if self.txt.find('/*!') != -1 :
                print("%s file was already oxygenated"%self.fct)
                if not self.strip :
                    return
                else :
                    self.txt_list = self.strip_old()
        self.txt_list = self.make_functor_ox()
        self.txt      = '\n'.join(self.txt_list)
##        show(self.txt_list)
        self.txt_list = self.make_tag_ox()
        self.txt      = '\n'.join(self.txt_list) 
        self.txt_list =self.suppress_double_blank(self.txt_list)
        self.txt_list = self.make_file_ox()
        self.txt      = '\n'.join(self.txt_list)
        return self.txt_list
    
    def is_boost(self) :
        return self.tb_name.find('.') != -1

    def list_aliases(self) :
        pattern = re.compile("\(tag::"+self.fct+'_\s*,(.*),.*\)$')
        aliases=[]
        for l in self.txt_list :
            if (l.find("(tag::"+self.fct+'_') != -1) and (l.find("_TPL")==-1) :
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
            " * \\brief $action$ the tag $fct$_ of functor $fct$ ",
            " *        in namespace $namespace$::tag",
            "**/"
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


    def strlist(self,tpl,n=1,sep = ", ",arity=1) :
        """ generation of parameter strings
        """
        s = tpl % (n*(0,))
        tpl =sep+tpl
        for i in range(1,arity) :
            s += tpl % (n*(i,))
        return s
  
    def compose_call(self) :
        special_synopsis = self.df.get("special_synopsis",False)
        if special_synopsis :
            res = special_synopsis
        else :
            equalparams = self.df.get("equalparams",True)
            arity = int(self.df.get("max_arity",self.df.get("arity",'1')))
            is_template = self.df.get("template",False)
            tpl = "class T," if is_template  else ""
            if equalparams :
                tpl_list =  self.strlist('class A%d',sep=',',arity=1)
                type_list =  self.strlist('A0',sep=',',arity=int(arity),n=0)
                param_list =  self.strlist('const A0 & a%d',sep=',',arity=int(arity),n=1)
            else :
                tpl_list =  self.strlist('class A%d',sep=',',arity=arity)
                type_list =  self.strlist('A%d',sep=',',arity=int(arity),n=1)
                param_list =  self.strlist('const A%d & a%d',sep=',',arity=int(arity),n=2)
            tpl_str  = "template <" + tpl + tpl_list +">"
            result_str = "  meta::call<tag::"+self.fct+'_('+type_list+')>::type'
            param_str  =  "  "+self.fct+"("+param_list+");"
            res = [ tpl_str,result_str,param_str]
        return '\n'.join(self.starize(self.indent(res,2)))
   
    def compose_parameters(self) :
        special = self.df.get("special",[])
        arity = int(self.df.get("max_arity",self.df.get("arity",'1')))
        is_template = self.df.get("template",False)
        res = []
        if arity == 1 :
            param_0 =  self.df.get("param_0","")
            param = "\\\\param a0 the unique parameter of %s"%self.fct
            res.append(param)
        else :    
            for i in range(0,arity) :
                parami =  self.df.get("param_"+str(i),"")
                param = "\\\\param a%s the %s parameter of %s"%(str(i),self.ordinal(i+1),self.fct)
                if len(parami) : param += ', '+'\n'.join(parami)
                res.append(param)
        if is_template :
            res.append("")
            tpl_param = "\\\\param T a template parameter of %s"%self.fct
            res.append(tpl_param)
        ret =  self.df.get("return",[])
        res.append("")
        if len(ret) :
            res.append("\\\\return "+'\n'.join(ret))
        elif self.fct[0]=='i' :
            res.append("\\\\return an integer value")
        elif "reduction" in special :    
            res.append("\\\\return always a scalar value")
        elif arity == 1 :
            res.append("\\\\return a value of the same type as the parameter")
        else :
            res.append("\\\\return a value of the common type of the parameters")
        return '\n'.join(self.starize(res))+'\n'

    def compose_notes(self) :
        res = ['\par Notes',
               'In SIMD mode, this function acts elementwise on the inputs vectors elements','\par']
        special = self.df.get("special",[])
        if "predicate" in special :
            res.extend(["This is a predicate operation. Such operations return bool in scalar mode,",
                        "but not in SIMD mode.","\par",
                        "The return type in SIMD mode is the common type of the parameters and is",
                        "a 'signed boolean' type. This means that in this case True has all its bits",
                        "sets to one. This is to facilitate masking operations. You are invited to",
                        "consult the rationale."])
        if "reduction" in special :
            res.extend(["This is a reduction operation. As such it has not real interest outside",
                        "SIMD mode.","\par",
                        "Such an operation has always a scalar result which translate a property",
                        "of the whole SIMD vector.","\par",
                        "If usable and used in scalar mode, it reduces to the operation as acting",
                        "on a one element vector."])
        if "swar" in special :
            res.extend(["This is a swar operation. As such it has not real interest outside",
                        "SIMD mode.","\par",
                        "Such an operation is a transform of an SIMD vector,that will return",
                        "vectors obtained on a non necessarily elementwise basis from the inputs"
                        "elements","\par",
                        "If usable and used in scalar mode, it reduces to the operation",
                        "on a one element vector."])             
        return '\n'.join(self.starize(res))+'\n'
        
    def make_file_ox(self) :
        File_ox = [
            "/*!",
            " * \\file",
            "**/",
            ]
        j=0
        for ss in self.txt_list :
            if (len(ss) and ss[0] in '#') :
                break
            else :
                j=j+1
        r =self.txt_list[:j]
        r.extend(File_ox)
        r.extend(self.txt_list[j:])
        return r
    
    def make_functor_ox(self) :
        Functor_ox = [
            "/*!",
            " * \\ingroup %s"%self.tb_name.replace('.','_'),
            " * \\defgroup $fct$ $fct$ function",
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
            "$alias$",
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
            "$notes$"
            " *  ",
            "**/",
            " ",
            ]
        aliases=self.list_aliases()
        plural = "es" if len(aliases) > 1 else ""
        self.alias = " * \par Alias"+plural+" \n * \\\\arg "+'\n * \\\\arg '.join(aliases) if len(aliases) else "" 
        self.description = self.get_description()
        self.parameters  = self.compose_parameters()
        self.call        = self.compose_call()
        self.notes       = self.compose_notes()
        j=0
        for ss in self.txt_list :
            if not len(ss) or (ss[0] in '/#') :
                j+=1
            else :
                break
        l = len(self.txt_list[j-1])-len(self.txt_list[j-1].lstrip())
        functor_ox = self.indent(Functor_ox,l)
        functor_ox = self.suppress_blank(self.prepare(functor_ox))
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
      
    def strip_old(self) :
        r = []
        pattern1 = re.compile("\s*/\*[!\*]")
        pattern2 = re.compile("\s*\*{1,2}/") 
        in_dox = False
        for l in self.txt_list :
            if not in_dox :
                in_dox = pattern1.match(l) ##l[:3]=='/*!'
            if not in_dox :
                r.append(l)
            if in_dox :
                in_dox = not(pattern2.match(l)) ##l[:3]=='**/')
        return r        
             
    def suppress_blank(self,txt_list) :            
        return [l for l in txt_list if len(l)]
    
    def suppress_double_blank(self,txt_list) :
        for i,l in enumerate(txt_list) :
            if re.match('\s*$',l) : txt_list[i]=""
        pattern =re.compile("\n{3,}")
        txt = '\n'.join(txt_list)
        txt = re.sub(pattern,"\n\n",txt)
        return txt.split('\n')
    
if __name__ == "__main__" :
    pass
