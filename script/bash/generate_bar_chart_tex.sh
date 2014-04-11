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
  le[jj]=$(echo ${LEG} | tr "_" "." |tr "Z" "\n" | sed -n -e ${jj}p | sed  's/^ *//')
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
echo "\definecolor{darkpastelgreen}{rgb}{0.01, 0.75, 0.24}" >> ${filename}
echo "\definecolor{darkred}{rgb}{0.55, 0.0, 0.0}" >> ${filename}
echo "\definecolor{darkpastelred}{rgb}{0.76, 0.23, 0.13}" >> ${filename}
echo "\definecolor{darkgoldenrod}{rgb}{0.72, 0.53, 0.04}" >> ${filename}
echo "\definecolor{darkseagreen}{rgb}{0.56, 0.74, 0.56}" >> ${filename}
echo "\definecolor{denim}{rgb}{0.08, 0.38, 0.74}" >> ${filename}
echo "\definecolor{deepsaffron}{rgb}{1.0, 0.6, 0.2}" >> ${filename}
echo "\definecolor{flame}{rgb}{0.89, 0.35, 0.13}" >> ${filename}
echo "\definecolor{fulvous}{rgb}{0.86, 0.52, 0.0}" >> ${filename}
echo "\definecolor{harvardcrimson}{rgb}{0.98, 0.85, 0.37}" >> ${filename}
echo "\pgfplotsset{grid style={dotted,gray}}" >> ${filename}
echo "\pgfplotsset{every axis/.append style={legend style={font=\tiny,line width=1pt,mark size=1pt},}}" >> ${filename}
echo "\begin{axis}" >> ${filename}
echo "[ybar,enlargelimits=false,width=10.5cm,height=7cm," >> ${filename}
echo " bar width=15pt,area legend,legend pos=south east," >> ${filename}
echo "legend style={at={(0.8,0.99)},anchor=north,legend cell align=left,draw=none}," >> ${filename}
echo "tick align=outside," >> ${filename}
echo "xlabel=\textbf{Size},">> ${filename}
echo "ymin=0," >> ${filename}
echo "ymax=${max_y}," >> ${filename}
echo "xmin=0," >> ${filename}
((xmax=${nb_sizes}+1))
echo "xmax=${xmax}," >> ${filename}
echo "ylabel=\textbf{${UNIT}},">> ${filename}
echo " xtick={1,...,15}, " >> ${filename}

echo "xticklabels={ ">> ${filename}
for ((ii=0;ii<${nb_sizes};ii++));do
  echo  "\tiny\scalebox{0.75}{{${SIZE[$ii]}}},">> ${filename}
done
echo "}">> ${filename}
echo "]" >> ${filename}
echo "\def \myBox#1{\rotatebox{90}{\scalebox{.4}{#1}}}" >> ${filename}

colors[0]="darkpastelgreen"
colors[1]="denim"
colors[2]="deepsaffron"
colors[3]="flame"
colors[4]="harvardcrimson"
colors[5]="cyan"
colors[6]="orange"
colors[7]="gray"

for ((ii=0;ii<${NUM_TEST};ii++));do
  ((color_pos=$ii%7))
  echo "\addlegendimage{${colors[$color_pos]},fill}" >> ${filename}
  ((le_pos=$ii+1))
  echo "\addlegendentry{{\scalebox{0.6}{${le[$le_pos]}}}}"  >> ${filename}
done

for ((ii=0;ii<${NUM_TEST};ii++));do
  ((color_pos=$ii%7))
  echo "\addplot[draw=black,fill=${colors[$color_pos]}," >> ${filename}
  echo "     nodes near coords," >> ${filename}
  echo "     point meta=explicit symbolic," >> ${filename}
  echo "]" >> ${filename}
  echo "table [meta index=2" >> ${filename}
  echo "     ] {" >> ${filename}
  echo "x       y       label       alignment" >> ${filename}
  for ((jj=0;jj<${nb_sizes};jj++));do
    ((pos=$ii*${nb_sizes}+$jj))
    if [ "$ii" -eq  "0" ]
    then
      speed_up=''
    else
      if [ "$UNIT" == "fps" ];then
        speed_up=$(echo ${CYC[jj]} ${CYC[pos]}  | awk '{printf "x%4.2f",$2/$1}')
      else
        speed_up=$(echo ${CYC[jj]} ${CYC[pos]}  | awk '{printf "x%4.2f",$1/$2}')
      fi
    fi
    ((index=$jj+1))
    echo "$index ${CYC[pos]} \myBox{${speed_up}}      -45" >> ${filename}
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
