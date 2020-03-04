#!/bin/bash
booknumber=1
goodbooknumber=1
passfile="pass.rnk"
trap cleanup SIGINT SIGTERM SIGQUIT SIGHUP EXIT
function cleanup() {
if [ -e book$booknumber ]; then
rm -rf book$booknumber
exit
else
cd ..
rm -rf book$booknumber
exit
fi
}
while true; do
if [ -e book$booknumber ]; then
((booknumber++))
else
mkdir book$booknumber;
cp babelbot.exe book$booknumber;
cp searchbot.exe book$booknumber;
cp judgebot.exe book$booknumber;
cp en_US.txt book$booknumber;
cd book$booknumber;
./babelbot.exe book
for i in {1..410};
do ./searchbot.exe < Page"$i".txt;
done
./judgebot.exe
if [ -e $passfile ]; then
echo "book$booknumber pass"
rm babelbot.exe
rm searchbot.exe
rm judgebot.exe
rm en_US.txt
cd ..
mv book$booknumber Book$goodbooknumber 
((booknumber++))
else
cd ..
echo "book$booknumber fail"
rm -rf book$booknumber;
fi
fi
done