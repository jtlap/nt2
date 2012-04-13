[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' : ["return a value of integer type of the same size and signedness than the entry.",
                             "The value returned is the nearest integer to the entry"],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include <boost/simd/include/functions/round.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'default' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(1.4)' : '1',
                 'T(1.5)' : '2',
                 'T(1.6)' : '2',
                 'T(2.5)' : '2',
                 'boost::simd::Half<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Mhalf<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Minf<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::iround2even(a0)'],
                },
             'property_value' : {
                 'default' : ['r_t(boost::simd::round(a0))'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
