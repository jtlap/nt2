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
             'included' : ['#include <nt2/include/functions/asin.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 01/03/2011',
            },
         'ranges' : {
             'default' : [['T(-1)', 'T(1)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::cephes::asin(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::asin(a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1.0'],
                },
            },
        },
    },
]
