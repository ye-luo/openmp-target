for folder in [0-9]-*
do
  cd $folder
  make clean; make
  ./gemv*.x
  cd ..
done
