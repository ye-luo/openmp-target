for folder in [0-9]-*
do
  cd $folder
  make
  cd ..
done
