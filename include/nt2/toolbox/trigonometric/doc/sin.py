[  ## list of dictionnaries for different arities of the same functor
{
        'functor' : {      ## intrinsics values related to sin
            'arity'      : '1',   ## functor number of parameters
            'ret_arity'  : '0',            ## must be '0' or omitted or None if not a tuple 
            'types'      : ['real_', 'unsigned_int_', 'signed_int_'], ## list of types for which a specific test will be generated
            'rturn'      : { 'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type' },            ## dict of calls return types for each of <types>
            'call_types' : [  ],         ## list of types for one call [] default to 'T'
            'type_defs'  : [  ],          ## list of additional typedef needed (for examples for <call_types>,
        },
        'unit'    : { ## informations for creating unit tests
            'global_header' : { ## properties needed to construct header of sin.cpp
                'first_stamp' : 'created  by jt the 16/12/2010', ## creation stamp
                'stamp'       : 'modified by $author$ the $date$', ## modification stamp don't modify please (!)
                'included'    : ["#include <nt2/include/functions/cos.hpp>",
                                 "#include <nt2/include/functions/sqr.hpp>"], ## list of extra include directives
                'notes'       : [],                                ## list of strings that will be included in a global comment
            },
            'specific_values' : { ## parameters/values pairs to be asserted
                                  ## one parameter (no commas) is replicated else use comma separated string
                                  ## a specific ulp for a value can be introduced in the string result after a comma
                                  ## or in a dictionnary {'result' : '...','ulp_thresh','...'}
                'real_'       : {
                    'nt2::Inf<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                    'nt2::Minf<T>()':  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                    'nt2::Pi<T>()'  :  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.75'},
                    'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                    'nt2::Pi<T>()/2':  {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()' ,'ulp_thresh':'0'},
                },
                'signed_int_   ': {
                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},
                },
                'default': {
                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},
                },
            },
            'verif_test' : { ## assert result of property call equal to property values
                             ## up to ulp_threshold (0 means strict equality) for random
                             ## values uniformly distributed in ranges
                'property_call' : { 'real_' :  ["nt2::sqr(nt2::sin(a0))+nt2::sqr(nt2::cos(a0))",
                                                  "nt2::sin(nt2::Two<T>()*a0)"]},
                'property_value' :{ 'real_' :  ['nt2::One<T>()',"nt2::Two<T>()*nt2::sin(a0)*nt2::cos(a0)"], },
                'ulp_thresh'     :{ 'real_' :  ['0.5','0.5'],},
                'nb_rand'        :'100',
                'ranges' : {
                     'default'       : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
                     'real_'         : [['-nt2::Pi<T>()','nt2::Pi<T>()']],
                     'signed_int_'   : [['T(-40)','T(40)']],
                     'unsigned_int_' : [['T(0)','T(40)']],
                },
            },
        },
   },     
]
