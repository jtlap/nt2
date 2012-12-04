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


"""Utilities to get nt2 toolboxes structure
this give toolbox independant informations
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
import re
from pprint           import PrettyPrinter
from files_utils      import read, exist
from iter_utils       import flatten
from nt2_base_infos   import Nt2_base_infos
from nt2_archis_struct       import Nt2_archis_struct
sys.path.pop(0)

def populate_actions() :
    actions={}
    actions[os.path.join('..','..','include','functions')] = {
    'add' : {
        'name'    :'$fct_name$.hpp',   # direct include file for fct
        'tmpl'    :'fct_direct_include.tpl', # "#include <nt2/toolbox/$tb_name$/include/$fct_name$.hpp>"
        'commt'   : "//",
        'head'    : "full",
        },
    'mdy'   : {
        "file_name" : "$tb_name$.hpp",
        "line_2add" : "#include <$self.tb_pathfnt2$/include/$fct_name$.hpp>",
        "token"     : "//<\include>",
        },
    }

    actions[os.path.join("bench","scalar")] = {
    'add'   : {
        "file_name" : "$fct_name$.cpp",
        "tmpl_name" : "mk_cppbench.tpl",
        "str_cmmt" : "//",
        "head" : 'banner+inner',
        "parm" : "nt2::uint32_t",
        },
    'mdy'   : {
        "file" : "CMakeLists.txt",
        "l2ad" : "   $fct_name$.cpp",
        "tokn" : "SET\( SOURCES",
        },
    }
    actions[os.path.join("bench","simd")] = {
    'add'   : {
        "file" : "$fct_name$.cpp",
        "tmpl" : "mk_cppbench.tpl",
        "cmmt" : "//",
        "head" : 'banner+inner',
        "parm" : "boost::simd::native<float,nt2::tag::sse_>",
        },
    'mdy'   : {
        "file" : "CMakeLists.txt",
        "l2ad" : "  $fct_name$.cpp",
        "tokn" : "SET\( SOURCES",
        },
    }
    actions[os.path.join("unit","scalar")] = {
    'add'   : {
        "file" : "$fct_name$.cpp",
        "tmpl" : "mk_cppunit.tpl",
        "cmmt" : "//",
        "head" : 'banner+inner'
        },
    'mdy'   : {
        "file" : "CMakeLists.txt",
        "l2ad" : "  $fct_name$.cpp",
        "tokn" : "SET\( SOURCES",
        },
    }
    actions[os.path.join("unit","simd")] = {
    'add'   : {
        "file" : "$fct_name$.cpp",
        "tmpl" : "mk_cppunit_simd.tpl",
        "cmmt" : "//",
        "head" : 'banner+inner'
        },
    'mdy'   : {
        "file" : "CMakeLists.txt",
        "l2ad" : "  $fct_name$.cpp",
        "tokn" : "SET\( SOURCES",
        },
    },

    actions[os.path.join("doc","source")] = {
    "add"   : {
        "file" : "$fct_name$.rst",
        "tmpl" : "mk_doc.tpl",
        "cmmt" : "  ",
        "head" : 'inner'
        },
    },

    actions[os.path.join("doc","source")] = {
    "add"   : {
        "file" : "$fct_name$.py",
        "tmpl" : "mk_doc.py",
        "cmmt" : "##",
        "head" : 'inner'
        },
    },
    #actions.update(Archis.Required_fcts_actions)
    return actions



class Nt2_tb_struct(Nt2_archis_struct) :
    """ subdirectory structure required by a toolbox """
    Required_directories = ['','function', 'bench', 'unit','cover','doc','src','include','cmake']
    Required_tree = {
        '.'       : [],
        'function': "archis",
        'bench'   : ['scalar','simd'],
        'unit'    : ['scalar','simd'],
        'cover'   : ['scalar','simd'],
        'doc'     : ['source'],
##        'src'     : [],
##        'include' : []
        }
    Secundary = os.path.join('include','nt2','toolbox')
    Required_primary_unique_files = {
        '.'         : ["py_data.py","CMakeLists.txt"],
        'bench'     : ['CMakeLists.txt',os.path.join('simd','CMakeLists.txt'),os.path.join('scalar','CMakeLists.txt')],
        'unit'      : ['CMakeLists.txt',os.path.join('simd','CMakeLists.txt'),os.path.join('scalar','CMakeLists.txt')],
        'cover'     : ['CMakeLists.txt',os.path.join('simd','CMakeLists.txt'),os.path.join('scalar','CMakeLists.txt')],
        }
    Required_secundary_unique_files = {
        '.'         : ["$tb_name$.hpp", "include.hpp"],
        '..'        : ["$tb_name$.hpp"],
        'function'  : "archis",
        }

    Required_fcts_files = {
        os.path.join('..','..','include','functions') : ['$fct_name$.hpp'],
        'function': "archis",
        'bench'   : [os.path.join('simd','$fct_name$.cpp'),os.path.join('scalar','$fct_name$.cpp')],
        'unit'    : [os.path.join('simd','$fct_name$.cpp'),os.path.join('scalar','$fct_name$.cpp')],
        'doc'     : ['$fct_name$.py', os.path.join('source','$fct_name$.rst')],
        'include' : ["$fct_name$.hpp"],
        }
    Subkeys = ['\$tb_name\$','\$fct_name\$']

    Functions_actions = populate_actions()

    """
    get_nt2_rel_tb_path(to) : return the relative path to 'function', 'bench', 'unit', 'doc', 'src', 'include'
                              according the string value (class method)

    get_rel_tb_tree()       : return the list of needed subdirectories in a toolbox  (class method)
    """

    def __init__(self) :
        pass
        #        Nt2_tb_struct.Functions_actions = populate_actions()

    @classmethod
    def __get_tb_from_md_path(cls,tb_name) :
        return os.path.join("include","nt2","toolbox",tb_name)

    @classmethod
    def get_rel_tb_unique_files(cls,tb_name) :
        l = []
        for d in cls.Required_primary_unique_files.keys() :
            for f in cls.Required_primary_unique_files[d] :
                if '$' in f :
                    f = re.sub('\$tb_name\$',tb_name,f)
                df = os.path.join(d,f)
                l.append(df)
        for d in cls.Required_secundary_unique_files.keys() :
            if d == "function" :
                pass
            else :
                for f in cls.Required_secundary_unique_files[d] :
                    if '$' in f :
                        f = re.sub('\$tb_name\$',tb_name,f)
                    df = os.path.normpath(os.path.join(cls.Secundary,tb_name,d,f))
                    l.append(df)
        return l

    @classmethod
    def get_rel_tb_fcts_files(cls,tb_name,fct_name) :
        l = []
        for d in cls.Required_fcts_files.keys() :
            if d == "function" :
               l.append(os.path.join(cls.__get_tb_from_md_path(tb_name),d,fct_name+'.hpp'))
               tags = cls.get_rel_archis_tree()
               for tag in tags :
                  df = os.path.join(cls.__get_tb_from_md_path(tb_name),d,tag,fct_name+'.hpp')
                  l.append(df)
            else :
                for f in cls.Required_fcts_files[d] :
                    if '$' in f :
                        f = re.sub('\$fct_name\$',fct_name,f)
                        f = re.sub('\$tb_name\$',tb_name,f)
                    df = os.path.join(d,f)
                    l.append(df)
##                    print("%s, %s -> %s" % (d,f,df))
        return l

    @classmethod
    def get_previous_rel_path(cls,tag) :
        if re.match('scalar',tag) :
            return ""
        else :
            d,f = os.path.split(tag)
            d,f = os.path.split(d)
        archi =  Nt2_tb_struct.get_archi(f)
        return os.path.join("simd",archi.get_previous_path(tag))


    @classmethod
    def get_nt2_rel_tb_path(cls, tb_name, to = '') :
        return os.path.join('nt2/toolbox/',tb_name,cls.grtp(to))

    @classmethod
    def get_rel_tb_tree_list(cls, tb_name,root=None) :
        if isinstance(root,str ) :
            if root == "function" :
                a = [os.path.join(cls.__get_tb_from_md_path(tb_name),root,arch) for arch in cls.get_rel_archis_tree()]
            elif not (root in  cls.Required_tree) :
                return []
            else :
                a = [os.path.join(root,arch) for arch in cls.Required_tree[root] ]
            return ([root] if root != 'function' else [os.path.join(cls.__get_tb_from_md_path(tb_name),root)] )+a
        else :
            if root is None : root = Nt2_tb_struct.Required_tree
            z = [ cls.get_rel_tb_tree_list(tb_name,root=r) for r in root]
            return list(flatten(z))


    @classmethod
    def grtp(cls, to = '',mode='') :
        """ return realative path from the toolbox to 'to' and 'mode'
        to can be 'function', 'bench', 'unit', 'doc', 'src', 'include'
        and for some mode can be 'scalar' or 'simd'
        """
        if to =='' : return ''
        if mode == '' : return to
        return os.path.join(to,mode)



    #######################################################################################
    ## private methods
    #######################################################################################



    @classmethod
    def rxp(cls, s) :
        return string.replace('$','\$',s)
    @classmethod
    def strip(cls, s, c) :
        return string.replace('c','',s)

    @classmethod
    def substitute(cls, f) :
        for s in cls.Subkeys :
            return string.replace(f,'\$',s)



if __name__ == "__main__" :
##    PrettyPrinter().pprint(Nt2_tb_struct.get_rel_tb_tree_list("zorglub"))
##    PrettyPrinter().pprint(Nt2_tb_struct.Required_fcts_files)
##    PrettyPrinter().pprint(Nt2_tb_struct.Required_unique_files)
##    PrettyPrinter().pprint(Nt2_tb_struct.Functions_actions)


##    PrettyPrinter().pprint(Nt2_tb_struct.get_rel_tb_tree_list("ieee"))
##    PrettyPrinter().pprint(Nt2_tb_struct.get_rel_tb_unique_files("ieee"))
    PrettyPrinter().pprint(Nt2_tb_struct.get_rel_tb_fcts_files("ieee","frexp"))

