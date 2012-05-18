[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_integer<T, signed>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <nt2/include/functions/ilogb.hpp>', '#include <nt2/include/functions/abs.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
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
                 'nt2::Minf<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::One<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::exponent(a0)'],
                },
             'property_value' : {
                 'default' : ['a0 ?nt2::ilogb(nt2::abs(a0)):0'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
