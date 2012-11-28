[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns the exponent of the floating input.',
                          '\par',
                          'The sign \\\\f$ \\\\pm \\\\f$ , exponent e and mantissa m of a floating point entry a are related by',
                          '\\\\f$a = \\\\pm m\\\\times 2^e\\\\f$, with m between zero and one'],
         'return' : ['an integer value'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T, signed>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/ilogb.hpp>', '#include <boost/simd/include/functions/abs.hpp>'],
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
                 'boost::simd::Minf<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::exponent(a0)'],
                },
             'property_value' : {
                 'default' : ['a0 ?boost::simd::ilogb(boost::simd::abs(a0)):0'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
