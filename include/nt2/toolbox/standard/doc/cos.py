[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['standard'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 06/03/2011',
             'included' : ['#include <nt2/include/functions/cos.hpp>'],
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
                 'default' : ['nt2::standard::cos(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::cos(a0)'],
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
