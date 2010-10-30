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


"""User utility to recover functor(s) from old Nt2
   usage:
           recover_usr_tb.py <tb_name>

   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write,exist
from mylogging  import Mylogging
from list_utils import show
from re_list    import sub_list

class Get_old :
    def __init__(self, tb_name='cephes',
                 mode = 'modify',
                 style='usr') :
        self.__tb_name    = tb_name
        self.__old_def_path   = os.path.join('/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/toolbox',tb_name,'function')
        self.__old_scal_path  = os.path.join(self.__old_def_path,'details/scalar')
        self.__new_def_path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox',tb_name,'function')
        self.__new_scal_path  = os.path.join(self.__new_def_path,'scalar')
        self.__dictio = self.create_dict()

    def get_tb_name(self)   : return self.__tb_name
    def get_old_def_path(self)  : return self.__old_def_path
    def get_old_scal_path(self) : return self.__old_scal_path
    def get_new_def_path(self)  : return self.__new_def_path
    def get_new_scal_path(self) : return self.__new_scal_path
    def get_dict     (self) : return self.__dictio
    def get_includes(self) :
        l = []
        for name in os.listdir(self.get_old_def_path()) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l

    def get_arity_and_tplness(self,pname) :
        if exist(pname) :
            s = read(pname)
            r = []
            for l in s :
                m = re.search('  NT2_FUNCTION_IMPLEMENTATION',l)
                if m :
                    #            print "l = %s " % l
                    m = re.search('([0-9]+)\)',l)
                    if m :
                        #                print " arity %s "% m.groups()[0]
                        return (int(m.groups()[0]),False)
                else :
                    m = re.search('  inline NT2_FUNCTION_RETURN_TYPE',l)
                    if m :
                        #            print "l = %s " % l
                        m = re.search('([0-9]+)\)',l)
                        if m :
                            #                print " arity %s "% m.groups()[0]
                            return (int(m.groups()[0]),True)
                    
        return ""
    
    def create_dict(self) :
        s = self.get_includes()
        #    show(s)
        d= {}
        for fct_name in s :
            #        print "fct_name : %s"% fct_name
            p1=os.path.join(self.get_old_def_path(),fct_name+'.hpp')
            #        print "p1 : %s" %p1
            arity,tplness = self.get_arity_and_tplness(p1)
            if arity != "" : d[fct_name]=(arity,tplness)
            #        print d[fct_name]
        return d    

    def create_arity_list(self) :
        r = []
        for fct_name in self.get_dict().keys():
            r.append(fct_name+(30-len(fct_name))*' '+str(self.get_dict()[fct_name][0]))
        return r
    
    def create_text(self) :
        write(self.get_tb_name()+'.txt',self.create_arity_list(),True)

    def add_functors(self,fct) :
        d = self.get_dict()
        for fct_name in d.keys() :
            print " adding %s, of arity %d" % (fct_name,d[fct_name][0])
            fct.add_functor(fct_name,d[fct_name][0])
            old=self.get_old_scalar_impl(fct_name)
            new=self.get_new_scalar_impl(fct_name)
            new=self.insert_call(fct_name,old,new)
            new=self.insert_validate(fct_name,old,new)
            new=self.insert_extern_C(fct_name,old,new)
            self.write_new_scalar_impl(fct_name, new)
        
    def get_old_scalar_impl(self,fct_name) :
        p = os.path.join(self.get_old_scal_path(),fct_name+'.hpp')
        s = read(p)
        #        show(s)
        return s
    def get_new_scalar_impl(self,fct_name) :
        p = os.path.join(self.get_new_scal_path(),fct_name+'.hpp')
        s = read(p)
        #        show(s)
        return s
    
    def write_new_scalar_impl(self,fct_name, new) :
        p = os.path.join(self.get_new_scal_path(),fct_name+'.hpp')
        s = write(p,new,False)
        #        show(s)
        return s
    
    def get_part(self,tag,s,offset):
        tag_found = False
        beg = -1
        end = -1
        nb= 1+offset
        #        show(s)
        for i,l in enumerate(s) :
            #            print "tag %s i %d -> %s"% (tag,i,l)
            if not tag_found :
                m = re.match(tag,l)
                if m :
                    tag_found = True
                    beg = i+offset
                    m1 = re.search("({)",l)
                    m2 = re.search("(})",l)
                    nbl = len(m1.groups()) if m1 else 0
                    nbr = len(m2.groups()) if m2 else 0
            else :
                m1 = re.search("({)",l)
                m2 = re.search("(})",l)
                nbl = len(m1.groups()) if m1 else 0
                nbr = len(m2.groups()) if m2 else 0
                nb += nbl-nbr
                if not nb :
                    end = i+1
                    return s[beg:end]
        
    def insert_extern_C(self,fct_name,old,new) :
        c = self.get_part(' *extern',old,0)
        if (c is not None) and len(c) != 0 :
            m1 = re.search("({)",c[0])
            m2 = re.search("(})",c[0])
            nbl = len(m1.groups()) if m1 else 0
            nbr = len(m2.groups()) if m2 else 0
            if nbl==nbr : c = [c[0]]
            new = new[:13]+c+new[14:]
            #    show(new)
        return new
    
    def insert_call(self,fct_name,old,new) :
        c = self.get_part(' *struct call',old,-1)
        if  (c is not None) and len(c) >= 4 :
            new = new[:21]+c[4:]+new[27:]
        #        show(new)
        return new

    def insert_validate(self,fct_name,old,new) :
        c = self.get_part(' *struct validate',old,-1)
        if (c is not None) and len(c) !=0 :
            d = [
                "  template<class Info>",
                "  struct validate<"+self.get_tb_name()+"::"+fct_name+"_,tag::scalar_(tag::arithmetic_),Info>"
                ]
            new = new[:13]+d+c[2:]+new[14:]
        #        show(new)
        return new

    def modify_tpl_defs(self) :
        for k in self.get_dict().keys() :
            if self.get_dict()[k][1] :
               p =  os.path.join(self.get_new_def_path(),k+'.hpp')
               s = read(p)
               pattern = " *NT2_FUNCTION_IMPLEMENTATION.*"
               rep = "  NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL("+k+")"
               s = sub_list(pattern,rep,s)
               show(s)
               write(p,s,False)


##def set_one(fct,fct_name,arity,pname) :
##    s = fct.read_functor(fct_name,'scalar')
##    print "adding functor %s of arity %d" % (fct_name, arity) 
##    src = os.path.join(pname,fct_name+'.hpp')
##    d = read(src)
##    v = get_validate(d)
##    c = get_call(d)
##    s = insert_validate_and_call(s,v,c,fct.get_tb_style(),fct.get_tb_name())
##    show(s)
##    fct.write_functor(fct_name,'scalar',s,False)
    
##def modify_toolbox(tb_name) :
##    fct = Functor(tb_name,mode='modify')
##    print ("opening toolbox %s" %fct.get_tb_name())+ \
##          " with %s mode" % fct.get_tb_mode()
##    return fct


if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
        old = Get_old(sys.argv[1])
        fct = Functor(old.get_tb_name(),mode='modify',style='usr')
        old.add_functors(fct)
        #        show(old.create_arity_list())
    else :
        print __doc__

sys.path.pop(0)
           
       

