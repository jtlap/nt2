[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns the distance to the nearest (distinct) element of the same type.'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' :
                ['#include <boost/simd/include/functions/min.hpp>',
                 '#include <boost/simd/include/functions/next.hpp>',
                 '#include <boost/simd/include/functions/prev.hpp>'],
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
                 'boost::simd::Inf<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Eps<r_t>()/2',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Eps<r_t>()/2',
                 'boost::simd::Zero<T>()' : 'boost::simd::Mindenormal<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::ulp(a0)'],
                 },
             'property_value' : {
                 'default' : ['boost::simd::One<T>()'],
                 'real_' : ['boost::simd::min(a0-boost::simd::prev(a0),boost::simd::next(a0)-a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
