#!/bin/bash
if [ $# -lt 1 ]
then
    echo "Usage: `basename $0` PLOT_TYPE <program>..."
    echo "PLOT_TYPE is either bar or graph"
    echo "If program is -, use content of existing output.txt file"
    echo "RUN_CMD may be defined to an arbitrary prefix command"
    echo "RUN_ARGS may be defined to an arbitrary list of arguments"
    exit 65
fi

# run all programs, filter undesired output
# count number of experiments and sizes
# validate number of sizes
# compute legend

prev_nb_sizes=0
nb_sizes=0
prev_nb_experiments=0
nb_experiments=0
LEGEND=""
plot=$1
shift
#separators
data_type_seperator="With" #how experiments with diferent data types are separated
arch_separator="Arch"
start_data="CTEST_FULL_OUTPUT|---|Benchmark|Site:" #number of lines printed before the experiment results

#positions
arch_pos=2 #position of architecture
type_pos=4 #position of data type
name_pos=1 #position of name

if [ "$1" != "-" ]
then
  rm -f output.txt
  for i in  "$@"
  do
    $RUN_CMD $i $RUN_ARGS | tee -a output.txt
  done
fi

cat output.txt | grep -Ev "${start_data}" > res.txt #remove all the lines containing anything in $start_data
nb_experiments=$(grep -c ${arch_separator} output.txt) #count the number of times $arch_separator appears - this is the number of experiments
((nb_data_types=$(grep -c "${data_type_seperator}" res.txt)/${nb_experiments})) #the data types are printed for every experiment for every type so divide by the number of experiments

# benchmark name is the longest prefix of all experiments without the last _
grep -v ${arch_separator} res.txt > res2.txt #res2.txt contains the benchmark results and the data types
grep -Ev "${data_type_seperator}|${arch_separator}" res.txt > res3.txt #res3.txt only contains the benchmark results
prefix=""
while read l
do
  p=$(echo "$l" | cut -d$'\t' -f1)
  if [ "$prefix" == "" ]
  then
    prefix=$p
  else
    prefix=$(printf "%s\n%s\n" $prefix $p | sed -e 'N;s/^\(.*\).*\n\1.*$/\1/')
  fi
done < res3.txt

BENCH_NAME=$(echo "$prefix" | sed -r 's/_[^_]*//')
#bash array containing T for each experiment
data_types=($(grep ${data_type_seperator} output.txt | awk -v temp=${type_pos} ' { print $temp } ' | tr "[|]" "\000"))

#check that the sizes are correct
sizes=($(grep -n ${data_type_seperator}  res2.txt | cut -f1 -d:)) #assuming we have more than one experiment, count the number of lines between each occurence of $data_type_separator.

#types is the number of data types in the benchmarks. If types is zero, then the benchmark gave no informaion about data types.
types=$(grep -c "${data_type_seperator}" res.txt)
if [ ${types} == "0" ];then
  data_types=""
  ((nb_sizes=$(wc -l < res.txt)/${nb_experiments}))
  nb_data_types=1
else
  ((nb_sizes=${sizes[1]}-${sizes[0]}))
fi
ii=2
while ((ii<${nb_data_types}*${nb_experiments}));do
  ((pos=$ii-1))
  ((my_nb_sizes=${sizes[ii]}-${sizes[pos]}))
  if [ $nb_sizes -ne $my_nb_sizes ]
    then
    echo "inconsistent number of sizes, has $my_nb_sizes, previous had $nb_sizes" >&2
    exit 1
  fi
  ((ii++))
done
((nb_sizes--)) #$nb_sizes counts the line containing $arch_separator
arch_lines=($(grep -n ${arch_separator}  res.txt | cut -f1 -d:)) #find the line numbers on which architecture is printed

#the legend contains the benchmark name and the architecture type
LEGEND="legend(\" $(sed -n 3p res.txt  | awk -v temp=${name_pos} '{ print $temp }' | tr "_" " " | sed "s/$BENCH_NAME//g") $(sed -n 1p res.txt | awk -v temp=${arch_pos} '{ print $temp }')\" "

for ((ii=1;ii<${nb_experiments};ii++));do
  ((pos=${arch_lines[ii]}+2))
  LEGEND="${LEGEND} , \"$(sed  -n ${pos}p res.txt | awk -v temp=${name_pos} ' { print $temp }' | tr "_" " " | sed "s/$BENCH_NAME//g") $(sed -n ${arch_lines[ii]}p res.txt | awk -v temp=${arch_pos} '{ print $temp }')\" "
done
LEGEND="${LEGEND} ) "
NUM_TEST=${nb_experiments}

mv res3.txt res.txt

for ((ii=0;ii<${nb_experiments};ii++));do
    ((pos=${ii}*${nb_sizes}+1))
    BENCH_NAME[ii]=$(sed -n ${pos}p res.txt | awk '{ print $1 }' | tr "_" "\n"| sed -n 1p)
    PLOT_NAME[ii]="${BENCH_NAME[${ii}]}_${data_types[ii]}"
    TITLE[ii]="title(\"${BENCH_NAME[${ii}]} ${data_types[ii]}\")"
done

# generate M-file
if [ $plot == "bar" ]; then
  for ((kk=0;kk<${nb_data_types};kk++));do
    "$(dirname "${BASH_SOURCE[0]}")/generate_bar_chart.sh" $nb_data_types $NUM_TEST $nb_sizes "${LEGEND[@]}" "${TITLE[kk]}" "${PLOT_NAME[kk]}" $kk
  done
elif [ $plot == "graph" ]; then
  for ((kk=0;kk<${nb_data_types};kk++));do
    "$(dirname "${BASH_SOURCE[0]}")/generate_graph.sh" $nb_data_types $NUM_TEST $nb_sizes "${LEGEND[@]}" "${TITLE[kk]}" "${PLOT_NAME[kk]}" $kk
  done
fi
