[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::arithmetic(T,T)>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include<nt2/include/functions/floor.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(4),T(0)' : 'nt2::Inf<r_t>()',
                 'T(4),T(3)' : '1',
                 'nt2::Inf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::One<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                },
             'signed_int_' : {
                 'T(4),T(0)' : '0',
                 '4,3' : '1',
                 'nt2::Mone<T>()' : 'nt2::One<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                },
             'unsigned_int_' : {
                 '4,3' : '1',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::divfloor(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['r_t(a1 ? nt2::floor((1.0*a0)/a1) : 0)'],
                 'real_' : ['r_t(nt2::floor(a0/a1))'],
                 },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
