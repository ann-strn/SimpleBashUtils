#!/bin/bash

echo "test one flag. IF blank is ok"
for var1 in -b -e -n -s -t -v
do
    diff <(../../cat/s21_cat $var test.txt test2.txt) <(cat $var test.txt test2.txt)
    diff <(../../cat/s21_cat $var test.txt) <(cat $var test.txt)
done


echo "test one flag and blank file. IF blank is ok"

    diff <(../../cat/s21_cat $var test.txt test2.txt blank.txt) <(cat $var test.txt test2.txt blank.txt)
    diff <(../../cat/s21_cat $var test.txt blank.txt) <(cat $var test.txt blank.txt)

echo "test all flags. IF blank is ok"
    diff <(../../cat/s21_cat -b -e -n -s -t -v test.txt test2.txt) <(cat -b -e -n -s -t -v test.txt test2.txt)
    diff <(../../cat/s21_cat -b -e -n -s -t -v test.txt) <(cat -b -e -n -s -t -v test.txt)

echo "test all flags and blank. IF blank is ok"
    diff <(../../cat/s21_cat -b -e -n -s -t -v test.txt test2.txt blank.txt) <(cat -b -e -n -s -t -v test.txt test2.txt blank.txt)
    diff <(../../cat/s21_cat -b -e -n -s -t -v test.txt blank.txt) <(cat -b -e -n -s -t -v test.txt blank.txt)