[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include <nt2/toolbox/arithmetic/include/functions/hypot.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10000)', 'T(10000)'], ['T(-10000)', 'T(10000)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
             'default' : [['0', '100'], ['0', '100']],
             },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Mone<T>()' : ['nt2::Sqrt_2<r_t>()', '0.5'],
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()', '0.5'],
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Three<T>(),nt2::Four<T>()' : 'nt2::Five <r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : ['nt2::Sqrt_2<r_t>()', '0.5'],
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()', '0.5'],
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Three<T>(),nt2::Four<T>()' : 'nt2::Five <r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : ['nt2::Sqrt_2<r_t>()', '0.5'],
                 'nt2::Zero<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Three<T>(),nt2::Four <T>()' : 'nt2::Five <r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::fast_hypot(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['r_t(nt2::hypot(a0,a1))'],
                },
             'ulp_thresh' : {
                 'default' : ['2.0'],
                },
            },
        },
     'version' : '0.1',
    },
]
