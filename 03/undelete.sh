#Wiederherstellen

if [ ! -e $HOME/.trashbin/.dir ]; then
  echo "Kein .dir"
fi

if [ ! -f $HOME/.trashbin/$1 ]; then
  echo "Datei nicht gefunden"
else
  cat $HOME/.trashbin/.dir | while read LINE; do
    if [[ $LINE =~ $1* ]]; then
      echo $LINE
      TARGET=$LINE
    fi
  done
  echo $TARGET
  echo $(echo"$TARGET" | cut -d' ' -f 1)
fi
