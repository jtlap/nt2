[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::arithmetic(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_']   
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'included' : ['#include <nt2/include/functions/log10.hpp>',
                           'extern "C" { long double cephes_exp10l(long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['0', '10']],
             'unsigned_int_' : [['0', '10']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::One<r_t>()/10',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::Ten<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::One<r_t>()/10',
                 'nt2::One<T>()' : 'nt2::Ten<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::Ten<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : [],
                 'real_' : ['nt2::exp10(a0)'],#,'nt2::log10(nt2::exp10(a0))'],
                },
             'property_value' : {
                 'default' : [],
                 'real_' : ['::cephes_exp10l(a0)'],#, 'r_t(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5','5'],
                },
            },
        },
     'version' : '0.1',
    },
]
