#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for defining nt2 supported simd architectures 
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import re

class Scalar :
    Variants = {"" : ""}
    def __init__(self) : pass
    def __str__(self) :  return str(Scalar.Variants)
    def previous(self,tag) : return Scalar.Variants[tag]
    def mode() : return "scalar"
    
class Sse :
    """hierarchy of sse implementations"""
    Variants = {
        "common" : "common",
        "sse2"   : "sse/common",
        "sse3"   : "sse/sse2",
        "ssse3"  : "sse/sse3",
        "sse4_1" : "sse/ssse3",
        "sse4_2" : "sse/sse4_1",
        "sse4a"  : "sse/ssse3",
        "avx"    : "sse/sse4_2",
        "xop"    : "sse/sse4a",
        "fma4"   : "sse/xop"
        }
    def __init__(self) : pass
    def previous(self,tag) : return Sse.Variants[tag]
    def __str__(self) : return str(Sse.Variants)
    def mode() : return "simd"

class Vmx :
    """hierarchy of sse implementations"""
    Variants = {
        "common"        : "common",
        "altivec"       : "vmx/common",
        "spu"           : "vmx/common"
        }
    def __init__(self) : pass
    def __str__(self) : return str(Vmx.Variants)
    def previous(self,tag) : return Vmx.Variants[tag]
    def mode() : return "simd"

class Common :
    Variants = {"":""}
    def __init__(self) : pass
    def __str__(self) : return str(Common.Variants)
    def previous(self,tag) : return Common.Variants[tag]
    def mode() : return "simd"
 
class Archis :
    Supported = [ "scalar","sse", "vmx", "common"]
    Arbos = { "scalar": Scalar(),"sse" : Sse(), "vmx" :Vmx(), "common" : Common() }
    def supported(self) : return Archis.Supported
    def arbo(self, tag) : return Archis.Arbos[tag]
    def submodes(self, tag) :
        if re.search('/',tag) :
            return Archis.Arbos[tag.split('/')[-1]].Variants.keys()
        else :
            return [""]
#        return Archis.Arbos[tag.split('/')[-1]].Variants.keys()
    def __str__(self) :  return 'Supported archis are\n    '+'\n    '.join(Archis.Supported)
    
if __name__ == "__main__":
    a = Archis()
    for tag in a.supported() :
        print "%s -> %s"% (tag,a.arbo(tag))
        print "%s -> %s"% (tag,a.submodes(tag))
    print a
