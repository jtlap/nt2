[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns the exponent bits of the floating input as an integer value.',
                          'the other bits (sign and mantissa) are just masked.',
                          '\par',
                          'The sign \\\\f$ \\\\pm \\\\f$, exponent e and mantissa m of a floating point entry a are related by',
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
             'included' : 
                ['#include <boost/simd/include/functions/ldexp.hpp>',
                 '#include <boost/simd/include/functions/exponent.hpp>',
                 '#include <boost/simd/include/functions/bits.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10000)', 'T(10000)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                  'default' : ['boost::simd::exponentbits(a0)'],
               },
             'property_value' : {
                 'default' : ['boost::simd::bits(boost::simd::ldexp(boost::simd::One<T>(),boost::simd::exponent(a0)))'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
