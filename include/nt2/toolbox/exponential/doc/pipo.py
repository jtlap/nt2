[ ## list of dictionnaries for different arities of the same functor
{
    'functor' : {      ## intrinsics values related to functor
        'arity'  : 2,   ## functor number of parameters
        #'ret_arity'     : "2",  ## must be '0' or omitted if not a tuple 
        'types'  : ['real_'],##, 'unsigned_int_', 'signed_int_'],
        'rturn'  : { 'default': 'typename boost::result_of<nt2::meta::floating(T)>::type'},
        'call_types' : ["T","iT"],
        'type_defs' : ["typedef int iT;"]
        },
    'unit' : { ## informations for creating unit tests
        'all_parts'     : { ## common values for all the unit parts
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            },
        'global_header' : { ## header of machin.cpp
            'filename' : None, ## if header is defined in a file give a name
            'included' : ["#include <nt2/include/functions/log.hpp>",
                          "#include <nt2/include/functions/sqr.hpp>,"],   ## list of extra include directives
            'notes'    : [],   ## list of strings that will be included in a
                               ## global comment
            },
        'specific_values' : {
             'real_': { 'nt2::Inf<T>()': ['nt2::Inf<r_t>()','2.5'],
                        'nt2::Minf<T>(),4': 'nt2::Zero<r_t>()',
                        'nt2::Mone<T>()': 'nt2::One<r_t>()/nt2::Exp_1<r_t>()',
                        'nt2::Nan<T>()': 'nt2::Nan<r_t>()',
                        'nt2::One<T>()': 'nt2::Exp_1<r_t>()',
                        'nt2::Zero<T>()': 'nt2::One<r_t>()'},
             'signed_int_': { 'nt2::Mone<T>()': 'nt2::Half<r_t>()',
                              'nt2::One<T>()': 'nt2::One<r_t>()/nt2::Exp_1<r_t>()',
                              'nt2::Zero<T>()': 'nt2::One<r_t>()'},
             'unsigned_int_': { 'nt2::One<T>()': 'nt2::Exp_1<r_t>()',
                                'nt2::Zero<T>()': 'nt2::One<r_t>()'},
             'default' : {},   
            },
         'ranges' : {
             'default'       : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_'         : [['T(-100)','T(100)'],[2,4]],
             'signed_int_'   : [['T(-100)','T(100)'],[2,4]],
             'unsigned_int_' : [['T(0)','T(100)']],
                
             },  
##         'random_tuple_test' : {
##                "alternate_call" :{
##                    "default" : "T(a0)*2"
##                    },
##                "ulp_thresh" : "1.5",
##                },
##         'random_tuple_test' : {
##                "alternate_call" :{
##                    "default" : ["T(a0)*2","T(a0)/2"]
##                    },
##                "ulp_thresh" : ["1.5","1"],
##                },
         'verif_test' : {
##                "property_call" :{
##                    "default" : ["sqr(r0)+sqr(r1)","T(aa0)/2"]
##                    },
                "property_value" :{
                    "default" :  ["a0"],
 #                   "default" : ["a0","25"]
                    },
                "ulp_thresh" :  ["1.5"], 
#                "ulp_thresh" : ["1.5","1"],
                },
            
        },

},
{
    'functor' : {      ## intrinsics values related to functor
        'arity'       : 2,   ## functor number of parameters 
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

}
]
