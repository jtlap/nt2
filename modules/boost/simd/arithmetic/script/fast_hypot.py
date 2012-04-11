[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["computes \f$(a_0^2 + a_1^2)^{1/2}\f$ in a quicker,",
                        "but sometimes less accurate way than \c hypot"
                        ],
         'module' : 'boost',
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
             'included' : ['#include <boost/simd/toolbox/arithmetic/include/functions/hypot.hpp>'],
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
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Mone<T>()' : ['boost::simd::Sqrt_2<r_t>()', '0.5'],
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : ['boost::simd::Sqrt_2<r_t>()', '0.5'],
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : ['boost::simd::Sqrt_2<r_t>()', '0.5'],
                 'boost::simd::One<T>()' : ['boost::simd::Sqrt_2<r_t>()', '0.5'],
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : ['boost::simd::Sqrt_2<r_t>()', '0.5'],
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::fast_hypot(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['r_t(boost::simd::hypot(a0,a1))'],
                },
             'ulp_thresh' : {
                 'default' : ['2.0'],
                },
            },
        },
     'version' : '0.1',
    },
]
