#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for creating nt2 Functor templates
"""

import os
from identities import whosdad
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

class Mylogging :
    """printing options"""
    Level_tag = 'NOTSET'
    Level_val = 0
    Dvals = {
        'CRITICAL' : 50, 
        'ERROR'    : 40, 
        'WARNING'  : 30, 
        'INFO'     : 20, 
        'DEBUG'    : 10, 
        'NOTSET'   :  0 
        }
    Dtags = {
        50:'CRITICAL' ,  
        40:'ERROR'    ,  
        30:'WARNING'  ,  
        20:'INFO'     ,  
        10:'DEBUG'    ,  
        0 :'NOTSET'   ,  
        }
    def __init__(self, name, tag=None) :
        self.__name = name
        if type(tag) is str and tag.upper() in Mylogging.Dvals.keys() :
            Mylogging.Level_tag = tag.upper() 
            Mylogging.Level_val = Mylogging.Dvals[ Mylogging.Level_tag]
    
    def __print_if(self,msg,tag,dad) :
        if Mylogging.Level_val <= Mylogging.Dvals[tag] :
            print "%s - %s - %s " % (dad,self.__name, tag),
            print(msg)


    def critical(self,msg) : self.__print_if(msg,'CRITICAL',whosdad())  
    def error   (self,msg) : self.__print_if(msg,'ERROR'   ,whosdad())      
    def warning (self,msg) : self.__print_if(msg,'WARNING' ,whosdad())    
    def info    (self,msg) : self.__print_if(msg,'INFO'    ,whosdad())       
    def debug   (self,msg) : self.__print_if(msg,'DEBUG'   ,whosdad())      
    @classmethod    
    def set_level(cls,tag) : 
         Mylogging.Level_tag = tag
         Mylogging.Level_val = Mylogging.Dvals[tag]

    @classmethod    
    def get_level(cls) : return Mylogging.Level_val
    @classmethod    
    def get_tag  (cls) : return Mylogging.Level_tag

   
if __name__ == "__main__":
    logger = Mylogging('nt2', 'ERROR')
    print Mylogging.get_level()
    print Mylogging.get_tag()
    logger.critical('critical')
    logger.error('error')
    logger.warning('warn')
    logger.debug('debug')
