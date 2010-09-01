#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for defining nt2 supported simd architectures 
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"


class Sse :
    """hierarchy of sse implementations"""
    Variants = {
        "common_sse" : "common",
        "sse2"   : "sse/common",
        "sse3"   : "sse/sse2",
        "ssse3"  : "sse/sse3",
        "sse4_1" : "sse/ssse3",
        "sse4_2" : "sse/sse4_1",
        "sse4a"  : "sse/ssse3",
        "avx"    : "sse/sse4_2",
        "xop"    : "sse/sse4a"
        }
    def __init__(self) :
        pass

    def previous(self,tag) :
        return Sse.Variants[tag]
    
    def __str__(self) :
        return str(Sse.Variants)

class Vmx :
    """hierarchy of sse implementations"""
    Variants = {
        "common_vmx"    : "common",
        "altivec"       : "common_vmx",
        "spu"           : "common_vmx"
        }
    def __init__(self) :
        pass
    
    def __str__(self) :
        return str(Sse.Variants)

    def previous(self,tag) :
        return Vmx.Variants[tag]
