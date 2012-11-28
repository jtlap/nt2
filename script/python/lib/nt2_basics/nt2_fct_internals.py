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
from __future__         import print_function

"""Utilities to get parts of nt2 functors implementation files
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import re
from pprint            import PrettyPrinter

class Nt2_fct_internals() :
    """ dig in implementation to recover parts of functions
    """

    @classmethod
    def get_dispatch_types(self, txt) :
        """\
        get list of tags types used for specialization in an implementation
        file of a functor passed as txt (list of lines)
        """
        r = []
        for t in txt :
            m = re.search('\s*struct\s*call\s*<tag::.*\((.*)\)',t)
            if m :
                g = m.group(1)
                g = re.sub("tag::","",g);
                r.append(g.split(','))
        return r


    @classmethod
    def get_calls(self, txt, typ='.*') :
        """\
        get dictionnary of calls for a type tag or a list of types tags
        default to getting all calls
        """
        if isinstance(typ,list) : typ = '|'.join(typ)
        l = self.extract_parts('\s*struct\s*call<.*\(tag::(%s)\),' % typ,'{','}',txt,-1)
        d = {}
        for t in l :
            if t[2] != 0 :
                d[t[0]] = txt[t[1]-5:t[2]]
        return d


    @classmethod
    def get_returns(self,txt, typ='.*') :
        """ dictionnary of returns types key in tags types"""
        lc = self.get_calls(txt, typ)
        r = {}
        for c in lc.keys() :
            r[c]=self.get_return(lc[c])
        return r


    @classmethod
    def get_return(self,txt) :
        tag_found = False
        for i,l in enumerate(txt) :
            if re.match("\s*typedef.*\sreturn_type;",l) :
                return [txt[i]]
            if re.match("\s*typedef.*\sresult_type;",l) :
                return [txt[i]]
            if re.match("\s*template<class\sSig>.*",l) :
                deb = i
                tag_found = True
            if tag_found :
                if len(l) ==0 : return txt[deb:i]+[""]
                if  re.match("\s*NT2_FUNCTOR_CALL.*",l) : return txt[deb:i]+[""]
        return None



    @classmethod
    def get_fct_priv_part(self,txt) :
        tag_found = False
        for i,l in enumerate(txt) :
            if re.match(' *private *: *',l) :
                deb = i
                tag_found = True
            if tag_found :
                if  re.match(" *} *} *",l) : return txt[deb:i-1]
        return [ "" ]

    @classmethod
    def get_header_indices(self,txt) :
        for i,l in enumerate(txt) :
            if re.match("namespace nt2.*",l) : return (0,i)
        return (0,-1)

    @classmethod
    def get_header(self,txt) :
        return txt[hi[0],hi[1]]

    @classmethod
    def get_head_up_to_first_call(self,txt) :
        for i,l in enumerate(txt) :
            if re.match("\s*struct call<*.",l) : return txt[:i-3]
        return  [""]

    @classmethod
    def get_head_up_to_first_dispatch(self,txt) :
        for i,l in enumerate(txt) :
            if re.match("\s*NT2_REGISTER_DISPATCH\(.*",l) : return txt[:i-3]
        return  [""]

    @classmethod
    def get_footer(self,txt) :
        m = re.search("(}\s*}\s*#endif.*)",'\n'.join(txt))
        if m :
            return m.group(1).split('\n')
        else :
            return ["} }","","#endif"]

    @classmethod
    def get_extern_C(self,txt) :
        l = [self.extract_part('\s*extern\s"C"','{','}',txt,-1)]
        d = {}
        for t in l :
            if t[2] != 0 :
                #                print(txt[t[1]:t[2]])
                return txt[t[1]:t[2]]+[""]
        return []


    @classmethod
    def extract_parts(cls,tag,ld,rd,s,offset) :
        """tag      : is regexp indicating the txt part beginning
        ld and rd: are a pair of bracket to be matched after the tag
        s        : is the text to dig in
        offset   : indicate if some lines must be taken before tag
        """
        l = []
        prev = 0
        b = -1
        e = 0
        i = 0
        while True :
            g,b,e = cls.extract_part(tag,ld,rd,s,offset)
            if b==e : break
            s = s[e:]
            l.append([g,b+prev,e+prev])
            prev += e
            i = i+1
            if i>100 :
                print("pb more than 100 calls in one implementation !")
                raise SystemExit
        return l

    @classmethod
    def extract_part(cls,tag,ld,rd,s,offset):
        """
        tag      : is regexp indicating the txt part beginning
        ld and rd: are a pair of bracket to be matched after the tag
        s        : is the text to dig in
        offset   : indicate if some lines must be taken before tag
        """
        #        print "tag %s" % tag
        tag_found = False
        beg = -1
        end = -1
        nbl = 0
        nbr = 0
        g = ""
        #        show(s)
        for i,l in enumerate(s) :
            if not tag_found :
                m = re.match(tag,l)
                if m :
                    try :
                        g = m.group(1)
                    except :
                        g = []
                    tag_found = True
                    beg = i+offset
                    m1 = re.search("("+ld+")",l)
                    m2 = re.search("("+rd+")",l)
                    nbl += len(m1.groups()) if m1 else 0
                    nbr += len(m2.groups()) if m2 else 0
#                    print("tag just found i %d -> %s"% (i,l))
                    if nbl and (nbl == nbr) : return (g,i,i+1) #[s[i]]
            else :
                m1 = re.search("("+ld+")",l)
                m2 = re.search("("+rd+")",l)
                nbl += len(m1.groups()) if m1 else 0
                nbr += len(m2.groups()) if m2 else 0
#                print("tag      found i %d -> %s (%s,%s)"% (i,l,nbl,nbr))
                if (nbl != 0 or nbr != 0 ) and nbl == nbr :
                    end = i+1
                    for j in range(beg,end) :
                        if re.match(tag,s[j]) : return (g,j,end) #s[j:end]
        return (None,0,0)


if __name__ == "__main__" :
    from nt2_fct_props import Nt2_fct_props
    nfp = Nt2_fct_props("trigonometric","acos")
    s = nfp.get_fct_text()
    PrettyPrinter().pprint(Nt2_fct_internals.get_dispatch_types(s))
    PrettyPrinter().pprint( Nt2_fct_internals.get_calls(s))
    PrettyPrinter().pprint(Nt2_fct_internals.get_returns(s))
    PrettyPrinter().pprint(Nt2_fct_internals.get_footer(s))
    PrettyPrinter().pprint(Nt2_fct_internals.get_head_up_to_first_call(s))
    PrettyPrinter().pprint(Nt2_fct_internals.get_head_up_to_first_dispatch(s))
