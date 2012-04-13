[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns 2 times the Machine epsilon',
                          '\par',
                          'The Machine epsilon gives an upper bound on the relative',
                          'error due to rounding in floating point arithmetic. Typically \f$2^{-53}\f$',
                          'for floating point doubles and \f$2^{-24}\f$ for',
                          'floats. MATLAB(TM) language defines the value eps ',
                          'as the distance from 1.0 to the next larger double',
                          'which is two times the machine epsilon...',
                          'Returns one for integer types.'
                          ],
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
             'included' : [],
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
                 'boost::simd::Mone<T>()' : 'boost::simd::Eps<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Eps<r_t>()',
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
            },
        },
     'version' : '0.1',
    },
]
