[ ## this file was manually modified by jt
    {
     'functor' : {
        'description' : ['return the bitwise complement of the entry',
                          "Infix notation can be used with operator '~'"],
          'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ["#include <boost/simd/include/functions/shli.hpp>"],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::shli(boost::simd::Mone<r_t>(),1)','ulp_thresh' : '0',},
                 'boost::simd::Three<T>()' : {'result' : 'boost::simd::shli(boost::simd::Mone<r_t>(),2)','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::shli(boost::simd::Mone<r_t>(),1)','ulp_thresh' : '0',},
                 'boost::simd::Three<T>()' : {'result' : 'boost::simd::shli(boost::simd::Mone<r_t>(),2)','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::complement(a0)'],
                },
             'property_value' : {
                 'integer_' : ['T(~a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
