[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
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
             'default' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::nextafter(a0,a1)'],
                },
             'property_value' : {
                 'double' : ['::nextafter(a0,a1)'],
                 'float' : ['::nextafterf(a0,a1)'],
                 'signed_int_' : ['(a1 == a0) ? a0 : (a1 > a0) ? a0+boost::simd::One<T>() : a0-boost::simd::One<T>()'],
                 'unsigned_int_' : ['(a1 == a0) ? a0 : (a1 > a0) ? a0+boost::simd::One<T>() : a0-boost::simd::One<T>()'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
