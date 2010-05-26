Latest News
===========

Joel vers JT
^^^^^^^^^^^^
* generer la doc pour plus et comapgnie dans core/numeric/function
* couper les tableaux de perfs en plusieurs tableaux (cf abs)

JT vers Joel
^^^^^^^^^^^^

* cycle_timer
             #include <iostream>				       
	     #include <nt2/include/config.hpp>		       
	     #include <nt2/include/timing.hpp>		       
	     						       
	     using namespace std;				       
	     						       
	     int main( int argc, char** argv)		       
	     {						       
	     int wait;					       
	     double d;					       
	     						       
	     cout << "How many seconds do you want to wait ? ";   
	     cin >> wait;					       
	     {						       
	     nt2::time::cycle_timer s(d);		       
	     sleep(wait);				       
	     }						       
	     }                                                      

      c'est l'exemple de cycle_timer.
      Ne pourrait-on pas demander a attendre un nombre de cycles ?
      Ca montrerait en plus comment acceder a la vitesse d'horloge
      (d'ailleurs on fait ca ?)



*   Macros simd
 
      Dans les macros simd de detection, il faudrait decouper NT2_SIMD_SSE4 en 3
      pour 4_1, 4_2 et 4_a

*   dans la description de has_same_size as_integer, etc., tu ne decrit pas le 3eme parametre optionnel 

*   comment s'utilise make_integer pour calculer des trucs comme int16 -> int32

*   Je voudrais faire des conversions entre vecteur dont la taille 
    d'éléments est != 
    Comment faire pour que result_type soit
         
     bf:(native<float>,native<float>,native<float>,native<float>)
    
     ou 

     bf:(native<float>,native<float>)
     suivant que l'entrée soit native<int8> ou native<int16>

     ca serait interessant par exemple d'avoir une convesion 
     image<char> -> image<float> performante. J'ai fait un essai
     ad hoc et je gagne 30% par rapport au scalaire en transformant
     1 vecteur d'int16 en 2 vecteurs de float

*    en regardant AVX je me rend compte qu'il faudra absolument meler
     au moins en interne des vecteurs 128 et 256 bits et donc prevoir 
     des outils pour ça

Autres
^^^^^^
