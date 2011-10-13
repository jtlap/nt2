[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The result is the mathetical subtraction of the arguments',
                          'saturated in the interval defined by the common arguments type bounds',
                          ],
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
             'real_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::One<T>(),boost::simd::Mone<T>()' : 'boost::simd::Two<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmin<T>(),boost::simd::One<T>()' :  'boost::simd::Valmin<T>()',
                 'boost::simd::Valmin<T>(),boost::simd::Mone<T>()' :  'boost::simd::Valmin<T>()+boost::simd::One<T>()',
                 'boost::simd::Mone<T>(), boost::simd::Valmax<T>()' :  'boost::simd::Valmin<T>()',
                 'boost::simd::Mone<T>(), boost::simd::Valmin<T>()' :  'boost::simd::Valmax<T>()',   
                 'boost::simd::Zero<T>(), boost::simd::Valmin<T>()' :  'boost::simd::Valmax<T>()',
                 'T(-2), boost::simd::Valmin<T>()' :  'boost::simd::Valmax<T>()-boost::simd::One<T>()',   
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmin<T>(),boost::simd::One<T>()' :  'boost::simd::Valmin<T>()',
                 'boost::simd::One<T>(),boost::simd::Valmax<T>()' :  'boost::simd::Valmin<T>()',
                  },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::subs(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::subs(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
