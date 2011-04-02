[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
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
             'included' : ['#include <nt2/include/functions/sqr.hpp>',
                           '#include <nt2/include/functions/sqrt.hpp>',
                           'extern "C" { long double cephes_powl(long double,long double); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)'], ['T(0)', 'T(10)']],
             'signed_int_' : [['0', '10'], ['0', '10']],
             'unsigned_int_' : [['0', '10'], ['0', '10']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::Mone<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Mone<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()' : 'nt2::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : [],
                 'real_' : ['nt2::pow(a0,a1)', 'nt2::pow(a0,nt2::Two<T>())', 'nt2::pow(a0,nt2::Half<T>())'],
                },
             'property_value' : {
                 'default' : [],
                 'real_' : ['::cephes_powl(a0,a1)', 'nt2::sqr(a0)', 'nt2::sqrt(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['11','1', '1'],
                },
            },
        },
     'version' : '0.1',
    },
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 08/12/2010',
             'included' : ['extern "C" { long double cephes_powil(long double,int); }'],
             'notes' : [],
             'stamp' : 'modified by jt the 14/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
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
             'signed_int_' : {
                 'nt2::Mone<T>(),3' : 'nt2::Mone<r_t>()',
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>(),3' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>(),3' : 'nt2::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : [],
                 'real_' : ['nt2::powi(a0,a1)', 'nt2::powi(a0,nt2::Two<iT>())', 'nt2::powi(a0,nt2::Three<iT>())'],
                },
             'property_value' : {
                 'default' : [],
                 'real_' : ['cephes_powil(a0,a1)', 'nt2::sqr(a0)', 'a0*nt2::sqr(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['2','2', '2'],
                },
            },
        },
     'version' : '0.1',
    },
]
