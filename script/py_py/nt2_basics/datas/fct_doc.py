[ ## list of dictionnaries for different arities of the same functor
{
    'functor' : {      ## intrinsics values related to functor
        'arity'       : 1,   ## functor number of parameters
        },
    'unit' : { ## informations for creating unit tests
        'all_parts'     : { ## common values for all the unit parts
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            },
        'global_header' : { ## header of machin.cpp
            'filename' : None, ## if header is defined in a file give a name
            'included' : [],   ## list of extra include directives
            'notes'    : [],   ## list of strings that will be included in a
                               ## global comment
            },
        },
    'scalar' : {      ## values for scalar tests
        ## reproduce common for values to be specialized if needed
        },
    'simd' : {        ## values for simd tests
        ## reproduce common for values to be specialized if needed
        },
}
]
