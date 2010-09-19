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


"""utility to recover toolboxes  from old Nt2
   usage:
           recover_sys_toolboxes 

   <data_file_name> is the name of a text file the contain of which is:

          <tool_box_name>
          <functor_name_1> [arity_1]
            ...
          <functor_name_n> [arity_n]

          in this case, all the n functors will be added to the toolbox.
          Note: empty of fully blank lines are ignored
   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write, exist, mkdir
from mylogging  import Mylogging
from list_utils import show
from mk_tb_txt  import create_txt

def get_struct(s,struct_name) :
    """ return the part of the list containing the template class
    of given name"""
    struct_found = False
    beg = -1
    end = -1
    nb= 0
    for i,l in enumerate(s) :
        if not struct_found :
            m = re.match(" *struct "+struct_name,l)
            if m :
                struct_found = True
                beg = i-1
        else :
           m1 = re.search("({)",l)
           m2 = re.search("(})",l)
           nbl = len(m1.groups()) if m1 else 0
           nbr = len(m2.groups()) if m2 else 0
           nb += nbl-nbr
           if not nb :
               end = i+1
               return s[beg:end]

def create_impl_dirs(dirs=None) :
    if dirs is None :
        dirs = [
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/elliptic/function/scalar/impl/horner",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/trigonometric/function/scalar/impl/trigo",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/elliptic/function/simd/impl/horner",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/trigonometric/function/scalar/impl/invtrig",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/exponential/function/scalar/impl/expo",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/exponential/function/simd/impl/logs",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/exponential/function/simd/impl/expo",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/exponential/function/simd/impl/horner",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/trigonometric/function/simd/impl/invtrig",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/exponential/function/scalar/impl/logs",
            "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox/trigonometric/function/simd/impl/trigo",
            ]
        for d in dirs :
            if not exist(d) :
                os.makedirs(d)
    

class Recover :
    """recovery of the sys toolboxes from old nt2"""
    Toolbox_List = [
        "trigonometric","predicates","ieee","arithmetic","bitwise","fuzzy","hyperbolic",
        "exponential","reduction","elliptic","bessel","combinatorial","euler"]
    Pname = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/core/numeric/function/details'
    Iname = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/include/functions'
    SseVariants = ["sse2","sse3","ssse3","sse4_1","sse4_2","sse4a","avx","xop","fma4"]
    Variant_beg = [
        "#include <nt2/sdk/meta/strip.hpp>",
        "",
        "namespace nt2 { namespace functors",
        "{",
        "  template<class Extension,class Info>",
        ]
    Variant_end = [
        "} }",
        "" ,    
        "#endif",
        ]
    Dirs_to_create = {}
    def __init__(self,tb_list=None) :
       self.__tb_list = Recover.Toolbox_List if tb_list == None else tb_list

    def get_tb_list(self) : return self.__tb_list  

    def get_list(self,tb_name) :
        name = os.path.join(Recover.Iname,tb_name+'.hpp')
        txt_name = tb_name+'.txt'
        s = read(name)
        s = create_txt(tb_name,s)
        write(txt_name,s, False)
        return s
    
    def create_tb_texts(self) :
        for tb_name in self.get_tb_list() :
            s = get_list(tb_name)
            s = create_txt(tb_name,s)
            write(tb_name+'.txt',s, True)

    def treat_one_tb(self,s,mode) :
        if mode == 'simd' :
            path = mode+'/common'
        else :
            path = mode
        tb_name = s[0]
        fct = Functor(tb_name,'modify','sys')
        for ss in s[1:] :
            ss = re.sub('\b',' ',ss)
            if len(ss) == 0 : continue
            l = ss.split()
            if len(l) == 0 : continue
            fct_name = l[0]
            arity = 1 if len(l) <=1 else int(l[1])
            fct.add_functor(fct_name,arity)
            st = fct.read_functor(fct_name,path)
            print "in toolbox %s adding functor %s of arity %d" % (tb_name,fct_name, arity) 
            sys.stdout.flush()
            src = os.path.join(Recover.Pname,path,fct_name+'.hpp')
            if exist(src) :
                d = read(src)
                v = get_struct(d,"validate")
                c = get_struct(d,"call")
                i = self.get_includes(d,tb_name,mode,fct.get_path_to_nt2())
                st = self.insert_validate_and_call(st,v,c,i,
                                                   fct.get_tb_style(),
                                                   fct.get_tb_name(),
                                                   fct_name,
                                                   mode)
                #            show(st)
                fct.write_functor(fct_name,path,st,False)

        
    def treat_variant(self,s,variant) :
        mode = "simd"
        tb_name = s[0]
        fct = Functor(tb_name,'modify','sys')
        for ss in s[1:] :
            ss = re.sub('\b',' ',ss)
            if len(ss) == 0 : continue
            l = ss.split()
            if len(l) == 0 : continue
            fct_name = l[0]
            arity = 1 if len(l) <=1 else int(l[1])
            path = "simd/sse/"+variant
            fct.add_functor(fct_name,arity)
            st = fct.read_functor(fct_name,path)
            src = os.path.join(Recover.Pname,path,fct_name+'.hpp')
            if exist(src) and (os.path.getsize(src) > 1536) :
                print "adding functor %s of arity %d in variant %s (size %s)" % (fct_name, arity, variant,os.path.getsize(src))
                sys.stdout.flush()
                #                print"orig-----------------"
                #show(st)
                d = read(src)
                #                print"src-----------------"
                #show(d)
                v = get_struct(d,"validate")
                c = get_struct(d,"call")
                i = self.get_includes(d,tb_name,mode,fct.get_path_to_nt2())
                st = self.insert_variants(st,v,c,i,
                                          fct.get_tb_style(),
                                          fct.get_tb_name(),
                                          fct_name,
                                          mode)
                #                print"avant-----------------"
                #show(st)
                #                print"apr-Aès-----------------"-b
                fct.write_functor(fct_name,path,st,False)

        
    def treat_all(self,mode) :
        if type(mode) is str :
            for tb_name in self.get_tb_list() :
                s = self.get_list(tb_name)
                print "treating %s in mode %s" % (tb_name, mode)
                self.treat_one_tb(s,mode)
        else :
            for sm in mode :
               self.treat_all(sm) 

    def treat_variants(self) :
        for tb_name in self.get_tb_list() :
            s = self.get_list(tb_name)
            print "treating %s in mode %s" % (tb_name, "simd")
            for variant in Recover.SseVariants :
                self.treat_variant(s,variant)
        
    def insert_validate_and_call(self,d,v,c,i,style,tb_name,fct_name,mode) :
        if c is not None :
            if mode == "scalar" :
                d = d[:20] + c[3:]+d[27:]
            else :
                d = d[:22] + c[4:]+d[30:]
        if v is not None :
            v[1]= "  struct validate<"
            if style == 'usr' : v[1] += tb_name+"::"
            if mode == "scalar" :
                v[0]= "  template<class Info>"
                v[1] += fct_name+"_,tag::scalar_(tag::arithmetic_),Info>"
            elif mode == "simd" :
                v[0]= "  template<class Extension,class Info>"
                v[1] += fct_name+"_,tag::simd_(tag::arithmetic_,Extension),Info>"
            d = d[:14]  + v + d[14:]
        else :
            d = d[:14]  + ["  //  no special validate for %s" % fct_name, ""] + d[14:]
        if i is not None :
            d = d[:11]+i+d[11:]
        d = self.modify_result_of(d,mode) 
        return d

    def insert_variants(self,d,v,c,i,style,tb_name,fct_name,mode) :
        if c is not None :
            d1 = d[:10] + Recover.Variant_beg 
            d1 += ["  struct call<%s_,tag::simd_(tag::arithmetic_,Extension),Info>" %fct_name ]
            d1 += c[2:]+ Recover.Variant_end 
            d1 += d[13:]
        else :
            return d
        if v is not None :
            v[1]= "  struct validate<"
            if style == 'usr' : v[1] += tb_name+"::"
            v[0]= "  template<class Extension,class Info>"
            v[1] += fct_name+"_,tag::simd_(tag::arithmetic_,Extension),Info>"
            v[2]=""
            d1 = d1[:14]  + v + d1[14:]
        else :
            d1 = d1[:14]  + ["  //  no special validate for %s" % fct_name, ""] + d1[14:]
        if i is not None :
            d1 = d1[:12]+i+d1[12:]
        d1 = self.modify_result_of(d1,mode)    
        return d1

    def modify_result_of(self,d,mode) :
        if mode == "simd" :
            target1 = "{ typedef A0 type; };"
            nst1=" : meta::strip<A0>{};"
            for i,ld in enumerate(d) :
                if re.search("struct result<This\(",ld):
                    if re.search(target1,ld) :
                        d[i]=ld.replace(target1,nst1)
                        if (i+1<len(d)) and re.search(target1,d[i+1]) :
                            d[i+1]=d[i+1].replace(target1,nst1)
                d[i] = ld.replace("Dummy","Info")
        else :
            target1 ="typename nt2::meta::scalar_of<A0>::type,"
            nst1 = "A0,"
            for i,ld in enumerate(d) :
                if re.search(target1,ld) :
                    d[i]=ld.replace(target1,nst1)
        return d    

    def provide_dir(self,path,directory) :
        d = os.path.join(path,"nt2",directory)
        print "directory to provide %s" %d
        if d in Recover.Dirs_to_create :
            Recover.Dirs_to_create[d]+=1
        else :
            Recover.Dirs_to_create[d]=0

##        if not exist(d) : mkdir(d)

    def get_includes(self,s,tb_name,mode,path) :
        """ return the list of includes associated to the text"""
        r = []
        for ls in s :
            m = re.match("^#include <nt2/core/numeric/.*impl.*/(.*)>$",ls)
            if m :
                directory = "toolbox/"+tb_name+'/function/'+mode+'/impl/'+m.groups()[0]
                self.provide_dir(path,directory[:-4])
                lr = "#include <nt2/include/%s>" % directory
                r.append(lr)
                r.append("//  MIGRATION WARNING you have to provide the file for the previous include from")
                r.append("//  "+ ls[10:-1])
                r.append("//  of the old nt2")
                continue
            m = re.match("^#include <nt2/core/numeric/function/(.*)>$",ls)
            if m :
                lr = "#include <nt2/include/functions/"+m.groups()[0]+">"
                ##            print "lr %s " % lr
                r.append(lr)
        r.append("")
        return r
        
if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    r = Recover(tb_list=["arithmetic"])
    r.treat_all(["scalar","simd"])
    r.treat_variants()
##    show(r.Dirs_to_create)
##    create_impl_dirs()
sys.path.pop(0)
           
       

