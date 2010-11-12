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


"""User utility to add functor(s) to an existing Nt2 toolbox
   usage:
           add_functor <tool_box_name> <functor_name> <arity>
         
   <tool_box_name> (mandatory) is the name of the toolbox, it must
                   a valid C++ variable name (please use lower case)

   <functor_name>  (mandatory) is the name of the functor to be created

   [arity]         [optionnal] is the number of parameters taken by the
                   functor (1 is the default)

   or
           add_functor @<data_file_name>

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
#sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'source'))


import sys
import re
from fctor      import Functor
from file_utils import read,write
from list_utils import show
from mylogging  import Mylogging
from headerguards import Guard
from nt2_base     import Nt2
from banner       import Banner

def gen_proper_guard(path,name) :
    g = Guard(path,name)
    return g.get_guard_begin()


def dir_traversal(path='./', banner="") :
    # os.path.walk can be used to traverse directories recursively
    # to apply changes to a whole tree of files.
    def callback( arg, dirname, fnames ):
        for file in fnames:
            if file[-4:] =='.hpp' :
                fname =os.path.join(dirname,file)
                s =read(fname)
                v = gen_proper_guard(dirname[46:],file[:-4])
                if  len(s)>7 and s[8] != "" and s[8] !=v[0] :
                    print "file %s, dir %s " %(file,dirname[46:])
                    print "correct  %s "%v[0]
                    print "existing %s "%s[8]
                    s1 = []
                    s1.extend(banner)
                    s1.extend(v)
                    s1.extend(s[10:])
                    write(fname,s1,False)
##                    print "******************"
##                    show(s1)
##                    print "=================="
    arglist = []
    os.path.walk(path,callback,arglist)




if __name__ == "__main__" :
    nt2 = Nt2()
##   show(gen_proper_guard(nt2.get_path_from_nt2(),'toto.hpp'))
    fr = "nt2/toolbox"
    dir_traversal(os.path.join(nt2.get_path_to_nt2(), fr),Banner().get_banner())
#sys.path.pop(0)
           
       

