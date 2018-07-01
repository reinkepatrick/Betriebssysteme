echo $0
DIV=$1
shift
PROD=1
while (( "$#" ));
do
    PROD=$(($PROD*$1))
    shift
done
echo $(($PROD/$DIV))
