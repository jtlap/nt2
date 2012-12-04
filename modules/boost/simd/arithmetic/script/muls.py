[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' : ["return the saturated multiplication of a0 by a1"],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['signed_int_', 'unsigned_int_'],
         'type_defs' : [],
         'types' : ['signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'included' : [],
             'notes' : [],
             'no_ulp' :'True',
             'stamp' : 'modified by jt the 24/3/2010',
            },
         'ranges' : {
             'default' : [['3*(boost::simd::Valmin<T>()/4)', '3*(boost::simd::Valmax<T>()/4)'], ['3*(boost::simd::Valmin<T>()/4)', '3*(boost::simd::Valmax<T>()/4)']],
            },
         'specific_values' : {
             'default' : {
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>(),boost::simd::One<T>()' :  'boost::simd::Valmax<T>()',
                 'boost::simd::Valmax<T>(),boost::simd::Mone<T>()' :  'boost::simd::Valmin<T>()+boost::simd::One<T>()',
                 'boost::simd::Valmax<T>()' :  'boost::simd::Valmax<T>()',
                 'boost::simd::Valmax<T>(),T(2)' :  'boost::simd::Valmax<T>()',
                 'boost::simd::Valmin<T>(),boost::simd::Mone<T>()' :  'boost::simd::Valmax<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>(),T(2)' :  'boost::simd::Valmax<T>()',
                  },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::muls(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::muls(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
