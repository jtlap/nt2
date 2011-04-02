[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_real<T>::type',
            },
         'simd_types' : ['uint32_t', 'uint64_t', 'int32_t', 'int64_t'],
         'type_defs' : [],
         'types' : ['uint32_t', 'uint64_t', 'int32_t', 'int64_t'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <nt2/include/functions/bitinteger.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'int32_t' : [['-100', '100']],
             'int64_t' : [['-100', '100']],
             'uint32_t' : [['0', '100']],
             'uint64_t' : [['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::bitinteger(nt2::bitfloating(a0))'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
