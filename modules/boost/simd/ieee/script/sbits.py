[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "The function return signed integer value which has the same bits of the input"],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T, signed>::type',
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
                 'boost::simd::Nan<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Mone<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<r_t>()',
                },
            },
         'verif_test' : {
            },
        },
     'version' : '0.1',
    },
]
