[ ##script modified by create_py_doc.py
{
    'functor' : {       ## intrinsics values related to functor lo
        'arity'         : '1',    ## functor number of parameters
        'ret_arity'     : '0',## must be '0' or omitted if not a tuple
        'types'         : ['real_', 'int64_','int32_','int16_'],     ## list of types string
        'rturn'         : { 'default' : 'typename nt2::meta::as_integer<T,unsigned>::type' },     ## dictionary of return types
        'call_types'    : [],## types used in call ['T']*arity if omitted 
        'type_defs'     : [],  ## supplementary typedefs
        'type_defs_aft' : ['typedef typename nt2::meta::downgrade<r_t>::type dr_t;'],  ## supplementary typedefs     
        }, ## end of functor
    'unit'    : {       ## informations for creating unit tests
        'global_header' : { ## header of machin.cpp
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            'included'    : ['#include<nt2/sdk/meta/downgrade.hpp>'],     ## list of supplementary include directives
            'notes'       : [],        ## list of strings that will be included in a
                                            ## global comment
            },
        'specific_values' : {
                'real_'       : {
                    'nt2::One<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::Nan<T>()' :  {'result' : 'nt2::Mone<dr_t>()',  'ulp_thresh':'0.5'},
                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},
                },
                'default': {
                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.5'},
                    'nt2::One<T>()' :  {'result' : 'nt2::One<r_t>()', 'ulp_thresh':'0.5'},
                },
           },  ## dictionary of parameters and values to be tested
        'ranges'          :  {
             'default'       : [["T(0)","T(10)"]],
              },  ## dictionary of ranges for random tests
        'verif_test'      : { ## verification dictionary
            'simd'            : {},   ## dictionary of translations for simd
            'property_call'   : {},   ##'integer_' : ['nt2::lo(a0)'],},  ## dictionary of calls per types
            'property_value'  : {},   ##'integer_' : ['nt2::lo(a0)'],}, ## dictionary of alternate calls
            'ulp_thresh'      : {},   ##'default' : ['0'],},     ## validity thresholds(s)
        },  ## end of verif_test
    },  ## end of unit 
},
]
