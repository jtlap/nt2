[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "this is \f$\|a_0-a_1\|\f$, and is always properly computed",
                         ],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
             'double' : [['-10.0', '10.0'], ['-10.0', '10.0']],
             'float' : [['-10.0f', '10.0f'], ['-10.0f', '10.0f']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::dist(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0>a1 ? a0-a1 : a1-a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
