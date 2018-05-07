#Wiederherstellen

if [ ! -e $HOME/.trashbin/.dir ]; then
  echo "Kein .dir"
fi

if [ ! -f $HOME/.trashbin/$1 ]; then
  echo "Datei nicht gefunden"
else
  cat $HOME/.trashbin/.dir | while read LINE; do
    if [[ $LINE =~ $1* ]]; then
      TEMPFILE=$(echo "$LINE" | cut -d'!' -f 1)
      NEWFILE=$(echo "$LINE" | cut -d' ' -f 2)
      TEMP=$(echo "$NEWFILE" | rev | cut -d'/' -f 1)

      if [ ! -d ${NEWFILE:0:(${#NEWFILE} - ${#TEMP})} ]; then
        echo "Verzeichnis existiert nicht mehr"
      else
        $(mv $HOME/.trashbin/$TEMPFILE $NEWFILE)
        $(sed -i '' "/^$TEMPFILE/d" $HOME/.trashbin/.dir)
      fi
    fi
  done
fi
