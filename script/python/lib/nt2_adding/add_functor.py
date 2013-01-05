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


"""utilities to add a functor to a toolbox
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

def create_unit(tb_name,fct_name,mode) :
    bg = Base_gen(tb_name,fct_name,mode)
    ghg = Global_header_gen(bg)
    r = ghg.get_gen_result()
    if True:#    try :
        dl = bg.get_fct_dict_list()
        for  rank, d in enumerate(dl) :
            origin ="types" if mode == 'scalar' else 'simd_types'
            types = bg.recover(origin,d["functor"],["real_convert_"])
            ret_arity = int(d["functor"]["ret_arity"])
            d_unit = d["unit"]
            for typ in types :
                thg = Type_header_test_gen(bg,d,typ,rank)
                r+=thg.get_gen_beg()
                if d_unit.get("specific_values",None) :
                    svt = Specific_values_test_gen(bg,d,typ,ret_arity,mode)
                    r += svt. get_gen_result()
                if d_unit.get("verif_test",None) :
                    vtg = Random_verif_test_gen(bg,d,typ,mode)
                    r += vtg. get_gen_result()
                r+=thg.get_gen_end()
        return r
##    except :
##        return None



class Add_functor_skel(Base_gen,Nt2_tb_struct) :
    def __init__(self,tb_name,fct_name,no_simd=False) :
        Base_gen.__init__(self, tb_name, fct_name, 'scalar')
        Nt2_tb_struct.__init__(self)
        self.tb_files  = self.get_rel_tb_unique_files(tb_name)
        self.fct_files = self.get_rel_tb_fcts_files(tb_name,fct_name)
        self.fct_dict = self.read_fct_info_dict(False)
        self.unique_files = self.get_rel_tb_unique_files(tb_name)
        self.no_simd = no_simd

    def add_files(self) :
        for fil in self.fct_files :
            if fil[:6]=='../../':
                self.create_include('../../include',fil)
            else :
                for pattern in self.Required_tree :
                    if  pattern ==fil[0:len(pattern)] :
                        print("--->%s ## %s"%('create_'+pattern,fil))
                        Add_functor_skel.__getattribute__(self,'create_'+pattern)(pattern,fil)
                        break
        print("--->%s ## %s"%('update_benches_and_units',fil))
        self.update_benches_and_units()
        print("--->%s ## %s"%('update_global_includes',fil))
        self.update_global_includes()

    def update_benches_and_units(self,option="update") :
        """ the files to be updated are:
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
            done, new_txt = self.insert_after("SET\( SOURCES",txt_orig,txt)
            if not done :
                print("Warning : line\n  %s\nis already in CMakelist.txt file"%txt )
            else :
                self.finalize(path,new_txt,"update")


    def update_global_includes(self,option="update") :
        """ the files to be updated is: ./$tb_name$.hpp
        ../$tb_name$.hpp' and ./include.hpp, are not to be modified after creation
        TO DO add action for "create"
        """
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        path = os.path.join(self.get_tb_path(),tb_name+'.hpp')
        txt_orig = read(path)
        txt = "#include <nt2/toolbox/%s/include/%s.hpp>"%(tb_name,fct_name)
        done, new_txt = self.insert_after("//<include>",txt_orig,txt)
        if not done :
            print("Warning : line\n  %s\nis already in include file"%txt )
        else :
            self.finalize(path,new_txt,"update")

    def create_include(self,pattern,fil,option="create") :
        """ create the include files in the global include files directory
        of nt2 if the toolbox is of 'sys' style and pattern is '../../include'
            also create the local toolbox functor include file if pattern is
            'include'
        """
        path = os.path.join(self.get_tb_path(),fil)
        sys = self.get_tb_style()
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        done = True
        if sys == 'sys' and pattern=='../../include' :
            txt = ["#include <nt2/toolbox/%s/include/%s.hpp>"%(tb_name,name)]
        elif pattern =='include' :
            txt = ["#include <nt2/toolbox/%s/function/%s.hpp>"%(tb_name,name)]
        else :
            done = False
        print("done = %s"%done)
        if done :
            new_txt = Headers(self.get_nt2_rel_tb_path(self.get_tb_name())+fil[:-4],"",inner=txt).txt()
            self.finalize(path,new_txt,option)

    def create_function(self,pattern,fil,option="create") :
        """ create functor def, scalar skel or simd arbo
        according to the pattern
        """
        f1 = fil[len(pattern)+1:]
        d,f = os.path.split(f1)
        if d == "" :
            print("------------->%s"%"gen_def")
            self.gen_def(fil,option)
        elif d[:4] == "simd" :
            if not self.no_simd :
                print("------------->%s"%"gen_simd")
                self.gen_simd(fil,option)
        elif d == "scalar" :
            print("------------->%s"%"gen_scalar")
            self.gen_scalar(fil,option)


    def create_doc(self,pattern,fil,option="create") :
        if fil[-3:] == '.py' :
            pass
        else :
            pass
        print(fil)
        print(pattern)
        self.finalize(fil,"","do nothing")

    def create_unit(self,pattern,fil,option="create") :
        """ create the unit tests for scalar
        (and simd version)
        """
        path = os.path.join(self.get_tb_path(),fil)
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        mode = 'scalar' if re.search('scalar',fil) else 'simd'
        new_txt = '\n'.join(create_unit(tb_name,name,mode))
        self.finalize(path,new_txt,option)
##        if not self.no_simd :
##            new_txt = '\n'.join(create_unit(tb_name,name,'simd'))
##            self.finalize(path,new_txt)

    def create_bench(self,pattern,fil,option="create") :
        """ create the benches for scalar
        (and simd version)
        """
        path = os.path.join(self.get_tb_path(),fil)
        mode = 'scalar' if re.search('scalar',fil) else 'simd'
        new_txt = self.gen_bench(mode)
        self.finalize(path,new_txt,option)
##        if not self.no_simd :
##            new_txt = self.gen_bench('simd')
##            self.finalize(path,new_txt)


    def gen_bench(self,mode,option="create") :
        """ auxilliary of create_bench
        """
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        txt = [
            "#include <nt2/toolbox/%s/include/%s.hpp>"%(tb_name,name),
            "#include <nt2/sdk/unit/benchmark.hpp>",
            "#include <cmath>",
            "" if mode=='scalar' else "typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;",
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// %s runtime benchmark for functor<%s_> from %s"%(mode,name,tb_name),
            "//////////////////////////////////////////////////////////////////////////////",
            "using nt2::tag::%s_;"%(name),
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// range macro",
            "//////////////////////////////////////////////////////////////////////////////",
            "#define RS(T,V1,V2) (T, %(T)s(V1) ,%(T)s(V2))"% {"T" :"" if mode=='simd' else "T"},
            "",
            ]
        txtf = [
            "",
            "#undef RS",
            "",
            ]
        d=self.fct_dict[0]
        d1 = d.get('bench',False)
        if d1 :
            pass
        else :
            d1 = { "arity"  : int(d["functor"]["arity"]),
                   "ranges" : d["unit"]["ranges"],
                   "types"  : d["functor"]['types'],
                   "type_defs": d["functor"]['type_defs'],
                   "call_types" :d["functor"]["call_types"],
                   }
            if d1["call_types"] == [] : d1["call_types"] = ["T"]
##            PrettyPrinter().pprint(d1)

        if True :
            call =  "  NT2_TIMING(nt2::tag::%s_,%s)" % (name,"%s")
            variety = { 'real_'         : ["float","double"],
                        'signed_int_'   : ["nt2::uint8_t","nt2::uint16_t","nt2::uint32_t","nt2::uint64_t"],
                        'unsigned_int_' : ["nt2::uint8_t","nt2::uint16_t","nt2::uint32_t","nt2::uint64_t"],
                        'float'         : ["float"],
                        'double'        : ["double"],
                        'float_'         : ["float"],
                        'double_'        : ["double"],
                        }
            r = []
            k=1
            for typ in d1["types"] :
               for t in variety[typ] :
                    r += ["namespace n%s {"%str(k) ]
                    k+=1;
                    r.append("  typedef %s T;"%t )
                    r += ["  "+td for td in d1["type_defs"]]
                    if mode == "simd" :
                        r += ["  typedef boost::simd::native<%s,ext_t> v%s;"%(ct,ct)  for ct in d1["call_types"] ]
                    tpl = "(RS(%s,%s,%s))"
                    rges = d1["ranges"].get(typ,d1["ranges"]["default"])
                    if not isinstance(rges[0][0],list) : rges = [rges]
                    prefix = "v" if mode == 'simd' else ''
                    calls = d1["call_types"]*d1["arity"] if len( d1["call_types"]) == 1 else d1["call_types"]
                    for rgen in rges :
                        param=""
                        for j,rge in enumerate(rgen) :
                            param += tpl%(prefix+calls[j],rge[0],rge[1])
                        r.append(call%param)
                    r += ["}"]
        else :
            pass
        txt += r+txtf;
        h = Headers(os.path.join(self.get_nt2_rel_tb_path(tb_name),'bench',mode),
                    name,inner=txt,guard_begin=[],guard_end=[]).txt()
        return h

    def gen_def(self,fil,option="create") :
        """ auxilliary of create_function
        create the functor definition file
        with the functor name
        """
        path = os.path.join(self.get_tb_path(),fil)
        arity = self.fct_dict[0]["functor"]["arity"]
        sys = self.get_tb_style()
        name = self.get_fct_name()
        tb_name = self.get_tb_name()
        namespace = "" if sys =='sys' else self.get_tb_name()
        namespacecolon2 = "" if sys=='sys' else namespace+'::'
        namespacebrak   = "" if sys=='sys' else namespace+' {'
        txt = [
            "#include <nt2/include/functor.hpp>",
            "#include <nt2/include/functor.hpp>",
            "#include <nt2/toolbox/%s/include.hpp>" % tb_name,
            "",
            "namespace nt2 {"+ namespacebrak,
            "  namespace tag",
            "  {",	
            "    struct %s_ {};" % name,
            "  }",
            "  NT2_FUNCTION_IMPLEMENTATION(%stag::%s_, %s, %s)" % (namespacecolon2,name,name,arity),
            "}",
            "",
            "#include <nt2/toolbox/%s/function/scalar/%s.hpp>" % (tb_name,name),
            "#include NT2_%s_INCLUDE(%s.hpp) "% (tb_name.upper(),name),
            "",
            ]
##        print("---------")
##        print("gen_def")
##        print("---------")
        new_txt = Headers(self.get_nt2_rel_tb_path(self.get_tb_name())+fil[:-4],"",inner=txt).txt()
        self.finalize(path,new_txt,option)

    def gen_simd(self,fil,option="create") :
        """ auxilliary of create_function
        create the functor skel file for the common version
        and the cascade include files for each simd variants
        with the functor name at the proper spots
        """
        path = os.path.join(self.get_tb_path(),fil)
##        print(path)
##        print("---------")
##        print("gen_simd")
##        print("---------")
        l = fil.split('/')
        if l[2] == 'common' :
            arity = self.fct_dict[0]["functor"]["arity"]
            a = int(arity)
            sys = self.get_tb_style()
            name = self.get_fct_name()
            txt = [
                "#include <nt2/sdk/meta/as_floating.hpp>",
                "",
                "/////////////////////////////////////////////////////////////////////////////",
                "// Implementation when type A0 is arithmetic_",
                "/////////////////////////////////////////////////////////////////////////////",
                "NT2_REGISTER_DISPATCH(tag::%s_, tag::cpu_,"% name,
                "                       (A0)(X),",
                "                       %s"% self.strlist('((simd_<arithmetic_<A0>,X>))',sep='',n=0,arity=a),
                "                      );",
                "",
                "namespace nt2 { namespace ext",
                "{",
                "  template<class X, class Dummy>",
                "  struct call<tag::%s_(%s),"% (name,self.strlist('tag::simd_<tag::arithmetic_, X>',n=0,sep=',',arity=a)),
                "              tag::cpu_, Dummy> : callable",
                "  {",
                "    template<class Sig> struct result;",
                "    template<class This,%s>" % self.strlist('class A%d',sep=',',arity=a),
                "    struct result<This(%s)> : meta::as_floating<A0>{};" % self.strlist('A%d',sep=',',arity=a),
                "",
                "    NT2_FUNCTOR_CALL(%s)"%arity,
                "    {",
                "      typedef typename NT2_RETURN_TYPE(%s)::type type;"%arity,
                "      // CODE HERE",
                "      return WHATEVER",
                "    }",
                "  };",
                "} }",
                "",
                ]
        else :
            arch =Nt2_archis_struct.get_archi(l[2])
            rppath =Nt2_archis_struct.get_archi(l[2]).get_previous_path(l[2]+'/'+l[3])
##            print("path %s"%(l[2]+'/'+l[3]))
##            print("prev %s"%rppath)
            txt = ["#include <nt2/toolbox/%s/function/simd/%s/%s.hpp>" %(self.get_tb_name(),rppath,self.get_fct_name())]
        new_txt = Headers(self.get_nt2_rel_tb_path(self.get_tb_name())+fil[:-4],"",inner=txt).txt()
        self.finalize(path,new_txt,option)

    def gen_scalar(self,fil,option="create") :
        """ auxilliary of create_function
        create the functor skel file for the scalar version
        with the functor name at the proper spots
        """
        path = os.path.join(self.get_tb_path(),fil)
        arity = self.fct_dict[0]["functor"]["arity"]
        a = int(arity)
        sys = self.get_tb_style()
        name = self.get_fct_name()
        txt = [
            "",
            "/////////////////////////////////////////////////////////////////////////////",
            "// Implementation when type A0 is arithmetic_",
            "/////////////////////////////////////////////////////////////////////////////",
            "NT2_REGISTER_DISPATCH(tag::%s_, tag::cpu_," % name,
            "                      %s," % self.strlist('(A%d)',sep='',arity=a),
            "                      %s"% self.strlist('(arithmetic_<A%d>)',sep='',arity=a),
            "                     )",
            "",
            "namespace nt2 { namespace ext",
            "{",
            "  template<class Dummy>",
            "  struct call<tag::%s_(%s)," % (name,self.strlist('tag::arithmetic_',n=0,sep=',',arity=a)),
            "              tag::cpu_, Dummy> : callable",
            "  {",
            "    template<class Sig> struct result;",
            "    template<class This,%s>" % self.strlist('class A%d',sep=',',arity=a),
            "    struct result<This(%s)> :"% self.strlist('A%d',sep=',',arity=a),
            "      boost::result_of<meta::floating(%s)>{};"%self.strlist('A%d',sep=',',arity=a),
            "",
            "    NT2_FUNCTOR_CALL(%s)"%arity,
            "    {",
            "      typedef typename NT2_RETURN_TYPE(%s)::type type;"%arity,
            "      // CODE HERE",
            "      return WHATEVER",
            "    }",
            "  };",
            "} }",
            "",
            ]
        new_txt = Headers(self.get_nt2_rel_tb_path(self.get_tb_name())+fil[:-4],"",inner=txt).txt()
        self.finalize(path,new_txt,option)

    def read_fct_info_dict(self,verbose = False) :
        p = self.get_fct_doc_path()
        if not exist(p) :
            print("%s does not exist: please create it before use" % p )
            raise SystemExit
##            self.__create_fct_info_dict(p,error='warn')
        s = '\n'.join(read(p))
        if verbose :
            print("py doc file for %s is:" % self.get_fct_name())
            print("=============================================")
            print(s)
            print("=============================================")
        exec("d = "+s)
        return d

    def strlist(self,tpl,n=1,sep = ", ",arity=1) :
        """ generation of parameter strings
        """
        s = tpl % (n*(0,))
        tpl =sep+tpl
        for i in range(1,arity) :
            s += tpl % (n*(i,))
        return s

    def insert_after(self,token, txt, line2add) :
        """ insertion of a line after a line
        containing a token in a list of lines
        """
        pattern = re.compile(line2add)
        def find_index(p) :
            for i,l in enumerate(txt) :
                if p.match(l) : return i+1
            return 0
        if find_index(pattern) :
          return (False,txt)
        else :
            #### match for token
            pattern = re.compile(token)
            i = find_index(pattern)
            if i != 0 : txt.insert(i,line2add)
            return (True,txt)

    def finalize(self,path,txt,option) :
        verbose = False
        print("======================")
        if option == "create" :
            if exist(path) :
                if verbose : print("file\n  %s\n exists"%path)
            else :
                if verbose : print("file\n  %s\nwill be created"%path)
                self.create(path,txt)
                if verbose : print("file\n  %s\nis now created"%path)
        elif option == "update" :
            if exist(path) :
                if verbose : print("file\n  %s\nwill be updated")
                self.update(path,txt)
                if verbose : print("file\n  %s\nis now updated"%path)
            else :
                if verbose : print("file\n  %s\n does not exist"%path)
        else :
            if verbose : print("I do not know what to do with: \n  %s\nplease help me!"%path)
        print("----------------------")


    def create(self,path,txt) :
        """ file path does not exist on entry
        is created on exit
        """
        write(path,txt,False)

    def update(self,path,txt) :
        """ file path does exist on entry
        is upated on exit, old version is in path+'~' file
        """
        shutil.move(path,path+'~')
        write(path,txt,False)

##def add_functor_skel(tb_name,fct_name) :
##    bg = Base_gen(tb_name,fct_name,'scalar')
##    dl = bg.get_fct_dict_list(verbose=False)
##    fct_files = Nt2_tb_struct.get_rel_tb_fcts_files(tb_name,fct_name)
##    tb_files  = Nt2_tb_struct.get_rel_tb_unique_files(tb_name)
##    PrettyPrinter().pprint(tb_files)
##    PrettyPrinter().pprint(fct_files)
##    tags = Nt2_tb_struct.get_rel_archis_tree()

##    for d in dl :
##        pass



if __name__ == "__main__" :
    tb_name = "combinatorial"
    fcts = ["pipo"]
    for fct_name in fcts :
        print fct_name
        afs = Add_functor_skel(tb_name,fct_name,no_simd=False)
        afs.add_files()


