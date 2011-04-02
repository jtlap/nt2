[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'included' : ['#include <nt2/include/functions/exp10.hpp>',
                           '#include <nt2/include/functions/sqr.hpp>',
                           'extern "C" { long double cephes_log10l(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0.1)', 'T(10)']],
             'signed_int_' : [['0', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::Minf<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::Minf<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::Minf<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::log10(a0)'],#,'nt2::log10(nt2::exp10(a0))', 'nt2::log10(nt2::sqr(a0))'],
                },
             'property_value' : {
                 'real_' : ['cephes_log10l(a0)'],#,'a0', '2*log10(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['1'],#,'2.0', '100'],
                },
            },
        },
     'version' : '0.1',
    },
]
