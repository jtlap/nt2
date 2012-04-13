[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['float','double','signed_int_','unsigned_int_'],
         'type_defs' : [],
         'types' : ['float','double','signed_int_','unsigned_int_'],
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
             'float' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'double': [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],  
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::nextafter(a0,a1)'],
                },
             'property_value' : {
                 'double' : ['::nextafter(a0,a1)'],
                 'float' : ['::nextafterf(a0,a1)'],
                 'signed_int_' : ['(a1 == a0) ? a0 : (a1 > a0) ? a0+nt2::One<T>() : a0-nt2::One<T>()'],
                 'unsigned_int_' : ['(a1 == a0) ? a0 : (a1 > a0) ? a0+nt2::One<T>() : a0-nt2::One<T>()'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
