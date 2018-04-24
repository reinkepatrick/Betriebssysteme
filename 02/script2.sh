#Aufgabe 2

function exists() {
  if [ -e $1 ]; then
    echo 'Die Datei oder das Verzeichnis existiert.'
  else
    echo 'Die Datei oder das Verzeichnis existiert nicht.'
  fi
}

function regular() {
  if [ -f $1 ] || [ -d $1 ]; then
    echo 'Es handelt sich um eine reguläre Datei oder ein Verzeichnis.'
  fi
}

function link() {
  if [ -h $1 ]; then
    echo 'Es handelt sich um einen symbolsichen Link.'
  fi
}

function amiowner() {
  local USER="$(whoami)"
  local OWNER="$(ls -l $1 | awk '{print $3}')"
  if [ $USER == $OWNER ]; then
    echo "Der Aufrufer ist der Besitzer der Datei."
  fi
}

function whoisowner() {
  local OWNER="$(ls -l $1 | awk '{print $3}')"
  echo "$OWNER ist der Besitzer."
}

for var in $@
do
  exists $1
  regular $1
  link $1
  amiowner $1
  whoisowner $1
  echo ""
done
