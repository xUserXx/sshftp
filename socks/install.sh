#!/bin/bash


echo "COMPILLING FILE"

gcc socket.c -o socket

echo "COPYING FILE TO /usr/bin/ DIRECTORY"

sudo cp socket /usr/bin
echo " "
echo "INSTALATION COMPLETE"

echo "NOW READ THE README FILE"

sleep 1
echo "."
sleep 1
echo "."
sleep 1
echo "."

./README

echo " "
echo "THANKS FOR DOWNLOADING AND INSTALLING THIS PROGRAM"
