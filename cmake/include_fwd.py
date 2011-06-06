display = False

def path_split(str):
    l = str.replace('\\', '/').replace('//', '/').split('/')
    if(l[0] == ''):
        l[0] = '/'
    elif(len(l[0]) == 2 and l[0][1] == ':'):
        l[0] = l[0]+'\\'
    return l

import os
import sys
class IncludeFile(object):
    
    def __init__(self, context):
        
        self.path_prefix = path_split(context['PATH_PREFIX'])
        self.basefile = [context['FUNCTION_FILE']]
        
        self.file = self.path_prefix + self.basefile
        self.file_path_source = path_split(context['SOURCE_INCLUDE_PATH']) + self.file
        self.file_path_binary = path_split(context['BINARY_INCLUDE_PATH']) + self.file
        
    def create(self):
        source_path = os.path.join(*self.file_path_source)
        source_exists = os.path.exists(source_path)
        binary_path = os.path.join(*self.file_path_binary)
        binary_exists = os.path.exists(binary_path)

        if(source_exists and binary_exists):
            os.remove(binary_path)
            return None
            
        if(source_exists):
            return None
    
        for i in range(1, len(self.file_path_binary)):
            path = os.path.join(*self.file_path_binary[:i])
            if not os.path.exists(path):
                os.mkdir(path)

        f = open(binary_path, 'w')
        if(display):
            sys.stdout.write('/'.join(self.file) + "\n")
        return f
        
    def write_header(self, f):
        f.write("/*******************************************************************************\n")
        f.write(" *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II       \n")
        f.write(" *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI       \n")
        f.write(" *                                                                              \n")
        f.write(" *          Distributed under the Boost Software License, Version 1.0.          \n")
        f.write(" *                 See accompanying file LICENSE.txt or copy at                 \n")
        f.write(" *                     http://www.boost.org/LICENSE_1_0.txt                     \n")
        f.write(" ******************************************************************************/\n")
        headername = str.join('_', self.file).upper().replace('.', '_') + "_INCLUDED"
        f.write("#ifndef " + headername + "\n")
        f.write("#define " + headername + "\n")
        
    def write_footer(self, f):
        f.write("#endif\n")
        f.close()
        
    def create_forward(self, parent):
        f = self.create()
        if(f == None):
            return
            
        self.write_header(f)
        parent_file = path_split(parent) + self.basefile
        f.write("#include <" + str.join('/', parent_file) + ">\n")
        self.write_footer(f)

def main_(source, binary, from_prefix, output, function):
    context = {
        'SOURCE_INCLUDE_PATH': source,
        'BINARY_INCLUDE_PATH': binary,
        'PATH_PREFIX': from_prefix,
        'FUNCTION_FILE': function
    }

    for out in output:
        prev = context['PATH_PREFIX']
        context['PATH_PREFIX'] = out
        f = IncludeFile(context)
        f.create_forward(prev)

import optparse
def main():
    parser = optparse.OptionParser()
    parser.add_option('-d', '--display',
                      default=False,
                      action="store_true",
                     )
    parser.add_option('-o', '--output',
                      default=[],
                      action="append",
                     ) 
    options, args = parser.parse_args()
    options = options.__dict__
    
    global display
    display = options['display']
    
    if(len(args) >= 4):
        main_(args[0], args[1], args[2], options['output'], args[3])
    elif(len(args) == 3):
        path = args[0] + '/' + args[2]
        if(os.path.exists(path)):
            for file in os.listdir(path):
                if(len(file) > 4 and file[-4:] == '.hpp'):
                    main_(args[0], args[1], args[2], options['output'], file)
        for i in range(len(options['output'])):
            path = args[0] + '/' + options['output'][i]
            if(os.path.exists(path)):
                for file in os.listdir(path):
                    if(len(file) > 4 and file[-4:] == '.hpp'):
                        main_(args[0], args[1], options['output'][i], options['output'][i+1:], file)
    else:
        sys.stderr.write("Not enough parameters\n")

if __name__ == "__main__":
    main()
