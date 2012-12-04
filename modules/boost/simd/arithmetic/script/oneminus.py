[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["returns the saturated \f$1-a_0\f$"],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : [],
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
                 'boost::simd::Inf<T>()' : '-boost::simd::Inf<r_t>()',
                 'boost::simd::Minf<T>()' : '-boost::simd::Minf<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::oneminus(a0)'],
                },
             'property_value' : {
                 'default' : ['1-a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
