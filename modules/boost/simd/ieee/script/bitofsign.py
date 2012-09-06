[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns a value of the same type as the input',
                          'with all bits set to zero',
                          'except the bit of sign which is preserved.',
                          'Returns always zero for unsigned types'],   
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
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/is_negative.hpp>'],
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
                 '-boost::simd::Zero<T>()' : '-boost::simd::Zero<r_t>()',
                 'boost::simd::Inf<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Minf<T>()' : '-boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'T(1ull << (sizeof(T)*8-1))',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::is_negative(boost::simd::bitofsign(a0))'],
                },
             'property_value' : {
                 'default' : ['boost::simd::is_negative(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },            },
        },
     'version' : '0.1',
    },
]
