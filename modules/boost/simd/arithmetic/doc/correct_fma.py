[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Always compute the correct fused multiply add,",
                           "For floating point entries this means",
                           "the computation of a0*a1+a2 with only one rounding operation.",
                           "On machines not possessing this hard wired capability",
                           "this can be a bit costly",
                           ],
           'module' : 'boost',
         'arity' : '3',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T,T>::type',
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
             'notes' : [''],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : 
                [['boost::simd::Valmin<T>()',
                 'boost::simd::Valmax<T>()'],
                 ['boost::simd::Valmin<T>()',
                 'boost::simd::Valmax<T>()'],
                 ['boost::simd::Valmin<T>()',
                 'boost::simd::Valmax<T>()']],
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<T>()',
                 'boost::simd::One<T>()+boost::simd::Eps<T>(), boost::simd::One<T>()-boost::simd::Eps<T>(),boost::simd::Mone<T>()' : '-boost::simd::Eps<T>()*boost::simd::Eps<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Two<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
              },
        },
     'version' : '0.1',
    },
]
