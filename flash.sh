#!/bin/sh

PORT=/dev/ttyUSB0

ls -lah images

echo "Copying Mackerel image..."
echo "load 300000" > $PORT
sleep 1
ctt -p $PORT -f images/linux.bin

sleep 1
echo "Booting Linux..."
echo "runrom" > $PORT

echo "Done"
