#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

"""Tools for playing (adding/removing) nt2 Functor templates
   to an existing nt2 toolbox
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import string
import re
##from tbox        import Toolbox
##from mylogging   import Mylogging
##from archi       import Sse, Vmx
##from identities  import whoami
##from nt2_env     import nt2_py_dir
##from list_utils  import show
##from file_utils  import read, write
##from headerfiles import Headers


    def __init__(self, tool_box_name,
                 mode = 'modify',
                 style='usr',
                 actions = None) :
        self.logger = Mylogging("nt2.fctor.Functor")
        Toolbox.__init__(self, tool_box_name, mode=mode, style=style)
        if not self.get_tb_status() and mode !='check' :
            self.logger.error(
                "\ntoolbox %s has invalid status\n" % self.get_tb_name() +
                "aborting"
                )
            raise SystemExit
        self.__fct_actions = Functor.Fct_actions if actions is None else actions
        self.ext='.hpp'
        
    def get_fct_actions(self) : return self.__fct_actions
        
    def add_functor(self,fct_name,fct_arity=1) :
        "adding a new functor"
        self.read_style()
        def strlist(tpl,n=1,sep = ", ") :
            s = tpl % (n*(0,))
            tpl =sep+tpl
            for i in range(1,fct_arity) :
                s += tpl % (n*(i,))
            return s
        if self.get_tb_style()[0] != 's' :
            tb_taggedname =  self.get_tb_name()+'::'+fct_name
        else :
            tb_taggedname = fct_name
        subs_dict = {
            "\$self.tb_name\$"              : self.get_tb_name(),
            "\$self.tb_nameupper\$"         : self.get_tb_name().upper(),
            "\$self.name\$"                 : fct_name,
            "\$self.arity\$"                : str(fct_arity),
            "\$self.class_list\$"           : strlist("class A%d"),
            "\$self.const_type_list\$"      : strlist("A0",0), 
            "\$self.const_class_list\$"     : strlist("class A0",0), 
            "\$self.type_list\$"            : strlist("A%d"),
            "\$self.parm_list\$"            : strlist("a%d"),
            "\$self.parm_list_j\$"          : strlist("a%d[j]"),
            "\$self.const_type_T_list\$"    : strlist("T",0),
            "\$self.const_type_n_t_list\$"  : strlist("n_t",0), 
            "\$self.gl_list\$"              : strlist("//    n_t a%d = load<n_t>(&data[0],%d);",2,"\n"),
            "\$self.call_list\$"            : strlist("const A%d& a%d",2),
            "\$self.const_type_call_list\$" : strlist("const A0& a%d",1),
            "\$self.tb_namespace\$"         : self.get_tb_namespace(),
            "\$self.tb_taggedname\$"        : tb_taggedname,
            "\$parms_type_and_ranges\$"     : strlist("(($parm$, -10, 10))",0,"\n//"+(17+len(fct_name))*' '),
            }
        for acts, datas in self.get_fct_actions().items() :
            action_names = self.get_fct_actions()[acts]
            for action_name, action_data in action_names.items() :
                action = getattr(Functor,action_name,None)
                action(self,fct_name,acts,subs_dict,action_data,check=True)

    def rmv_functor(self,fct_name) :
        "removing an existing functor"
        for acts, datas in self.get_fct_actions().items() :
            action_names = self.get_fct_actions()[acts]
            for action_name, action_data in action_names.items() :
                action_name = action_name[::-1]
                action = getattr(Functor,action_name,None)
                action(self,fct_name,acts,{},action_data,check=True)


    def add(self,fct_name,acts,subs_dict,action_data,check=True) :
        """add a file"""
        do_it = True
        fname = action_data["file"].replace('$fct_name$',fct_name)
        fct_name_path = os.path.abspath(os.path.join(self.get_tb_abs_path(),acts,fname))
        if acts != "" :
            rel_path = os.path.join(self.get_tb_pathfnt2(),acts)
        else :
            rel_path = 'nt2/include/functions'
            do_it = self.get_tb_style()[0]=='s'
        if do_it :
            tplname = '../tpl/'+action_data["tmpl"]
            # print  "action_data[tmpl] %s" % action_data["tmpl"]
            tpl_name_path = os.path.join(nt2_py_dir(),tplname)
            if "parm" in action_data.keys() :
                s = subs_dict["\$parms_type_and_ranges\$"]
                subs_dict["\$parms_type_and_ranges\$"] =  re.sub('\$parm\$', action_data["parm"], s)
            subs_dict["\$acts\$"] = acts
            inner_text = self.__treat(read(tpl_name_path),subs_dict)
            if "parm" in action_data.keys() :
                subs_dict["\$parms_type_and_ranges\$"] = s
            comment = action_data["cmmt"]
            flag    = action_data["head"]
            h = Headers(rel_path,fct_name,inner=inner_text,comment=comment)
            # print "fct_name_path %s" % fct_name_path
            h.write_header2(fct_name_path,flag=flag,check=check)
         
    def dda(self,fct_name,acts,subs_dict,action_data,check=True) :
        """remove a file: reverse of add"""
        fname = action_data["file"].replace('$fct_name$',fct_name)
        fct_name_path = os.path.abspath(os.path.join(self.get_tb_abs_path(),acts,fname))
        os.remove(fct_name_path)  

    def mdy(self,fct_name,acts,subs_dict,action_data,check=True) :
        """modify a file, inserting a line"""
        fname = action_data["file"].replace('$root_name$',self.get_tb_name())
        file2modify = os.path.join(self.get_tb_abs_path(),acts,fname)
        
        text = read(file2modify)
        subs_dict["\$self.tb_pathfnt2\$"]=self.get_tb_pathfnt2()
        subs_dict["\$fct_name\$"]=fct_name
        line2add = self.__treat(action_data["l2ad"], subs_dict) 
        token = action_data["tokn"]
        test, text = self.__add_line(text, line2add, token)
        if test :
            self.logger.info(
                "\nmodifying \n%s\nfor definition of functor %s\n" % (file2modify,fct_name)
                )
            write(file2modify,text,False)
        else :
            self.logger.warning(
                "\nFile %s was already included\n" % fct_name +
                "in file\n%s\n" %  file2modify
                )

    def ydm(self,fct_name,acts,subs_dict,action_data,check=True) :
        """modify a file (reverse of mdy): deleting a line"""
        fname = action_data["file"].replace('$root_name$',self.get_tb_name())
        file2modify = os.path.join(self.get_tb_abs_path(),acts,fname)
        text = read(file2modify)
        subs_dict["\$self.tb_pathfnt2\$"]=self.get_tb_pathfnt2()
        subs_dict["\$fct_name\$"]=fct_name
        line2rmv = self.__treat(action_data["l2ad"], subs_dict) 
        test, text = self.__rmv_line(text, line2rmv)
        if test :
            self.logger.info(
                "\nmodifying \n%s\nfor definition of functor %s\n" % (file2modify,fct_name)
                )
            write(file2modify,text,False)
        else :
            self.logger.warning(
                "\nFile %s was not present in file\n%s\n" %  (fct_name,file2modify)
                )



                
    def hie(self,fct_name,acts,subs_dict,action_data,check=True) :
        """create an include hierarchy for simd"""
        fname = action_data["file"].replace('$fct_name$',fct_name)
        path = os.path.join(self.get_tb_abs_path(),acts) 
        hierarchy = action_data["hier"]
        cmmt = action_data["cmmt"]
        head = action_data["head"]
        relpath = os.path.join(self.get_tb_pathfnt2(),acts)
        relpathm1 = '/'.join(relpath.split('/')[:-1])
        for base, prev in hierarchy.Variants.items() :
            file = os.path.join(path,base,fct_name+'.hpp')
            inner_text = ["#include <" + os.path.join(relpathm1, prev,fct_name + '.hpp>')]
            rpath = os.path.join(relpath,base)
            h = Headers(rpath,fct_name, inner=inner_text)
            h.write_header2(file,flag='full',check=check)
             
    def eih(self,fct_name,acts,subs_dict,action_data,check=True) :
        """delete an include hierarchy for simd(reverse of hie)"""
        path = os.path.join(self.get_tb_abs_path(),acts) 
        hierarchy = action_data["hier"]
        for base, prev in hierarchy.Variants.items() :
            file = os.path.join(path,base,fct_name+'.hpp')
            os.remove(file)
            
    def __treat(self,s, subs_dict) :
        """__treat substitutes all $self.<id>$ chains in the
           string s with the value of the variable self.<id> if it
           exist else leaves it as is"""
        if type(s) is str :
            for k,v in subs_dict.items() :
                s = re.sub(k,str(v),s)
            return s        
        elif type(s) is list :
            self.tb_name = self.get_tb_name()
            l= [] 
            for ss in s :
                l.append(self.__treat(ss, subs_dict))
            del self.tb_name
            return l
        
    def __add_line(self,text, line2add, token) :
        pattern = re.compile(line2add)
        def find_index(p) :
            for i,l in enumerate(text) :
                if p.match(l) : return i+1
            return 0
        if find_index(pattern) :
          return (False,text)
        else :
            #### match for token
            pattern = re.compile(token)
            i = find_index(pattern)
            if i != 0 :
                text.insert(i,line2add)
            return (True,text)

    def __rmv_line(self,text, line2rmv) :
        if line2rmv in text :
            text.remove(line2rmv)
            return (True,text)
        else :
            return (False,text)

    def read_functor(self,fct_name,type) :
        fct_name_path = os.path.join(self.get_tb_abs_path(),'function',type,fct_name+'.hpp')
        r = read(fct_name_path)
        return r

    def write_functor(self,fct_name,type,s,check) :
        fct_name_path = os.path.join(self.get_tb_abs_path(),'function',type,fct_name+'.hpp')
        r = write(fct_name_path,s,check)

if __name__ == "__main__":
    Mylogging.set_level('ERROR')
    tb = Functor("pipo3")
    tb.add_functor("zorro",fct_arity=2)
#    tb.add_functor("zzo",fct_arity=2)
    print "done"
#    tb.rmv_functor("zorro")
