#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
from __future__         import print_function

"""Tools for defining nt2 supported simd architectures
   Currently defined are
    scalar : no simd
    sse    : 
    vmx
    common
   class Archi  define  
     supported()    : list of supported tags
     arbo(tag)      : directory hierarchy of supported tags within nt2
     submodes(tag)  : submodes associated with a tag
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 27/11/2010 Jean-thierry Lapreste"
__license__   = "Python"

__all__ = ['Nt2_archis']

import re
import os
from pprint import PrettyPrinter

class Swar(object) :
    """ base class for simd (and scalar) hierarchies
        In derivation please redefine if different:
          Variants: a dictionnary of variants tags keys and predecessors access list values
                    (see SSe for example)
          Mode: Which is currently 'scalar' or 'simd'  but could be anything else if needed
          Tag : Which is the tag defining the architecture  as 'vmx', 'sse', or '' (for scalar)
    """
    Variants = {"" : [""]}
    Mode = "scalar"
    Tag  = "swar"
    def __init__(self) :
        pass

    @classmethod
    def get_variants(cls) : return cls.Variants
    
    @classmethod
    def get_mode(cls) : return cls.Mode

    @classmethod
    def __str__(cls) :
        return PrettyPrinter().pformat(cls.Variants)

    @classmethod
    def get_previous(cls,tag) :
        return cls.Variants[tag][-1]

    @classmethod
    def get_previous_path(cls,tag) :
        """
        return the relative path
        for  inclusion if no proper implementation is furnished for
        this archi variant
        """
        if re.search('./',tag) :
            a,tag = os.path.split(tag)
        l = cls.Variants[tag]
        if len(l) == 2 :
            return os.path.join(l[0],l[1])
        else :
            return l[0]
    
    @classmethod
    def get_rel_tree(cls) :
        """
        return all the necessary relative paths
        for proper  different implementations
        of a functor
        """
        return sorted([ os.path.join(cls.Mode,cls.Tag,l) for l in cls.Variants.keys()])
            
   

class Scalar(Swar) :
    """hierarchy of scalar implementations:
    there is only one..."""
    Tag = ""
    def __init__(self) : Swar.__init__(self)

    
class Sse(Swar) :
    """hierarchy of sse implementations"""
    Tag = "sse"
    Variants = {
        "common" : ["common"],
        "sse2"   : ["sse","common"],
        "sse3"   : ["sse","sse2"],
        "ssse3"  : ["sse","sse3"],
        "sse4_1" : ["sse","ssse3"],
        "sse4_2" : ["sse","sse4_1"],
        "sse4a"  : ["sse","ssse3"],
        "avx"    : ["sse","sse4_2"],
        "xop"    : ["sse","sse4a"],
        "fma4"   : ["sse","xop"],
        }
    Mode = "simd"
    def __init__(self) : Swar.__init__(self)

class Vmx(Swar) :
    """hierarchy of sse implementations"""
    Tag="vmx"
    Variants = {
        "common"        : ["common"],
        "altivec"       : ["vmx","common"],
        "spu"           : ["vmx","common"]
        }
    Mode = "simd"
    def __init__(self) : Swar.__init__(self)

class Common(Swar) :
    Mode = "simd"
    Tag  = "common"
    def __init__(self) :  Swar.__init__(self)
 
class Nt2_archis_struct :
 #   Supported = [ "scalar","sse", "vmx", "common"]
    Archs = { "scalar"  : Scalar,
              "sse"     : Sse,
              "vmx"     : Vmx,
              "common"  : Common }

    @classmethod
    def get_rel_archis_tree(cls, tags=None) :
        """
        return the relative tree of all archis whose tags are in tags
        all supported archis if tag is None
        """
        if tags is None : tags = cls.Archs.values()
        r = []
        for a in tags : r += a.get_rel_tree()
        return sorted(r)

    @classmethod
    def get_supported_archis_tags(cls) :
        return sorted(cls.Archs.keys())

    @classmethod
    def get_archi(cls, arch) :
        return cls.Archs[arch]

    @classmethod
    def get_submodes(cls, arch) :
        return [sm[-1] for sm in cls.get_archi(arch).get_variants().values() if len(sm)==2]

    def __str__(self) :
        return 'Supported archis are\n    '+'\n    '.join(Nt2_archis_struct.get_supported_archis_tags())
    
if __name__ == "__main__":
    pp = PrettyPrinter()
    pp.pprint(" Swar variants   %s " % Swar().get_variants())
    pp.pprint(" Swar mode       %s " % Swar().get_mode())
    pp.pprint(" Scalar variants %s " % Scalar().get_variants())
    pp.pprint(" Scalar mode     %s " % Scalar().get_mode())
    pp.pprint(" Scalar rel_tree %s " % Scalar().get_rel_tree())
    pp.pprint(" Sse variants    %s " % Sse().get_variants())
    pp.pprint(" Sse mode        %s " % Sse().get_mode())
    pp.pprint(" Sse rel_tree    %s " % Sse().get_rel_tree())
    pp.pprint(" Vmx variants    %s " % Vmx().get_variants())
    pp.pprint(" Vmx mode        %s " % Vmx().get_mode())
    pp.pprint(" Vmx rel_tree    %s " % Vmx().get_rel_tree())
#    pp.pprint(" Sse truc        %s " % Sse.get_previous_path('simd/sse/sse3'))
    pp.pprint(Nt2_archis_struct.get_rel_archis_tree())
    pp.pprint(Nt2_archis_struct())
