[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '2',
         'rturn' : {
             'default' : 'boost::fusion::vector<T,nt2::int32_t>',
            },
         'simd_types' : [],
         'special' : ['standard'],
         'type_defs' : [],
         'types' : ['float','double'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 06/03/2011',
             'included' :
                ['#include <boost/fusion/tuple.hpp>',
                 '#include <nt2/include/functions/mantissa.hpp>',
                 '#include <nt2/include/functions/exponent.hpp>'],

             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 06/03/2011',
            },
         'ranges' : {
             'default' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::standard::frexp(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::mantissa(a0)/2', 'nt2::exponent(a0)+1'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
