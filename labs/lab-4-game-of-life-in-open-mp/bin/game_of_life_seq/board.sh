if [[ $# != 3 ]]; then
    echo "Usage: $(basename $0) Prob nRows nCols"
    exit 1  
fi

P=$1
R=$2
C=$3

echo Rows: $R
echo Cols: $C
for i in $(seq 1 $R); do
    for j in $(seq 1 $C); do
        read -n 1 n
        v=$(echo -n "$n" | od -An -t uC)
        if [[ $v -le $P ]]; then
            echo -n "#"
        else
            echo -n "."
        fi
    done
    echo
done < /dev/random