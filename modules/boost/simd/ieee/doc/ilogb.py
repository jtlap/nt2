[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :["This function returns the integer truncation",
                         "of the base 2 logarithm of a0.",
                         "It coincides with the exponent function",
                         "on all platforms supported."],   
         'return' : ['always an integer value'],   
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T, signed>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/exponent.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)']],
             'signed_int_' : [['0', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Minf<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Two<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Two<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Two<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::ilogb(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::exponent(double(a0))'],
                 'real_' : ['boost::simd::exponent(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
