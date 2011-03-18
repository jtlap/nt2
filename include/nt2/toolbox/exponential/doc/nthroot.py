[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created by jt the 08/12/2010',
             'included' : ['#include <nt2/include/functions/sqr.hpp>', '#include <nt2/include/functions/abs.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 15/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>(),3' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>(),3' : 'nt2::Minf<r_t>()',
                 'nt2::Mone<T>(),3' : 'nt2::Mone<r_t>()',
                 'nt2::Nan<T>(),3' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::nthroot(a0*nt2::sqr(a0),3)', 'nt2::nthroot(nt2::sqr(a0),2)'],
                },
             'property_value' : {
                 'real_' : ['T(a0)', 'nt2::abs(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['1', '1'],
                },
            },
        },
     'version' : '0.1',
    },
]
