#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for reading and writing list of strings
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 27/11/2010 Jean-thierry Lapreste"
__license__   = "Python"

__all__ = ['rm','exist','read','write','mkdir']

import os
import sys
import string
import inspect

def rm(file):
    """suppress the file"""
    os.remove(file)

def exist(filename):  
    """does the file exist?"""
    return os.path.exists(filename)
    
def read(filename):  
    "read the file as list of strings"
    source = open(filename,'r')
    s=source.read()
    source.close()
    return s.split('\n')

def  write(filename, s, check=True,verbose=False):  
    """write a string or a list of string to a file 
    
    if check is true and file exist NOTHING is done
    else the file is overwriten
    """
    if isinstance(s,str ):
        s = s.split('\n')
    if (len(s)==0 or s[-1] != '') :
        s.append('');
    ex = exist(filename)
    if check and ex :
        if verbose : 
            print(
                '\nfile \n%s \nexists and is not overwriten\n' % filename
                )
        return False
    else:
        if verbose :
            if exist(filename):
                print(
                    '\nfile \n%s \nexists and is overwriten\n' % filename
                    )
            else:
                print(
                    'file \n%s \nis created\n' % filename
                    )
        source = open(filename,'w')
        if type(s) is list : s ='\n'.join(s)
        source.write(s)
        source.close()
        return True

def mkdir(d):
    if not os.path.exists(d):
        try:
            os.mkdir(d)
        except (OSError, IOError):
           print(
                ('\n Error: unable to create user config directory\n'+
                    d+'\n Check path and permissions.\n Exiting!\n\n')
                )
           raise SystemExit


if __name__ == "__main__":
    pass
