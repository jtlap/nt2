[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns the first entry logically shifted left',
                          'by the absolute value of second entry.'],
         'param_1' : ['must be a scalar integer value'],
         'return'  : ['returns a value of the type of the first parameter'],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['integer_'],
         'type_defs' : [],
         'types' : ['integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <boost/simd/include/functions/twopower.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['T(0)', 'sizeof(T)*8-1']],
            },
         'specific_values' : {
             'integer_' : {
                 'boost::simd::Mone<T>(),1' : {'result' : 'r_t(-2)','ulp_thresh' : '0.5',},
                 'boost::simd::Mone<T>(),2' : {'result' : 'r_t(-4)','ulp_thresh' : '0.5',},
                 'boost::simd::One<T>(),1' : {'result' : 'boost::simd::Two<r_t>()','ulp_thresh' : '0.5',},
                 'T(2),2' : {'result' : 'boost::simd::Eight<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>(),1' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::shli(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0*boost::simd::twopower(a1))'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]
