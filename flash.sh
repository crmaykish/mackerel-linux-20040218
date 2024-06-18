#!/bin/sh

PORT=/dev/ttyACM0

ls -lah images

echo "Copying filesystem image..."
echo "load 300000" > $PORT
sleep 1
ctt -p $PORT -f images/romfs.img

sleep 2

echo "Copying Mackerel image..."
echo "load 200000" > $PORT
sleep 1
ctt -p $PORT -f images/mackerel.rom

sleep 1
echo "Booting Linux..."
echo "runrom" > $PORT

echo "Done"
