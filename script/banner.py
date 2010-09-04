#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for automatic generation of nt2 banners
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import time

from mylogging  import Mylogging
from re_list   import sub_list

class Banner :
    """create nt2 banner

       you can set a banner_template_begin and a banner_template_end as string lists
       but defaults are provided

       you can also define or add to the default list banner_cprth (copyrights)
    """
    Std_begin = [
        "/******************************************************************************",
        ]
    Std_end = [
        " *                                                                             ",
        " *          Distributed under the Boost Software License, Version 1.0.         ",
        " *                 See accompanying file LICENSE.txt or copy at                ",
        " *                     http://www.boost.org/LICENSE_1_0.txt                    ",
        " *****************************************************************************/",
        ]
    Std_cpght = [
        " *        Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand      ",  
        " *        Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI           ",
        ]
    def __init__(self,
                 year = None,
                 banner_cpght = None,
                 banner_template_begin = None,
                 banner_template_end   = None) :
        self.logger = Mylogging("nt2.banner.Banner")
        self.__banner_begin = Banner.Std_begin if (banner_template_begin is None) else banner_template_begin
        self.__banner_end   = Banner.Std_end   if (banner_template_end   is None) else banner_template_end
        self.__banner_cpght = Banner.Std_cpght if (banner_cpght          is None) else banner_cpght 
        self.__year = year
        self.set_year()

    def add_cpght(self, cpght) :
        if type(cpght) is str :
            self.__banner_cpght.append(cpght)
        elif type(cpght) is list :
            self.__banner_cpght.extend(cpght)
        self.__banner_cpght = sub_list('<year>',self.__year,self.__banner_cpght)
                  
    def __str__(self) :
        return "\n".join(self.__call__())
    
    def set_year(self) :
        if self.__year is None :
            self.__year = time.localtime().tm_year
        if type(self.__year) is not str :
            self.__year = str(self.__year)
        if len(self.__year)==1 :
            self.__year = '0'+self.__year
        if len(self.__year)==2 :
            self.__year = "20"+self.__year
        try :
            self.__year = str(int(self.__year))
        except :
            saved_year =self.__year
            self.logger.warning(
                "\nin setyear\n"+
                ("year has been given the incorrect value: %s" % self.__year)
                )
            self.__year = str(time.localtime().tm_year)
            self.logger.warning(
                "\nin Banner.setyear\n "+
                "year has been given the incorrect value: %s" % saved_year +
                "\nyear is turned to %s " % self.__year
                )
        self.__banner_cpght = sub_list('<year>',self.__year,self.__banner_cpght)

    def get_banner(self) :
        """ return the complete banner """
        return self.__banner_begin + self.__banner_cpght + self.__banner_end
    def __call__(self) :
        """ return the complete banner """
        return self.__banner_begin + self.__banner_cpght + self.__banner_end
    def get_banner_begin(self) :
        """ return the high part of the banner """
        return self.__banner_begin
    def get_banner_end(self) :
        """ return the low part of the banner """
        return self.__banner_end
    def get_banner_cprght(self) :
        """ return the copyright part of the banner """
        return self.__banner_cpght
    def get_year(self) :
        """ return the current end year of the copyright"""
        return self.__year

if __name__ == "__main__":
    Mylogging.set_level('INFO')
    print Mylogging.get_level()
    banner = Banner()
    print banner
    banner = Banner(20)
    print banner
    banner = Banner('2013')
    print banner
    banner = Banner('z')
    print banner
    banner.add_cpght(" *        Copyright 1907-<year> ZORGLUB THE GREAT      ") 
    print banner

