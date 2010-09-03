#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Some environment related nt2 tools

   function:
   
   nt2_dir return the absolute path to the directory under which
   stands the main nt2 directory
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"


import os
import sys
import re
import logging

nt2_env_logger = logging.getLogger("nt2.nt2_env")



def nt2_dir() :
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
        if not d : d = os.getcwd()
        try :
            d1 = re.match("(^.*/)nt2/",d).groups()
        except :
            nt2_env_logger.error(
                     "\n Environment chain 'NT2_DIR' is not defined\n"+
                     "and your current path does not contain /nt2/\n"+
                     "sorry aborting\n"+
                     nt2_dir.__doc__
                     )
            raise SystemExit
        if len(d1)!=0 : d = d1[0]
        nt2_env_logger.warning(
                     "\n Environment chain 'NT2_DIR' is not defined\n "+
                     ("defaulting to %s\n"%d)+
                     nt2_dir.__doc__
                     )
    return os.path.expanduser(os.path.join(d,"nt2/include/"))

def nt2_py_dir() :
    return os.path.dirname(os.path.realpath(__file__))

        
if __name__ == "__main__":
    import nt2_logs
    NT2_LOGS = nt2_logs.Nt2_logs()
    print "nt2_dir %s" % nt2_dir()
    print "------------"
    print "sys.path[0] %s" % sys.path[0]
    print "------------"
    print "os.getcwd() %s" % os.getcwd()
    print "------------"

