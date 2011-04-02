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
         'special' : ['cephes'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 01/03/2011',
             'included' : ['#include <nt2/include/functions/i0.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 01/03/2011',
            },
         'ranges' : {
             'default' : [['T(-50)', 'T(50)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::cephes::i0(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::i0(a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['2.0'],
                },
            },
        },
    },
]
