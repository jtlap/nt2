[ ##script manually modified 
{
    'functor' : {       ## intrinsics values related to functor fast_tand
        'arity'         : '1',    ## functor number of parameters
        'ret_arity'     : '0',## must be '0' or omitted if not a tuple
        'types'         : ['real_', 'unsigned_int_', 'signed_int_'],     ## list of types string
        'rturn'         : { 'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type' },     ## ditionary of return types
        'call_types'    : [],## types used in call ['T']*arity if omitted 
        'type_defs'     : [],  ## supplementary typedefs
        }, ## end of functor
    'unit'    : {       ## informations for creating unit tests
        'global_header' : { ## header of machin.cpp
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
            'included'    : ['#include <nt2/toolbox/trigonometric/include/constants.hpp>',
                             '#include <nt2/toolbox/crlibm/include/tan.hpp>'],     ## list of supplementary include directives
            'notes'       : [],        ## list of strings that will be included in a
                                            ## global comment
            },
        'specific_values' : {
                'real_'       : {
                    'nt2::Inf<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'1.0'},
                    'nt2::Minf<T>()':  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'1.0'},
                    'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'1.0'},
                    'nt2::_180<T>()':  {'result' : 'nt2::Nan<r_t>()','ulp_thresh':'1.0'},
                    'nt2::_90<T>()':   {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'1.0'},
                    'nt2::_45<T>()':   {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'1.0'},
                    '-nt2::_180<T>()': {'result' : 'nt2::Nan<r_t>()','ulp_thresh':'1.0'},
                    '-nt2::_90<T>()':  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'1.0'},
                    '-nt2::_45<T>()':  {'result' : 'nt2::Mone<r_t>()' ,'ulp_thresh':'1.0'},
                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'1.0'},
                },
                'signed_int_   ': {
                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'1.0'},
                    'nt2::_45<T>()':   {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'1.0'},
                    '-nt2::_45<T>()':  {'result' : 'nt2::Mone<r_t>()' ,'ulp_thresh':'1.0'},
                },
                'default': {
                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'1.0'},
                    'nt2::_45<T>()':  {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'1.0'},
                },
           },  ## dictionary of parameters and values to be tested
        'ranges'          :  {
             'default'       : [["T(-45)","T(45)"]],
              },  ## dictionary of ranges for random tests
        'verif_test'      : { ## verification dictionary
            'property_call'   : {'real_' : ['nt2::fast_tand(a0)'],},  ## dictionary of calls per types
            'property_value'  : {'real_' : ['nt2::crlibm::tan<nt2::rn>(a0*nt2::Deginrad<T>())'],}, ## dictionary of alternate calls
            'ulp_thresh'      : {'real_' : ['2.5'],},     ## validity thresholds(s)
        },  ## end of verif_test
    },  ## end of unit 
},
]
