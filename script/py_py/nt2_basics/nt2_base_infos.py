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


"""Nt2 base configuration infos
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
import re

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from nt2_archis_struct  import Nt2_archis_struct
from files_utils        import exist
sys.path.pop(0)

class Nt2_base_infos(object) :
    def __init__(self, author = None) :
        self.__nt2_path = self.get_nt2_dir()
        self.__author   = self.get_author() if author is None else author
        self.__toolbox_list = self.__mk_toolbox_list()
        self.__implanted_simd_archis = self.__find_implanted_simd_archis()
        self.__implanted_scalar_archis = self.__find_implanted_scalar_archis()
        
    def get_nt2_path(self) : return self.__nt2_path
    def get_author(self) : return self.__author
    def get_toolboxes_path(self) : return  os.path.join(self.get_nt2_path(),'nt2','toolbox')
    def get_toolbox_list(self) :return self.__toolbox_list
    def get_implanted_simd_archis(self) : return self.__implanted_simd_archis
    def get_implanted_scalar_archis(self) : return self.__implanted_scalar_archis
    def get_implanted_archis(self) : return self.__implanted_scalar_archis + self.__implanted_simd_archis

    def __str__(self) :
        r =  "nt2 is situated at %s" % self.get_nt2_path()
        r +="\ntoolboxes are in %s"  % self.get_toolboxes_path()
        r +="\nsupported simd archis are %s "  % str(Nt2_archis_struct.get_supported_archis_tags())
        r +="\nimplanted simd archis are %s "  % self.get_implanted_simd_archis()
        r +="\nimplanted scalar archis are %s "  % self.get_implanted_scalar_archis()
        r +="\nimplanted archis are %s "  % self.get_implanted_archis()
        r +="\ntoolboxes list is"
        for t in self.get_toolbox_list() :
           r += "\n  "+t 
        r +="\ncurrent <<signature>> is %s " % self.get_author()
        return r

    def __mk_toolbox_list(self) :
        l = []
        for name in os.listdir(self.get_toolboxes_path()) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l

    def __find_implanted_simd_archis(self) :
        return [os.path.join("simd",s) for s in Nt2_archis_struct.get_supported_archis_tags()
                if exist(os.path.join(self.get_toolboxes_path(),"arithmetic/function/simd",s))
                ]
    def __find_implanted_scalar_archis(self) :
        return [s for s in  Nt2_archis_struct.get_supported_archis_tags()
                if exist(os.path.join(self.get_toolboxes_path(),"arithmetic/function/",s))
                ]

    @classmethod
    def get_nt2_dir(cls) :
        """    nt2_dir() returns the absolute path to the directory under which
        stands the main nt2 directory
        The path is taken
            from the environment if "NT2_DIR" is defined
        or
            default to the absolute path in the current call directory up
            but non comprising the first /nt2/ occurence...
            This path can be sometimes erroneous
        or
            abort if the path does not contain /nt2/
        """
        try :
            d = os.environ["NT2_DIR"]
        except KeyError :
            d = sys.path[0] 
            if not d :
                d = os.getcwd()
            d1 = re.match("(.*/)nt2/",d)
            if not d1 :
                print("\n Environment chain 'NT2_DIR' is not defined")
                print("and your current path")
                print(d)
                print("does not contain /nt2/")
                print("sorry aborting")
                print("")
                print(__doc__)
                raise SystemExit
            else :
               dd=d1.groups()
            if len(dd)!=0 : d = dd[0]
        return os.path.expanduser(os.path.join(d,"nt2","include"))

    @classmethod
    def get_author(cls) : # TO DO something for zindows
        s = os.environ['HOME']
        return os.path.split(s)[1]
   
if __name__ == "__main__" :
    print(__doc__)
    nbi = Nt2_base_infos()
    print(nbi)
    print(sys.path)
