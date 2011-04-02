class Tree(object):
    
    def __init__(self, value, children = []):
        self.parent = None
        self.value = value
        self.children = children
        for child in self.children:
            child.parent = self
      
    def walk(self, f, arg):
        f(arg, self.value, self.parent)
        for child in self.children:
            child.walk(f, arg)
            
    def linearize(self):
        l = [self.value]
        for child in self.children:
            l.extend(child.linearize())
        return l

tree = Tree(
  ['common'],
  [
    Tree(
      ['sse', 'common'],
      [
        Tree(
          ['sse', 'sse2'],
          [
            Tree(
              ['sse', 'sse3'],
              [
                Tree(
                  ['sse', 'ssse3'],
                  [
                    Tree(
                      ['sse', 'sse4a'],
                      [
                        Tree(
                          ['sse', 'xop'],
                          [
                            Tree(
                              ['sse', 'fma4']
                            )
                          ]
                        )
                      ]
                    ),
                    Tree(
                      ['sse', 'sse4_1'],
                      [
                        Tree(
                          ['sse', 'sse4_2'],
                          [
                            Tree(
                              ['sse', 'avx']
                            )
                          ]
                        )
                      ]
                    )
                  ]
                )
              ]
            )
          ]
        )
      ]
    ),
    Tree(
      ['vmx', 'common'],
      [
        Tree(
          ['vmx', 'altivec']
        ),
        Tree(
          ['vmx', 'spu']
        )
      ]
    )
  ]
)

def path_split(str):
    l = str.replace('\\', '/').replace('//', '/').split('/')
    if(l[0] == ''):
        l[0] = '/'
    elif(len(l[0]) == 2 and l[0][1] == ':'):
        l[0] = l[0]+'\\'
    return l

import os
class SimdFile(object):
    
    def __init__(self, context, dir):
        
        self.path_prefix = path_split(context['PATH_PREFIX'])
        self.basefile = [context['FUNCTION_FILE']]
        
        self.file = self.path_prefix + ['simd'] + dir + self.basefile
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
            
        if(source_exists or binary_exists):
            return None
    
        for i in range(1, len(self.file_path_binary)):
            path = os.path.join(*self.file_path_binary[:i])
            if not os.path.exists(path):
                os.mkdir(path)

        f = open(binary_path, 'w')
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
        
    def create_forward(self, parents):
        f = self.create()
        if(f == None):
            return
            
        self.write_header(f)
        if(len(parents) == 0):
            f.write("#error function has no SIMD implementation\n")
        else:
            for parent in parents:
                parent_file = self.path_prefix + ['simd'] + parent + self.basefile
                f.write("#include <" + str.join('/', parent_file) + ">\n")
        self.write_footer(f)

def create_forward_file(context, value, parent):
    f = SimdFile(context, value)
    parents = []
    if(parent != None):
      parents.append(parent.value)
    f.create_forward(parents)

def main_(source, binary, prefix, function):
    context = {
        'SOURCE_INCLUDE_PATH': source,
        'BINARY_INCLUDE_PATH': binary,
        'PATH_PREFIX': prefix,
        'FUNCTION_FILE': function
    }
    tree.walk(create_forward_file, context)

    f = SimdFile(context, ['all'])
    f.create_forward(tree.linearize())

import sys
def main():
    if(len(sys.argv) >= 5):
        main_(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
    elif(len(sys.argv) == 4):
        path = sys.argv[1] + '/' + sys.argv[3]
        if(os.path.exists(path)):
          for file in os.listdir(path):
            if(len(file) > 4 and file[-4:] == '.hpp'):
              main_(sys.argv[1], sys.argv[2], sys.argv[3], file)
    else:
        sys.stderr.write("Not enough parameters\n")

if __name__ == "__main__":
    main()
