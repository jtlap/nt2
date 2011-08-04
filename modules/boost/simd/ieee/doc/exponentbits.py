[ ## this file was manually modified by jt
    {
     'functor' : {
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
                ['#include <nt2/include/functions/ldexp.hpp>',
                 '#include <nt2/include/functions/exponent.hpp>',
                 '#include <nt2/include/functions/bits.hpp>'],
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
