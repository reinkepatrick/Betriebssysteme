TIME=$(date +'%H')
USER=$(whoami)
if (( TIME > 0 ))& (( TIME < 12 ));
then
    echo "Guten Morgen $USER"
elif (( TIME < 17 ));
then
    echo "Guten Tag $USER"
else
    echo "Guten Abend $USER"
fi
