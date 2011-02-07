[ ##script modified by create_py_doc.py
{
    'functor' : {       ## intrinsics values related to functor is_ngez
        'arity'         : '1',    ## functor number of parameters
        'ret_arity'     : '0',## must be '0' or omitted if not a tuple
        'types'         : ['real_', 'signed_int_','unsigned_int_'],     ## list of types string
        'simd_types'    : ['real_','signed_int_','unsigned_int_'],     ## list of simd types string
        'rturn'         : { 'default' : 'typename nt2::meta::logical<T>::type' },     ## dictionary of return types
        'call_types'    : [],## types used in call ['T']*arity if omitted 
        'type_defs'     : [],  ## supplementary typedefs
        'special'       : ['predicate',],        ## special property
        }, ## end of functor
    'unit'    : {       ## informations for creating unit tests
        'global_header' : { ## header of machin.cpp
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            'included'    : ['#include <nt2/sdk/meta/logical.hpp>'],     ## list of supplementary include directives
            'notes'       : [],        ## list of strings that will be included in a
                                            ## global comment
            },
        'specific_values' : {
                'real_'       : {
                    'nt2::Inf<T>()' :  {'result' : 'nt2::False<r_t>()',  'ulp_thresh':'0.5'},
                    'nt2::Minf<T>()':  {'result' : 'nt2::True<r_t>()',  'ulp_thresh':'0.5'},
                    'nt2::One<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::Mone<T>()' :  {'result' : 'nt2::True<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::Two<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::Nan<T>()' :  {'result' : 'nt2::True<r_t>()',  'ulp_thresh':'0.5'},
                    'nt2::Half<T>()':   {'result' : 'nt2::False<r_t>()',  'ulp_thresh':'0.5'},
                    'nt2::Quarter<T>()':  {'result' : 'nt2::False<r_t>()','ulp_thresh':'0.5'},
                    'nt2::Zero<T>()':  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                    '-nt2::Zero<T>()':  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                },
                'signed_int_': {
                    'nt2::Zero<T>()':  {'result' : 'nt2::False<r_t>()','ulp_thresh':'0.5'},
                    'nt2::Two<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::Mone<T>()' :  {'result' : 'nt2::True<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::One<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                },
                'default': {
                    'nt2::Zero<T>()':  {'result' : 'nt2::False<r_t>()','ulp_thresh':'0.5'},
                    'nt2::Two<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                    'nt2::One<T>()' :  {'result' : 'nt2::False<r_t>()', 'ulp_thresh':'0.5'},
                },
           },  ## dictionary of parameters and values to be tested
        'ranges'          :  {
             'default'       : [["T(-10000)","T(10000)"]],
              },  ## dictionary of ranges for random tests
        'verif_test'      : { ## verification dictionary
            'simd'            : {},   ## dictionary of translations for simd
            'property_call'   : {'default' : ['nt2::is_ngez(a0)'],},  ## dictionary of calls per types
            'property_value'  : {'default' : ['a0<0'],}, ## dictionary of alternate calls
            'ulp_thresh'      : {'default' : ['0'],},     ## validity thresholds(s)
        },  ## end of verif_test
    },  ## end of unit 
},
]
