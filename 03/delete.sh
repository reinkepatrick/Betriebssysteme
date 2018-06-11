# Löschen

if [ ! -e $HOME/.trashbin ]; then
  $(mkdir $HOME/.trashbin)
fi

if [ ! -e $HOME/.trashbin/.dir ]; then
  $(touch $HOME/.trashbin/.dir)
fi

if [ ! -f $1 ]; then
  echo 'Datei nicht vorhanden.'
else
  TIMESTAMP=$(date '+%y%m%d%H%M%S')
  FILENAME="$TIMESTAMP""_$$.dat"
  $(mv $1 $HOME/.trashbin/$FILENAME)
  $(echo "$FILENAME! $(pwd)/$1" >> $HOME/.trashbin/.dir)

  echo $FILENAME
fi
