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


"""transitionnal doc conversion utlity
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
import datetime
import shutil
from files_utils                     import write, exist
from nt2_base_infos                  import Nt2_base_infos
from pprint                          import PrettyPrinter
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
##from pprint                          import PrettyPrinter
##from unit_base_gen                   import Base_gen
##from unit_global_header_gen          import Global_header_gen
##from unit_type_header_gen            import Type_header_test_gen 
##from unit_specific_values_gen        import Specific_values_test_gen 
##from unit_random_verif_gen           import Random_verif_test_gen

Dict_doc_tpl = [
    "{                                                                                            ",
    "    'functor' : {       ## intrinsics values related to functor                              ",
    "        'arity'         : $arity_str$,      ## functor number of parameters                  ",
    "        'ret_arity'     : $ret_arity_str$,  ## must be '0' or omitted if not a tuple         ", 
    "        'types'         : $types_list$,     ## list of types string                          ",
    "        'rturn'         : $rturn_dict$,     ## ditionary of return types                     ",
    "        'call_types'    : $call_types_list$,## types used in call ['T']*arrity if omitted    ",
    "        'type_defs'     : $type_def_list$,  ## supplementary typedefs                        ",
    "        }, ## end of functor                                                                                  ",
    "    'unit'    : {       ## informations for creating unit tests                              ",
    "        'global_header' : { ## header of machin.cpp                                          ",
    "            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp             ",
    "            'stamp'       : 'modified by $author$ the $date$', ## modification stamp         ",
    "            'included'    : $included$,     ## list of supplementary include directives'     ",
    "            'notes'       : $notes$,        ## list of strings that will be included in a    ",
    "                                            ## global comment                                ",
    "            },                                                                               ",
    "        'specific_values' : $specific_values$  ## dictionary of parameters and values        ",
    "                                               ## to be tested                               ",
    "        'ranges'          :  $ranges$  ## dictionary of ranges for random tests              ",
    "        'verif_test'      : ## verification dictionary{                                      ",
    "            'property_call'   : $property_call$  ## dictionary of calls per types            ",
    "            'property_value'  : $property_value$ ## dictionary of alternate calls            ",
    "            'ulp_thresh'      : $ulp_thresh$     ## validity thresholds(s)                   ",
    "        },  ## end of unit                                                                   ",
    "},                                                                                           ",
]                                                                         

def construct_new_dict_0_1(od) :
    nl = []
    if type(od) is dict : od = [od]
    author = Nt2_base_infos.get_author()
    date = datetime.datetime.now().strftime("%d/%m/%Y")
    for d in od :
        n = {}
        nf = {} 
        nf[ 'arity'      ] = str(d.get('arity',1))
        nf[ 'ret_arity'  ] = '2' if "random_tuple" in d else '0'
        nf[ 'types'      ] = (d.get('types',[]))    
        nf[ 'rturn'      ] = (d.get('rturn',{'default': 'T',})) 
        nf[ 'call_types' ] = (d.get('buftp',[]))
        nf[ 'type_defs'  ] = (d.get('tpdef',[]))

        n["functor"]=nf
        nu = {}
        nug = {}
        nug['first_stamp'] = d.get("stamp",'created  by ' + author +' the ' +date)
        nug['stamp']       = 'modified by ' + author +' the ' +date
        nug['included']    = (d.get('incld',[]))
        nug['notes']       = (d.get('notes',[]))
        nu['global_header'] = nug
        
        nu['specific_values'] = (d.get('specv',{}))
        nu['ranges']          = (d.get('rnges',{}))
        nuv = {}
        if d.get('tcall',None) :
            nuv['property_call'] = None
            nuv['property_value']= { "default" : [d.get('tcall',None)] }
            nuv['ulp_thresh'] = { "default" : ['0']}
        elif d.get('tuple',None) :
            nuv['property_call'] = None
            nuv['property_value']= { "default" :[d.get('tcal0',None),d.get('tcal1',None)]}
            nuv['ulp_thresh'] =  { "default" : ['0','0']}
        elif d.get('verif',None) :
            def mklist(l) : return l if type(l) is list else [l]
            nuv['property_call'] = { "default" :mklist(d.get('verif',None))}
            nuv['property_value']= { "default" :mklist(d.get('verva',None))} 
            nuv['ulp_thresh'] =    { "default" :mklist(d.get('verth','0'))}
            
        nu['verif_test']= nuv

        n["unit"]=nu
        n["version"]='0.1'
        nl.append(n)
    return nl

   
def write_new_doc(tb_name,fct_name) :
    if mv_old_doc(tb_name,fct_name) :
        nfp = Nt2_fct_props(tb_name,fct_name)
        od =nfp.get_fct_dict_list()
        p = nfp.get_fct_doc_path()
        nd = construct_new_dict_0_1(od)
        pp = PrettyPrinter()
        s=pp.pformat(nd)
        print s
        write(p,s,False)
    else :
        print "doc is already updatted"
        
def mv_old_doc(tb_name,fct_name) :
    nfp = Nt2_fct_props(tb_name,fct_name)
    od =nfp.get_fct_dict_list()
    if type(od) is dict : od = [od]
    if not od[0].get("version",False) :
        p = nfp.get_fct_doc_path()
        [p0,p1]=os.path.split(p)
        p2 = os.path.join(p0,fct_name+'_0_0.py')
        shutil.copy(p,p2)
        return True
    return False

if __name__ == "__main__" :
##    PrettyPrinter().pprint(Nt2_fct_props.get_rel_tb_tree("zorglub"))
##    PrettyPrinter().pprint(Nt2_fct_props.get_rel_tb_tree())
##    old_dict = Nt2_fct_props("ieee","successor").get_fct_dict_list()
##    PrettyPrinter().pprint(old_dict)
##    PrettyPrinter().pprint(construct_new_dict_0_1(old_dict))
##    write_new_doc("ieee","bitfloating")

    tb_name = "combinatorial"
    l = Nt2_tb_props(tb_name).get_fcts_list()
    PrettyPrinter().pprint(l)
#    l = ['gcd']
    for fct in l :
        print fct
        write_new_doc(tb_name,fct)
sys.path.pop(0)
