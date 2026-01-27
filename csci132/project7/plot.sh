#!/bin/bash

set -e

if [ $# -lt 4 ]; then
  echo "Missing parameter. Try something like this instead:"
  echo "   $0 ./program option 100 200 300 400"
  echo "This will run ./program option 100; ./program option 200; ./program option 300, etc.,"
  echo "and collect any output into a file for safe keeping. It will also"
  echo "extract any output lines of the form 'PLOT xval yval' into a"
  echo "separate comma-separated-value file, and plot those results as a"
  echo "PNG image."
  exit 1
fi

testprog="$1"
shift

if [ ! -x "$testprog" ]; then
  echo "Sorry, program not found: $testprog"
  echo "Try running this script without any parameters to get a help message."
  exit 1
fi

# # Pick a name to use for the text, csv, and png output files.
# outnum=1
# while [ -e "${testprog}-${outnum}.png" -o \
#   -e "${testprog}-${outnum}.txt" -o \
#   -e "${testprog}-${outnum}.csv" ]; do
#   outnum=$((outnum+1))
# done
# 
# outpng="${testprog}-${outnum}.png"
# outtxt="${testprog}-${outnum}.txt"
# outcsv="${testprog}-${outnum}.csv"

outpng="${1}.png"
outtxt="${1}.txt"
outcsv="${1}.csv"

rm -f "$outpng" "$outtxt" "$outcsv"

for n in "${@:2}"; do
  $testprog $1 $n | tee -a "$outtxt"
done

echo
echo "Extracting data from $outtxt to $outcsv, then plotting data as $outpng"

echo "ProblemSize, ExecutionTime" > "$outcsv"
awk -- '/^PLOT / { printf("%s, %s\n", $2, $3); }' "$outtxt" >> "$outcsv"

# grab the highest value, divide by 3
third=`tail -1 "$outcsv" | cut -d, -f1`
third=$((third/3))
five=`head -5 "$outcsv" | tail -1 | cut -d, -f1`
if [ $third -lt $five ]; then
  third=$five
fi

SCRIPT="
d <- read.csv(\"${outcsv}\", sep=\",\", header=TRUE)

model_linear1 <- lm(ExecutionTime ~ ProblemSize, data = subset(d, ProblemSize<=$third))
model_intercept <- coef(model_linear1)[1]
model_slope <- coef(model_linear1)[2]

png(filename = \"${outpng}\",
	width = 480, height = 480, units = \"px\", pointsize = 12,
	bg = \"white\",  res = NA,
	type = c(\"cairo\", \"cairo-png\", \"Xlib\", \"quartz\"))

plot(d\$ProblemSize, d\$ExecutionTime, type=\"o\", col=\"red\",
  xlab=\"Problem Size\", ylab=\"Time (seconds)\", main=\"${1} Execution Time\")
abline(a=model_intercept, b=model_slope)
"

Rscript <(echo "$SCRIPT")

echo
echo "See $outpng for results."
# xdg-open "$outpng"
