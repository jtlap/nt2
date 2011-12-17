[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['in the type A0 of a0, the least A0 strictly greater than a0'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/successor.hpp>', '#include <boost/simd/include/constants/eps_related.hpp>'],
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
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Valmin<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()+boost::simd::Eps<r_t>()/2',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()+boost::simd::Eps<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()+boost::simd::Mindenormal<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Inf<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::next(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::successor(a0)'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
