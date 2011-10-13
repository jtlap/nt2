[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' : ["return a value of the same type of the entry",
                             "which is the smallest integer greater or equal to the entry"],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'cover_included' : ['#include <boost/simd/toolbox/standard/include/functions/ceil.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [['T(-100)', 'T(100)']],
             'unsigned_int_' : [['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(-1.1)' : 'r_t(-1)',
                 'T(1.1)' : 'r_t(2)',
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Minf<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::ceil(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::standard::ceil(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
