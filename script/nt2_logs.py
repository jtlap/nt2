#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for creating nt2 toolboxes templates
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"


import logging
import logging.config

class Nt2_logs :
    def __init__(self, ch_level=logging.DEBUG,fh_level=logging.INFO) :
        # create logger with "nt2"
        self.logger = logging.getLogger("nt2")
        self.logger.setLevel(logging.DEBUG)
#        self.logger.setLevel(0)
        
        #create file handler and set level to debug
        self.fh = logging.FileHandler("nt2.log")
        self.fh.setLevel(fh_level)
#        self.fh.setLevel(0)
        
        # create console handler and set level to debug
        self.ch = logging.StreamHandler()
        self.ch.setLevel(ch_level)
#        self.ch.setLevel(0)
        
        # create formatter
        self.formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
        
        # add formatter to ch and fh
        self.fh.setFormatter(self.formatter)
        self.ch.setFormatter(self.formatter)
        
        # add ch to logger
        self.logger.addHandler(self.fh)
        self.logger.addHandler(self.ch)

    def log(self,level,warn) : return self.logger.log(level,warn)
    def logger(self) : return self.logger
    def set_ch_level(level) :  self.ch.setLevel(level)
    def set_fh_level(level) :  self.fh.setLevel(level)

if __name__ == "__main__":
    logs = Nt2_logs(ch_level=logging.DEBUG,fh_level=logging.INFO);

