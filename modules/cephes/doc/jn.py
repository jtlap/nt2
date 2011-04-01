[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['iT','T'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['cephes'],
         'type_defs' : [],
         'types' : ['double'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 01/03/2011',
             'included' : ['#include <nt2/include/functions/jni.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 01/03/2011',
            },
         'ranges' : {
             'default' : [['iT(0)', 'iT(10)'],['T(0)', 'T(10)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::cephes::jn(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::jni(a0,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['10000'],
                },
            },
        },
    },
]
