#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""remove integer benches
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import sys
import os
import glob
import re
from files_utils import read, write, exist
from pprint import pprint

import argparse

class Fix_includes_in_file() :
    def __init__(self, fname,mode,name,d) :
        self.debug=  True
        self.name = name
        self.mode = mode
        self.base = d['base']
        self.root = d['binarybase']
        self.module = d['module']
        self.fname = fname
        self.fnamedirect = d['fnamedirect']
        self.modeloc = "simd/common" if self.mode =="simd" else self.mode
        if not exist(fname) :
            pprint('Warning')
            pprint('File: '+ fname)
            pprint('does not exist')
        self.textorig = read(fname)
        if d['save'] :
            pprint("saving to: "+fname+'_')
            write(fname+'_',self.textorig,False)
        if d['show_source'] :
            pprint('Original file for '+self.name)
            pprint('=orig===============================================')
            pprint(self.textorig)
            pprint('===============================================orig=')
        self.ids = {}
        self.includes = []
        self.uncommented = self.suppress_comments_and_includes()
        self.anomaly= False
        self.anomaly_msg=''
        self.modestr = "simd/" if (self.mode == "generic/" and d['add'] != "complex/")  else self.mode
        self.modestr = "" if (d['add'] == "complex/")  else self.modestr
        self.unspecif = self.unspecified_present()
        self.write = d["write"];

    def unspecified_present(self) :
        return ' '.join(self.textorig).find('unspecified_') != -1

    def suppress_comments_and_includes(self) :
        res = []
        for line in self.textorig:
            if ( line.find('#else') != -1):
                 self.anomaly= True
                 self.anomaly_msg='#else detected'
            if ( line.find('#include') != -1 ) or  line.find('NT2_FUNCTOR') != -1:
                continue
            i = line.find('//')
            if (i != -1) and (i != 0):
                res.append(line[0:i])
            elif (i !=0) :
               res.append(line)
        return res[2:-2]

    def treat_text(self) :
        self.anomaly= False
        self.anomaly_msg=''
        all_ranges = []
        d = self.find_special_ranges()
##        print d
        for k in d :
            self.ids[k] = self.get_ids(d[k])
##            pprint('&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&')
##            pprint(k)
##            pprint( d[k])
##            pprint( self.ids[k])
##            pprint(self.uncommented)
##            pprint(d[k][0][0])
##            pprint(d[k][0][1])
##            for dd in d[k] :
##                pprint(dd)
##                pprint(self.uncommented[dd[0]:dd[1]])
##            pprint('&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&')
            all_ranges.extend(d[k])
##        pprint('||||||||||||||||||||||||||||||||||||||||||')
##        pprint(sorted(all_ranges))
##        pprint(self.content(all_ranges))
##        pprint('||||||||||||||||||||||||||||||||||||||||||')
        regular_range= self.complement_range(sorted(all_ranges))
##        pprint("regular")
##        pprint(regular_range)
##        pprint(self.content(regular_range))
        self.ids["regular"]=self.get_ids(regular_range)
##        pprint(self.ids["regular"])
        includes = self.get_includes(self.ids["regular"],True);
        if d :
            for k in d :
                 notk =        self.get_ids_not(d[k])
                 self.ids[k] =  self.ids[k]-self.ids["regular"]
                 includes.append('')
                 includes.append('#ifndef '+k)
                 includes.extend(self.get_includes(self.ids[k]))
                 includes.append('#endif')
        newtext = self.transform_file(includes)
        newtext = self.clean(newtext)
        newtext = self.sup_doubleblank(newtext)
        return newtext,self.anomaly,self.anomaly_msg


    def content(self,ranges) :
        z=[]
        for r in ranges :
            z.extend(self.uncommented[r[0]:r[1]])
            z.append('--------')
        return z

    def sup_doubleblank(self,newtext) :
        i=0
        n = len(newtext)-1
        res = []
        blank = False
        while i<=n :
            if not blank :
                if len(newtext[i])==0 :
                    blank = True
                    res.append(newtext[i])
                    i=i+1
                else :
                   res.append(newtext[i])
                   i = i+1
            else :
                if len(newtext[i])==0 :
                    i = i+1
                else :
                    blank = False
                    res.append(newtext[i])
                    i = i+1
        return res

    def clean(self,newtext) :
        res = [newtext[0]]
        n = len(newtext)-1
        i = 1
        while i<n :
            if (newtext[i].find('#ifndef') != -1) and (newtext[i+1].find('#endif') != -1) :
                i = i+2
            else :
                res.append(newtext[i])
                i = i+1
        res.append(newtext[n])
        if self.fnamedirect :
            for i,l in enumerate(res) :
                if l.find('#include')!=-1 :
                    if l.find(self.module)==-1:
                        del res[i]
                        break
        return res

    def zone(self,ranges) :
        if not ranges :
            return self.uncommented
        else :
            z = []
            for r in ranges :
##                pprint('r')
##                pprint(r)
                z.extend(self.uncommented[r[0]:r[1]])
##            pprint('11111111111111111111111111')
##            pprint(z)
##            pprint('22222222222222222222222222')

            return z

    def complement_range(self,ranges) :
        ranges = sorted(ranges)
#        pprint(ranges)
        if len(ranges)==0 :
            nr = [[0,len(self.uncommented)]]
        elif len(ranges)==1 :
            nr = [[0,ranges[0][0]],[ranges[0][1],len(self.uncommented)]]
        else :
            nr = [[0,ranges[0][0]]]
            pred = ranges[0]
            for r in ranges[1:] :
                nr.append([pred[1],r[0]])
                pred =r
            nr.append([pred[1], len(self.uncommented)])
        return nr

    def get_ids_not(self,ranges) :
        return self.get_ids(self.complement_range(ranges))

    def get_ids(self,ranges=[]) :
        d = {'*':'multiplies','/':'divides','+':'plus','-':'minus'}
        ll =" ".join(self.zone(ranges))
        s =list(set(re.findall(re.compile('[A-Za-z][a-z0-9_]+ *[(<]'), ll)))
        s1 = []
        for e in s:
            if ' ' in e :
                e=re.sub(' ', '',e)
            if e[0] == e[0].lower() and e[-2] !='_' :
                s1.append(e[:-1])

        s =list(set(re.findall(re.compile('[A-Z][a-z0-9_]+[<]'), ll)))
        for e in s:
            if e[-2] !='_' :
                s1.append(e[:-1])
        if self.mode == 'simd/' :
            s =list(set(re.findall(re.compile('[\*/+-]'), ll)))
            for e in s :
                s1.append(d[e])
##                if '-' in s :
##                    s1.append('unary_minus')
            s =list(set(re.findall(re.compile('[\*/+-]='), ll)))
            for e in s :
                s1.append(d[e[0]])
            s =list(set(re.findall(re.compile('[,=+\*/><\([] *-'), ll)))
            if s :
                s1.append('unary_minus')

        excluded = set(['template','return','exit','for','while','do','if','compute','operator','expa','static_cast'])
        return set(s1)-excluded

    def translate(self,idd) :
        d = {}#"expa":"expo","log":"logs","log2":"logs","log10":"logs"}
        if idd in d.keys() :
            return d[idd]
        else :
            return idd

    def add_specifics(self,l):
        t =' '.join(self.textorig)
        if t.find('BOOST_ASSERT_MSG') != -1 :
            l.append('#include <boost/assert.hpp>')
        if t.find('BOOST_SIMD_NO') != -1 :
            l.append('#include <boost/simd/sdk/config.hpp>')
        if t.find('BOOST_FORCEINLINE') != -1 :
            l.append('#include <boost/dispatch/attributes.hpp>')
        return l


    def get_includes(self,idds,specifics=False) :
        Aliases = {'lt':'is_less',
                   'gt':'is_greater',
                   'le':'is_less_equal',
                   'ge':'is_greater_equal',
                   'b_xor':'bitwise_xor',
                   'b_or' :'bitwise_or',
                   'if_nan_else':'if_allbits_else',
                   'assert_all':'assert_utils',
                   'single_constant':'Real_splat',
                   'double_constant':'Real_splat',
                   'l_or':'logical_or',
                   'l_and':'logical_and',
                   'eq':'is_equal',
                   "shri":'shr',
                   "shl" :'shift_left'
                   }

        root = self.root
        sdk =['as_logical', 'cardinal_of','scalar_of','as_floating']
        kernels =['tanh_kernel', 'sinh_kernel', 'sinhc_kernel']
        s= []
#        pprint(idds)
#        pprint(self.textorig)
        ids =[]
        for idd in idds :
            idd = self.translate(idd)
            if idd in Aliases.keys() :
                idd = Aliases[idd]
            ids.append(idd)
        ids=set(ids)
#        pprint(ids)
        for idd in ids :
            if (idd == 'powf') :
               s.append('#include <cmath>')
            elif (idd == 'horner') :
                s.append('#include <nt2/polynomials/functions/scalar/impl/horner.hpp>')
            elif (idd[0] == idd[0].upper()) :
                f =self.base+'include/constants/'+idd.lower()+'.hpp'
                if exist(root+f) :
                    s.append('#include <'+ f +'>')
                else :
                    pprint(root+f+" does not exist")
            elif idd in sdk :
                f = self.base+'sdk/meta/'+idd+'.hpp'
                s.append('#include <'+f+'>')
            elif idd in kernels :
                s.append('#include <nt2/'+self.module+'functions/details/'+idd+'.hpp>')
            else :
                if self.unspecif :
                    f =self.base+'include/functions/'+idd+'.hpp'
                else :
                    f =self.base+'include/functions/'+self.modestr+idd+'.hpp'
##                pprint("========================================================")
##                pprint(root)
##                pprint(f)
##                pprint(exist(root+f))
##                pprint("********************************************************")
                if exist(root+f) :
                    s.append('#include <'+f+'>')
                else :
                    incs = self.get_include_in_orig(idd)
                    if incs :
##                        pprint("found in orig file ")
##                        pprint(incs)
                        s.extend(incs) #TODO verif something on that
                    else :
                        pprint("nothing found in orig file for "+idd)
##                    pprint("========================================================")
                if specifics : s = self.add_specifics(s)
        return sorted(set(s))

    def get_include_in_orig(self,idd) :
        incs =[]
#        pprint(self.textorig)
        for l in self.textorig :
            if (l.find("#include") != -1) :
                if (l.find('/'+idd+'.hpp') != -1) :
                    incs.append(l)
        return incs



    def find_special_ranges(self) :
        r= []
        val = [ '',0,0,False]
        for i,l in enumerate(self.uncommented) :
            if l.find('#ifndef')!=-1 :
                l1 = re.sub(' ','',l)
                l1 = re.sub('#ifndef','',l1)
                val = [ l1, i, 0, True]
            elif l.find('#include') != -1 and val[3] :
                val[3]=False
            elif  (l.find('#else')!=-1) :
                val[2]=i+1
                if i!=val[1]+1 :
                    val[3]=False
                    r.append(val)
            elif (l.find('#endif')!=-1)  :
                if val[2]== 0 :
                    val[2]=i+1
                    if i!=val[1]+1 :
                        val[3]=False
                        r.append(val)
                val =  [ '',0,0,False];
        d ={}
        if r :
            for v in r :
                if v[0] in d.keys() :
                    d[v[0]].append(v[1:])
                else:
                    d[v[0]] =[v[1:]]
        return d

    def transform_file(self,includes) :
        newtext = []
        firstinclude=0
        empty =False
        for l in self.textorig :
            if  l == '' :
                empty = True
                continue
            elif empty :
                newtext.append('')
                empty = False
            if l.find('#include') != -1 :
                if  firstinclude==0 :
                    newtext.append(l);
                    newtext.extend(includes)
                    firstinclude =1
            else:
                newtext.append(l);
        return newtext

class Fix_includes_in_files() :
    def __init__(self,mode,d) :
        self.d = d
        self.show = d['show']
        self.write=d['write']
        self.mode = mode
        if self.d['fnamedirect'] :
            self.file_list = [d['fname']]
            mode = "simd"+"/"
        else:
            self.modeloc = "simd/common" if self.mode =="simd"  else self.mode
            self.direc = self.__setdir()

            choice = self.direc+self.d['names']+'.hpp'
            print "choice is ", choice
            self.file_list = sorted(glob.glob(choice))

    def __setdir(self) :
        modeloc = "simd/common"+"/" if  self.mode =="simd"+"/" else  self.mode
        return self.d['dirbase']+self.d['module']+"include/"+self.d['base']+self.d['module']+"functions/"+self.d['add']+modeloc


    def treat_files(self) :
        if not self.file_list :
            pprint("no file match the choice")
        for fname in self.file_list :
            name = os.path.basename(fname)[:-4]
            fiif = Fix_includes_in_file(fname,self.mode,name,self.d)
            newtext,anomaly,anomaly_msg =fiif.treat_text()
            if self.show :
                pprint('Transformed file for '+name)
                pprint('=trans===============================================')
                pprint(newtext)
                pprint('===============================================trans=')
            elif self.write:
                if anomaly :
                  print(anomaly_msg)
                  print(name + " was not modified")
                  pprint(fiif.textorig)
                else :
                    pprint(fname)
                    write(fname,newtext,False,True)

def addslash(s):
    if s is list :
        return [addslash(l) for l in s]
    if not s :
       return s
    if s[-1]=='/' :
        return s
    return s+'/'

def main(argv):
    d = {'module':"exponential"+"/",
         'mode' :"all"+"/",
         'names' :"dgammainc",
         'base' : 'nt2'+'/',
         'show_only' : True,
         'save' : False,
         'fname' : "",
         'fnamedirect':False,
         'supermod':'core/',   #'type'+"/"
         'add': "",
         'save':False,
         'dirbase':'',
         'binarybase':''
         }
    try:
        nsr =os.environ['NT2_SOURCE_ROOT']
    except :
        pprint('variable NT2_SOURCE_ROOT is not present your enironment please set it to use the script')
        sys.exit(1);
    try:
        nbr =os.environ['NT2_BINARY_ROOT']
    except :
        pprint('variable NT2_BINARY_ROOT is not present your enironment please set it to use the script')
        sys.exit(1);

    d['dirbase'] = nsr+"/modules/"+d['supermod']+d['add']
    d['binarybase'] = nbr+"/include/"

    parser = argparse.ArgumentParser(description='find corect includes for an nt2 functor implementation.')
    parser.add_argument('-s','--save', dest='s', action='store_true',
                   help='make a copy of each treated file with an appended _ to its name')
    parser.add_argument('-w','--write', dest='w', action='store_true',
                   help='perform all the planned operation rewriting the original files')
    parser.add_argument('--show', dest='show', action='store_true',
                   help='show the transformed files')
    parser.add_argument('--show_source', dest='show_source', action='store_true',
                   help='show the source files')
    parser.add_argument('-f','--fname', dest='fname', action='store',
                        default="",
                        help='give the full path to the name of the file to be treated (overides other naming options)')
    parser.add_argument('-n','--names', dest='names', action='store',
                        default="*",
                        help='names of the functors to be treated (can contain jokers *?')
    parser.add_argument('-m','--mode', dest='mode', action='store',
                        default="all",
                        help='simd or scalar or generic or all')
    parser.add_argument('-u','--module', dest='module', action='store',
                        default="exponential",
                        help='module in which functor files are found')
    parser.add_argument('--super', dest='supermod', action='store',
                        default="core",
                        help='super module in which functor files are found')

    print argv
    args = parser.parse_args(argv)
    print args
    d['mode'] = addslash(args.mode)
    d['module'] = addslash(args.module)
    d['names'] = args.names
    d['show'] = args.show
    d['show_source'] = args.show_source
    d['save'] = args.s
    d['fname'] = args.fname
    if d['fname'] :
        d['fnamedirect']=True
    d['write'] = args.w
    d['save'] = args.s
    d['show_only'] = (not args.w) and args.show
    if d['supermod'] == 'type'+"/" :
        d['add']="complex"+"/"

    pprint ('mode        is    "'+ d['mode']       +'"')
    pprint ('module      is    "'+ d['module']     +'"')
    pprint ('names       is    "'+ d['names']      +'"')
    pprint ('dirbase     is    "'+ d['dirbase']    +'"')
    pprint ('supermod    is    "'+ d['supermod']   +'"')
    pprint ('fname       is    "'+ d['fname']      +'"')
    pprint ('fnamedirect is    "'+ str(d['fnamedirect'])+'"')
    pprint ('show        is    "'+ str(d['show'])  +'"')
    pprint ('write       is    "'+ str(d['write'])      +'"')
    pprint ('save        is    "'+ str(d['save'])       +'"')
    pprint ('show_only   is    "'+ str(d['show_only'])  +'"')
    pprint ('show_source is    "'+ str(d['show_source'])  +'"')
    if d['show_only'] : print("This is a show only run")
    if d['mode'][:3] != "all" :
        modes = [d['mode']]
    else :
        modes = ['scalar/','simd/','generic/']
    for m in modes :
        pprint(m)
        fiifs = Fix_includes_in_files(m,d)
        fiifs.treat_files()
    if d['show_only'] : print("it was a show only run")


if __name__ == "__main__" :
    main(sys.argv[1:])
