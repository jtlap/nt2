[ ## this file was manually modified by jt
    {
     'functor' : {
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
             'default' : [['3*(nt2::Valmin<T>()/4)', '3*(nt2::Valmax<T>()/4)'], ['3*(nt2::Valmin<T>()/4)', '3*(nt2::Valmax<T>()/4)']],
             'real_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Zero<T>()',
                 'nt2::One<T>(),nt2::Mone<T>()' : 'nt2::Two<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Valmin<T>(),nt2::One<T>()' :  'nt2::Valmin<T>()',
                 'nt2::Valmin<T>(),nt2::Mone<T>()' :  'nt2::Valmin<T>()+nt2::One<T>()',
                 'nt2::Mone<T>(), nt2::Valmax<T>()' :  'nt2::Valmin<T>()',
                 'nt2::Mone<T>(), nt2::Valmin<T>()' :  'nt2::Valmax<T>()',   
                 'nt2::Zero<T>(), nt2::Valmin<T>()' :  'nt2::Valmax<T>()',
                 'T(-2), nt2::Valmin<T>()' :  'nt2::Valmax<T>()-nt2::One<T>()',   
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Valmin<T>(),nt2::One<T>()' :  'nt2::Valmin<T>()',
                 'nt2::One<T>(),nt2::Valmax<T>()' :  'nt2::Valmin<T>()',
                  },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::subs(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::subs(a0,a1)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
