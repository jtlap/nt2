[ ##script modified by create_py_doc.py
{
    'functor' : {       ## intrinsics values related to functor shli
        'arity'         : '2',    ## functor number of parameters
        'ret_arity'     : '0',## must be '0' or omitted if not a tuple
        'types'         : ['integer_'],     ## list of types string
        'simd_types'    : ['integer_'],     ## list of types string
        'rturn'         : { 'default' : 'T' },     ## dictionary of return types
        'call_types'    : ['T','iT'],## types used in call ['T']*arity if omitted 
        'type_defs'     : [],  ## supplementary typedefs
        }, ## end of functor
    'unit'    : {       ## informations for creating unit tests
        'global_header' : { ## header of machin.cpp
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            'included'    : ['#include <nt2/include/functions/twopower.hpp>'],     ## list of supplementary include directives
            'notes'       : [],        ## list of strings that will be included in a
                                            ## global comment
            },
        'specific_values' : {
                'integer_': {
                    'nt2::Zero<T>(),1': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.5'},
                    'nt2::One<T>(),1': {'result' : 'nt2::Two<r_t>()','ulp_thresh':'0.5'},
                    'nt2::Two<T>(),2': {'result' : 'nt2::Eight<r_t>()','ulp_thresh':'0.5'},
                    'nt2::Mone<T>(),1': {'result' : '-2','ulp_thresh':'0.5'},
                    'nt2::Mone<T>(),2': {'result' : '-4','ulp_thresh':'0.5'},
                 },
           },  ## dictionary of parameters and values to be tested
        'ranges'          :  {
             'default'       : [["T(-10000)","T(10000)"],["T(0)","sizeof(T)*8-1"]],
              },  ## dictionary of ranges for random tests
        'verif_test'      : { ## verification dictionary
            'simd'            : {},   ## dictionary of translations for simd
            'property_call'   : {'integer_' : ['nt2::shli(a0,a1)'],},  ## dictionary of calls per types
            'property_value'  : {'integer_' : ['a0*nt2::twopower(a1)'],}, ## dictionary of alternate calls
            'ulp_thresh'      : {'default' : ['0'],},     ## validity thresholds(s)
        },  ## end of verif_test
    },  ## end of unit 
},
]
