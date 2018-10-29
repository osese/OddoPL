echo "************* TEST **************"

echo "testsymboltable"
  make testsymboltable
  ./testsymboltable.exe

echo "testhash"
  make testhash
  ./testhash.exe

echo "testhashtable"
  make testhashtable
  ./testhashtable.exe

echo "testvalue"
  make testvalue
  ./testvalue.exe

echo "testvstr"
  make testvstr
  ./testvstr.exe

echo "testvstr_per"
  make testvstr_per
  ./testvstr.exe 

make clean 
