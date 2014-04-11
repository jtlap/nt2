nb_data_types=$1
NUM_TEST=$2
nb_sizes=$3
TITLE=$4
PLOT_NAME=$5
kk=$6
LEG=$7
i=0
filename="create_plot${kk}.tex"
count=0

for ((jj=0;jj<${NUM_TEST};jj++));do
  for ((ll=1;ll<=${nb_sizes};ll++));do
    ((pos=${jj}*${nb_sizes}*${nb_data_types}+${ll}+${kk}*${nb_sizes}))
    SIZE[count]=$(sed -n ${pos}p res.txt | tr "(" "\n" | tr ")" "\n" | sed -n 2p)
    CYC[count]=$(sed -n ${pos}p res.txt  | tr ")" "\n" |  sed -n 2p | awk '{ print $1 }')
    UNIT=$(sed -n ${pos}p res.txt  | tr ")" "\n" |  sed -n 2p | awk '{ print $2 }')
    ((count++))
  done
done

for ((jj=1;jj<=${NUM_TEST};jj++));do
  le[jj]=$(echo ${LEG} | tr "_" "." |tr "Z" "\n" | sed -n -e ${jj}p| sed  's/^ *//')
done

#determine max Y
IFS=$'\n'
max_y=$(echo "${CYC[*]}" | sort -nr | head -n1)
max_y=${max_y%.*}
((max_y=max_y*14/10))

echo "\documentclass{standalone}" > ${filename}
echo "\ifstandalone" >> ${filename}
echo "\usepackage{listings}" >> ${filename}
echo "\ifxetex" >> ${filename}
echo "  \usepackage{fontspec}" >> ${filename}
echo "  \defaultfontfeatures{Mapping=tex-text}" >> ${filename}
echo "  \newcommand{\codefont}{\ttfamily}" >> ${filename}
echo "\else" >> ${filename}
echo "  \usepackage[utf8x]{inputenc}" >> ${filename}
echo "  \newcommand{\codefont}{\fontfamily{fi4}\selectfont}" >> ${filename}
echo "\fi" >> ${filename}
echo "\usepackage[english]{babel}" >> ${filename}
echo "\usepackage{pgfplotstable}" >> ${filename}
echo "\fi" >> ${filename}
echo "\begin{document}" >> ${filename}
echo "\ifstandalone" >> ${filename}
echo "\begin{tikzpicture}[scale=1.0]" >> ${filename}
echo "\fi" >> ${filename}
echo "\pgfplotsset{grid style={dotted,gray}}" >> ${filename}
echo "\begin{axis}" >> ${filename}
echo "[area legend,legend pos=south east," >> ${filename}
echo "legend style={at={(0.2,0.99)},anchor=north,legend cell align=left,draw=none}," >> ${filename}
echo "xlabel=\textbf{Size}," >> ${filename}
echo "ylabel=\textbf{${UNIT}}," >> ${filename}
echo "ymin=1," >> ${filename}
#echo "ymax=13," >> ${filename}
echo "xmin=1," >> ${filename}
echo "xmax=6," >> ${filename}

echo "xticklabels={ 0,">> ${filename}
for ((ii=0;ii<${nb_sizes};ii++));do
  echo  "\tiny\scalebox{0.9}{{${SIZE[$ii]}}},">> ${filename} #check this!! is size the correct one now???
done

echo "}" >> ${filename}
echo "]" >> ${filename}

colors[0]="red"
colors[1]="yellow"
colors[2]="blue"
colors[3]="green"
colors[4]="pink"
colors[5]="cyan"
colors[6]="orange"
colors[7]="gray"

symbols[0]="square*"
symbols[1]="triangle*"
symbols[2]="x*"
symbols[3]="o"
symbols[4]="pentagon*"
symbols[5]="cube*"
symbols[6]="diamond*"
symbols[7]="halfsquare*"

for ((ii=0;ii<${NUM_TEST};ii++));do
  ((color_pos=$ii%7))
  echo "\addlegendimage{${colors[$color_pos]},fill}" >> ${filename}
  ((le_pos=$ii+1))
  echo "\addlegendentry{{\scalebox{0.7}{${le[$le_pos]}}}}"  >> ${filename}
done

for ((ii=0;ii<${NUM_TEST};ii++));do
  ((color_pos=$ii%7))
  echo "\addplot[${colors[$color_pos]}]" >> ${filename}
  echo "plot[smooth,dashed,mark=${symbols[$color_pos]},mark size=1pt]">>${filename}
  echo "table [] {">>${filename}
  echo "x       y">>${filename}
  for ((jj=0;jj<${nb_sizes};jj++));do
    ((pos=$ii*${nb_sizes}+$jj))
    ((index=$jj+1))
    echo "$index ${CYC[pos]}" >> ${filename}
  done
  echo "};">> ${filename}
done

echo "\end{axis}" >> ${filename}
echo "\ifstandalone" >> ${filename}
echo "\end{tikzpicture}" >> ${filename}
echo "\fi" >> ${filename}
echo "\end{document}" >> ${filename}

which xelatex > /dev/null
if [ $? -eq 1 ];then
  xelatex ${filename} > /dev/null
else
  pdflatex ${filename} > /dev/null
fi

gnome-open $(echo $filename | sed  's/tex/pdf/g'  )
