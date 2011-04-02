[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include<nt2/toolbox/standard/include/floor.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(-1.1)' : 'r_t(-2)',
                 'T(1.1)' : 'r_t(1)',
                 'nt2::Inf<T>()' : 'nt2::Inf<T>()',
                 'nt2::Minf<T>()' : 'nt2::Minf<T>()',
                 'nt2::Mone<T>()' : 'nt2::Mone<T>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Mone<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::floor(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::standard::floor(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]