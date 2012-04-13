[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["return a value of the same type of the entry",
                          "which is the greatest integer less or equal to the entry"],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'cover_included' : ['#include <boost/simd/toolbox/standard/include/functions/floor.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
             'default' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'T(-1.1)' : 'r_t(-2)',
                 'T(1.1)' : 'r_t(1)',
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
                 'default' : ['boost::simd::floor(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::standard::floor(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
