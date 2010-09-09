#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for creating nt2 Functor templates
"""

import os

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"


import re
from nt2_env     import nt2_py_dir
from headerfiles import Headers
from toolbox     import Toolbox
import file_utils
from file_utils  import exist, read, write
from identities  import whoami
from mylogging import Mylogging

class Functor(Toolbox) :
    """adding/removing functors to a toolbox"""
    def __init__(self, tool_box_name, mode = 'modify',style='sys') :
        Toolbox.__init__(self, tool_box_name, mode=mode, style=style)
        if not self.get_status() : raise SystemExit
        self.logger = Mylogging("nt2.functors.Functor")
        self.ext='.hpp'
        
    def __lst_functor_item(self,base,local,tree =None) :
#        print "local %s" % local
        if local in self.get_actions() :
            action_name = 'lst_'+self.get_actions()[local][0]
            action_level= self.get_actions()[local][1]
            action_dir  = self.get_actions()[local][2]
            if action_level == 'std' :
                action = getattr(Functor,action_name,None)
                if callable(action) : 
                    d = os.path.join(self.get_pathfnt2(),self.get_tb_name(),action_dir)
                    action(self,d)
            elif action_level == 'hie' :
                action_archi = self.get_actions()[local][3]()
                action = getattr(Functor,action_name,None)
                if callable(action) : 
                    d = os.path.join(self.get_pathfnt2(),self.get_tb_name(),action_dir)
                    action(self,d,tree)

    def __mk_functor_item(self,base,local,tree =None) :
#        print "local %s" % local
        if local in self.get_actions() :
            action_name = 'mk_'+self.get_actions()[local][0]
            action_level= self.get_actions()[local][1]
            action_dir  = self.get_actions()[local][2]
            if action_level == 'std' :
                self.logger.info(
                    "\nin+ whoami()+' action for %s is %s\n" % (local,action_name)
                    )
                action = getattr(Functor,action_name,None)
                if callable(action) : 
                    self.logger.info(
                        "\nin '+whoami()+' action %s IS A Functor ATTRIBUTE\n" % action_name
                        )
                    d = os.path.join(self.get_pathfnt2(),self.get_tb_name(),action_dir)
                    action(self,d)
                else :
                    self.logger.info(
                        "\nin '+whoami()+' action %s is not a toolbox attribute\n" % action_name
                        )
            elif action_level == 'hie' :
                action_archi = self.get_actions()[local][3]()
                action = getattr(Functor,action_name,None)
                if callable(action) : 
                    self.logger.info(
                        "\nin '+whoami()+' action %s IS A Functor ATTRIBUTE\n" % action_name
                        )
                    d = os.path.join(self.get_pathfnt2(),self.get_tb_name(),action_dir)
                    action(self,d,action_name,tree,self.get_actions()[local])
                else :
                    self.logger.info(
                        "\nin '+whoami()+' action %s is not a toolbox attribute\n" % action_name
                        )
            else :
                   self.logger.info( "\naction level is %s\n"%action_level)
        else :
            self.logger.info("\naction is not defined for %s\n" % local)
                   
    def add_functor(self,functor_name,arity=1) :
        "adding a new functor"
        self.name = functor_name
        self.arity= arity
        def strlist(tpl,n=1) :
            s = tpl % (n*(0,))
            tpl =", "+tpl
            for i in range(1,arity) :
                s += tpl % (n*(i,))
            return s
        self.class_list = strlist("class A%d")
        self.const_type_list = strlist("A0",0) 
        self.type_list  = strlist("A%d")
        self.call_list  = strlist("const A%d& a%d",2)
        self.const_type_call_list = strlist("const A0& a%d",1)
        self.tb_namespace = self.get_tb_namespace()
        print "--------------self.tb_namespace %s" % self.tb_namespace
        if self.get_tb_style()=='usr' :
            self.tb_taggedname =  self.get_tb_name()+'::'+self.name
        else :
            self.tb_taggedname = self.name       
        self.traversal(self.get_pathfnt2(),self.get_arbo(),
                       self.__mk_functor_item)
        self.update_includes(functor_name)
        del self.name
        del self.arity
        del self.class_list
        del self.type_list 
        del self.const_type_list
        del self.call_list 
        del self.const_type_call_list
        del self.tb_taggedname
        del self.tb_namespace

        

    def list_functor_files(self,functor_name) :
        "list of files pertaining to a functor"
        self.name = functor_name
        self.lsf = []
        self.traversal(self.get_pathfnt2(),self.get_arbo(),
                       self.__lst_functor_item)
        #         self.lst_includes(functor_name)
        del self.name
        return self.lsf

    def rm_functor_files(self,functor_name,check=True) :
        """removing all functor files and includes
        related to an existing functor"""
        l = self.list_functor_files(functor_name)
        if not l :
           self.logger.warning(
              "\nfunctor %s does not exist\n" % functor_name
               )
           return
        r = 'Y'
        if check :
            print "you are about to delete:"
            show(l)
            r = raw_input("are you sure? (y/N):")
        if r.upper() == 'Y' :
            for ll in l :
                try :
                    file_utils.rm(ll)
                except OSError :
                    print "%s does not exist" % ll 

    def update_includes(self, func_name) :
        """update a toolbox include file
        adding an include line for the functor"""
        path = self.get_tb()
        line2add = "#include <"+self.get_tb_pathfnt2()+'/include/'+func_name+'.hpp>'
        file2modify = self.get_tb()+'/'+self.get_tb_name()+'.hpp'
        self.logger.info(
            "\nmodifying \n%s\nfor inclusion of %s\n" % (file2modify,func_name)
            )
        text = read(file2modify)
        # match for the candidate line
        pattern = re.compile(line2add)
        def find_index(p) :
            for i,l in enumerate(text) :
                if p.match(l) : return i+1
            return 0
        if find_index(pattern) :
            self.logger.warning(
                "\nFile %s was already included\n" % func_name +
                "in file\n%s\n" %  file2modify
                )
            return
        else :
            #### match for tag  //<include> 
            pattern = re.compile('//<include>')
            i = find_index(pattern)
            if i != 0 :
                text.insert(i,line2add)
                write(file2modify,text,False)

    def mk(self,path,func_name,flag=None,check=True,comment='//') :
        "wrapping for making different files"
#        print "func_name %s"%func_name
        self.logger.info(
            "\ncreating functor %s %s template for %s\n" % \
            (self.name, func_name[3:],self.get_tb_name()) +
            "in %s\n " % path
            )
        tplfilename = os.path.join(nt2_py_dir(),func_name+'.tpl')
        inner_text = self.__treat(read(tplfilename))
        h = Headers(path,self.name, ext = self.ext,inner=inner_text,comment=comment)
        h.write_header(path=self.get_path2nt2(),flag=flag,check=check)
        
    def lst(self,path,func_name) :
        #        print "func_name %s"%func_name
        extensions = ['.hpp','.rst']
        path2file = os.path.join(self.get_path2nt2(),path)+func_name
        for ext in extensions :
            if exist(path2file+ext) : self.lsf.append(path2file+ext)
       
    def __treat(self,s) :
        """__treat substitutes all $self.<id>$ chains in the
           string s with the value of the variable self.<id> if it
           exist else leaves it as is"""
        if type(s) is str :
            for k,v in self.__dict__.items() :
                s = re.sub('\$self.'+k+'\$',str(v),s)
            return s        
        elif type(s) is list :
            self.tb_name = self.get_tb_name()
            l= [] 
            for ss in s :
                l.append(self.__treat(ss))
            del self.tb_name
            return l
        
   
    def mk_doc(self,path)     :
        """ creation de <fctr>.rst dans nt2/<tb>/doc/source"""
        self.ext = ".rst"
        self.mk(path,whoami(),'inner',check=False)
        self.ext = '.hpp'
    def mk_include(self,path) :
        """ creation de <fctr>.hpp dans nt2/<tb>/include"""
        self.mk(path,whoami(),check=False)
    def mk_define(self,path)  :
        """ creation de <fctr>.hpp dans nt2/<tb>/function"""
        self.tb_nameupper =self.get_tb_name().upper()
        self.mk(path,whoami(),check=False)
    def mk_scalar(self,path)  :
        """ creation de <fctr>.hpp dans nt2/<tb>/function/scalar"""
        self.mk(path,whoami(),check=False)
    def mk_common(self,path)  :
        """ creation de <fctr>.hpp dans nt2/<tb>/function/simd/common"""
        self.mk(path,whoami(),check=False)
    def mk_hierarchy(self, path, func_name, tree, action) :
        """ creation des <fctr>.hpp dans les diverses specialisations simd"""
        #        print "func_name %s"%func_name
        self.logger.info(
            "\ncreating functor %s %s template for %s\n" % \
            (self.name, func_name[3:],self.get_tb_name()) +
            "in %s\n " % path
            )
        tplfilename = os.path.join(nt2_py_dir(),func_name+'.tpl')
        inner_tpl = read(tplfilename)
        for l in tree.values() :
            for k in l :
                self.previous = action[3]().previous(k)
                inner_text = self.__treat(read(tplfilename))
                h = Headers(os.path.join(path,k)+'/',self.name,
                            inner=inner_text)
                h.write_header(path=self.get_path2nt2(),check=False)

    def lst_doc(self,path)     : self.lst(path,self.name)
    def lst_include(self,path) : self.lst(path,self.name)
    def lst_define(self,path)  : self.lst(path,self.name)
    def lst_scalar(self,path)  : self.lst(path,self.name)
    def lst_common(self,path)  : self.lst(path,self.name)
    def lst_hierarchy(self, path,tree) :
        #        print "func_name %s"%func_name
        for l in tree.values() :
            for k in l :
                path2file = os.path.join(self.get_path2nt2(),path,k)+'/'+self.name+'.hpp'
                if exist(path2file) : self.lsf.append(path2file)

    
if __name__ == "__main__":
    from list_utils import show
    ftr = Functor("arithmetic",mode='update',style='sys')
    ftr.add_functor("zorglub",arity=3)
##    show(ftr.list_functor_files("abs"))
 #   ftr.rm_functor_files("zorglub")
