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


"""Utilities to get toolboxes informations
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
import re
from files_utils       import read, exist
from nt2_toolbox_infos import Toolbox_infos
from re_list           import sub_list

class Fctor_infos :
    def __init__(self, tb_name, fct_name, mode, submode="") :
        if tb_name is Toolbox_infos :
            self.tbi=tb_name
        else :
            self.tbi = Toolbox_infos(tb_name)
        self.__fct_name = fct_name
        self.__mode = mode
        self.__archi = mode.split('/')[0]
        self.__archi_spec = mode.split('/')[1] if len(mode.split('/'))>1 else ""
        self.__submode = submode
        self.__fct_filename = fct_name.lower()
        self.__fct_arity = self.__read_arity()
        self.__fct_path =  self.__set_fct_path()
        self.__old_fctor_txt = self.__read_old_fctor_txt()
        
    def get_fct_name(self)      : return self.__fct_name
    def get_fct_filename(self)  : return self.__fct_filename
    def get_fct_arity(self)     : return self.__fct_arity
    def get_fct_mode (self)     : return self.__mode
    def get_fct_archi(self)     : return self.__archi #re.sub("simd/","",self.__mode)
    def get_fct_archi_spec(self): return self.__archi_spec
    def get_fct_submode(self)   : return self.__submode
    def get_fct_path(self)      : return self.__fct_path         
    def get_old_fctor_txt(self) : return self.__old_fctor_txt

    
    def get_validation_txt(self) :
        return self.__read_part(' *struct validate<','{','}',self.get_old_fctor_txt(),-1)

    def get_result_txt(self) :
        s = self.get_old_fctor_txt()
        tag_found = False
        call_found = False
        for i,l in enumerate(s) :
            if re.match(" *struct call<",l) : call_found = True
            if call_found :
                if re.match(" *typedef .* result_type;",l) :
                   return [s[i]]
                if re.match(" *template<class Sig>.*",l) :
                    deb = i
                    tag_found = True
                if tag_found :
                    if len(l) ==0 : return s[deb:i]+[""]
                    if  re.match(" *NT2_FUNCTOR_CALL_DISPATCH.*",l) : return s[deb:i]+[""]
                    if  re.match(" *NT2_FUNCTOR_CALL.*",l) : return s[deb:i]+[""]
        return None

    def get_fct_priv_part(self) :
        s = self.get_old_fctor_txt()
        tag_found = False
        for i,l in enumerate(s) :
            if re.match(' *private *: *',l) :
                deb = i
                tag_found = True
            if tag_found :
                if  re.match(" *} *} *",l) : return s[deb:i-1]
        return [ "" ] 
        
    def get_old_fct_dispatch(self) :
        r = self.__read_part(' *NT2_FUNCTOR_CALL_DISPATCH *\(','\(','\)',self.get_old_fctor_txt(),-1)
        if r is None : return ("",[])
        return self.__parse_dispatch(r) 

    def get_old_fct_dispatch_type(self) :
        return  self.get_old_fct_dispatch()[0]

    def get_old_fct_dispatch_list(self) :
        return  self.get_old_fct_dispatch()[1]

    def get_old_fct_call(self, dispatch_tag) :
        if dispatch_tag is not None :
            s = self.__read_part(' *NT2_FUNCTOR_CALL_EVAL_IF\( *\d *, *'+dispatch_tag+'.*','{','}',self.get_old_fctor_txt(),-1)
        else :
            s = self.__read_part(' *NT2_FUNCTOR_CALL\(.*','{','}',self.get_old_fctor_txt(),0)
            if s is not None : 
                s += self.get_fct_priv_part()
            else :
                s = [""]
        return s

    def get_header(self) :
        s = self.get_old_fctor_txt()
        for i,l in enumerate(s) :
            if re.match("namespace nt2.*",l) : return s[:i+2]
        return [""]
    

    def get_head_up_to_first_call(self) :
        s = self.get_old_fctor_txt()
        for i,l in enumerate(s) :
            if re.match(" *struct call<*.",l) : return s[:i-1]
        return  [""]            

    def get_footer(self) :
        return ["} }","","#endif"]

    def __set_fct_path(self) :
        def_path = self.tbi.get_def_path()
        fct_mode = self.get_fct_mode()
        fct_filename = self.get_fct_filename()
        fct_submode =self.get_fct_submode()
        return os.path.join(def_path,fct_mode,fct_submode,fct_filename+'.hpp')
    
    def __read_old_fctor_txt(self) :
        p = self. get_fct_path()
        r = read(p)
        r = sub_list("^tag::sse_$","",r)
        return r

    
    def is_subsidiary(self) :
        s = ' '.join(read(self.get_fct_path()))
        if re.match("#include <nt2/toolbox/"+
                     self.tbi.get_tb_name() +
                     '/function/simd/.*'+
                     self.get_fct_filename()+'.hpp> *',s) :
            return True
        else :
            return False

    def is_already_revised(self) :
        s = ' '.join(read(self.get_fct_path()))
        if re.search('/// Revised by ',s) :
            return True
        else :
            return False
        
    def no_restore(self) :
        s = ' '.join(read(self.get_fct_path()))
        if re.search('/// No restore -- hand modifications',s) :
            return True
        else :
            return False
        
    def is_empty(self) :
        for s in read(self.get_fct_path()) :
            if (len(s) != 0 and s[0] != "#") : return False
            if (len(s)>1 and (s[0]!="/" or s[1]!="/") ) : return False
        return True

    def is_unimplemented(self) :
        s = ' '.join(read(self.get_fct_path()))
        if re.search('/// Still unimplemented',s) :
            return True
        else :
            return False
       
    def __parse_dispatch(self,r) :
        st = ' '.join(r)
        st = re.sub(',\s',',',st)
        m = re.search(",.*(A\d).*,",st)
        d_on = m.groups()[0] if m else "A0"
        m = re.search("\( *\d, *\((.*)\)\) *\)",st)
        d_list = m.groups()[0].split(",") if m else []
        return (d_on,d_list)
    
    def __read_part(self,tag,ld,rd,s,offset):
        #        print "tag %s" % tag
        tag_found = False
        beg = -1
        end = -1
        nbl = 0
        nbr = 0
        #        show(s)
        for i,l in enumerate(s) :
            if not tag_found :
                m = re.match(tag,l)
                if m :
                    tag_found = True
                    beg = i+offset
                    m1 = re.search("("+ld+")",l)
                    m2 = re.search("("+rd+")",l)
                    nbl += len(m1.groups()) if m1 else 0
                    nbr += len(m2.groups()) if m2 else 0
                    #                    print "tag just found i %d -> %s"% (i,l)
                    if nbl and (nbl == nbr) : return [s[i]]
            else :
                m1 = re.search("("+ld+")",l)
                m2 = re.search("("+rd+")",l)
                nbl += len(m1.groups()) if m1 else 0
                nbr += len(m2.groups()) if m2 else 0
#                print "tag      found i %d -> %s (%s,%s)"% (i,l,nbl,nbr)
                if (nbl != 0 or nbr != 0 ) and nbl == nbr :
                    end = i+1
                    for j in range(beg,end) :
                        if re.match(tag,s[j]) : return s[j:end]
        return None

    def __read_arity(self) :
        p = os.path.join(self.tbi.get_def_path(),self.get_fct_filename()+'.hpp')
        s = read(p)
        for l in s :
            m = re.search('  NT2_FUNCTION_IMPLEMENTATION',l)
            if m :
                m = re.search('([0-9]+)\)',l)
                if m :
                    return int(m.groups()[0])
            else :
                m = re.search('  NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL',l)
                if m :
                    m = re.search('([0-9]+)\)',l)
                    if m :
                        return int(m.groups()[0])
                    
        return None
    
    def __read_validity(self) :
        return None

    def __str__(self) :
        r =  "get_fct_name()      %s\n" % self.get_fct_name()      
        r += "get_fct_filename()  %s\n" % self.get_fct_filename()  
        r += "get_fct_arity()     %d\n" % self.get_fct_arity()     
        r += "get_fct_mode ()     %s\n" % self.get_fct_mode ()     
        r += "get_fct_archi()     %s\n" % self.get_fct_archi()     
        r += "get_fct_submode()   %s\n" % self.get_fct_submode()   
        r += "get_fct_path()      %s\n" % self.get_fct_path()          
        r += "\nget_old_fctor_txt()\n    %s\n" % '\n    '.join(self.get_old_fctor_txt()) 
        r += "\nget_fct_priv_part()\n    %s\n" % '\n    '.join(self.get_fct_priv_part())
        ss = self.get_validation_txt()
        if ss :
            r += "\nget_validation_txt() %s\n" % '\n    '.join(self.get_validation_txt())
        else :
            r += "\nget_validation_txt()\n     %s\n" % "no validation"
        r += "\nget_result_txt()\n    %s\n" % '\n    '.join(self.get_result_txt())
        r += "\nget_old_fct_dispatch_type()\n    %s\n" % self.get_old_fct_dispatch_type()
        r += "\nget_old_fct_dispatch_list()\n    %s\n" % '\n    '.join(self.get_old_fct_dispatch_list())
        ss = self.get_old_fct_dispatch_list()
        if len(ss) :
            for s in ss :
                t = self.get_old_fct_call(s)
                if t :
                    r += "\nget_old_fct_call(%s)\n    %s\n" % (s,'\n    '.join(t))
        else :
            t = self.get_old_fct_call(None)
            if t :
                r += "\nget_old_fct_call(%s)\n    %s\n" % ("None",'\n    '.join(t))
        r += "\nget_header()\n    %s\n" % '\n    '.join(self.get_header()) 
        r += "\nget_head_up_to_first_call()\n     %s\n" % '\n    '.join(self.get_head_up_to_first_call()) 
        r += "\nget_footer()\n     %s\n" % '\n    '.join(self.get_footer()) 
        r += "\nis_subsidiary() \n %s\n" %  str(self.is_subsidiary())
        r += "\nis_already_revised() \n %s\n" %  str(self.is_already_revised())
        return r
    
if __name__ == "__main__" :
    print __doc__
    tbfi = Fctor_infos("arithmetic",'abs','simd/common','')
    print tbfi
    tbfi = Fctor_infos("arithmetic",'abs','scalar','')
    print tbfi
    tbfi = Fctor_infos("arithmetic",'abs','simd/sse','ssse3')
    print tbfi
