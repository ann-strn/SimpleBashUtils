#!/bin/bash
echo "test without flags. if blank - all ok"

    diff <(../../grep/s21_grep home g_test.txt) <(grep home g_test.txt)
    diff <(../../grep/s21_grep home g_test.txt g_test1.txt) <(grep home g_test.txt g_test1.txt)

echo "test mult -e flags. if blank - all ok"

    diff <(../../grep/s21_grep -e home -e alex -e alla g_test.txt) <(grep -e home -e alex -e alla g_test.txt)
    diff <(../../grep/s21_grep -e home -e alex -e alla g_test.txt g_test1.txt) <(grep -e home -e alex -e alla g_test.txt g_test1.txt)

echo "test mult -f flags. if blank - all ok"

    diff <(../../grep/s21_grep -f find.txt -f find1.txt g_test.txt) <(grep -f find.txt -f find1.txt g_test.txt)
    diff <(../../grep/s21_grep -f find.txt -f find1.txt g_test.txt g_test1.txt) <(grep -f find.txt -f find1.txt g_test.txt g_test1.txt)


echo "test one flag (exept -f). if blank - all ok"
for var1 in -i -e -v -l -n -o -c -h -s
do
    diff <(../../grep/s21_grep $var home g_test.txt) <(grep $var home g_test.txt)
    diff <(../../grep/s21_grep $var home g_test.txt g_test1.txt) <(grep $var home g_test.txt g_test1.txt)
done

echo "test one flag -f. if blank - all ok"

    diff <(../../grep/s21_grep -f find.txt g_test.txt) <(grep -f find.txt g_test.txt)
    diff <(../../grep/s21_grep -f find.txt g_test.txt g_test1.txt) <(grep -f find.txt g_test.txt g_test1.txt)

echo "test two flag (exept -f -e). if blank - all ok"
for var1 in -v -l -n -h -o -c 
do
    for var2 in -v -l -n -h -o -c
    do
        if [ $var1 != $var2 ]
        then
                diff <(../../grep/s21_grep $var1 $var2 home g_test.txt) <(grep $var1 $var2 home g_test.txt)
                diff <(../../grep/s21_grep $var1 $var2 home g_test.txt g_test1.txt) <(grep $var1 $var2 home g_test.txt g_test1.txt)
        fi
    done
done

echo "test two flag -f.  if blank - all ok"
for var1 in -f 
do
    for var2 in -v -l -n -h -c
    do
        if [ $var1 != $var2 ]
        then
                diff <(../../grep/s21_grep $var2 $var1 find.txt g_test.txt) <(grep $var2 $var1 find.txt g_test.txt)
                diff <(../../grep/s21_grep $var2 $var1 find.txt g_test.txt g_test1.txt) <(grep $var2 $var1 find.txt g_test.txt g_test1.txt)
        fi
    done
done


echo "test two flag -e.  if blank - all ok"
for var1 in -e 
do
    for var2 in -v -l -n -h -c -o
    do
        if [ $var1 != $var2 ]
        then
                diff <(../../grep/s21_grep $var2 $var1 cat g_test.txt) <(grep $var2 $var1 cat g_test.txt)
                diff <(../../grep/s21_grep $var2 $var1 cat g_test.txt g_test1.txt) <(grep $var2 $var1 cat g_test.txt g_test1.txt)

                diff <(../../grep/s21_grep $var2 $var1 cat $var1 alla g_test1.txt) <(grep $var2 $var1 cat $var1 alla g_test1.txt)
                diff <(../../grep/s21_grep $var2 $var1 cat $var1 alla g_test1.txt g_test2.txt) <(grep $var2 $var1 cat $var1 alla g_test1.txt g_test2.txt)
        fi
    done
done


echo "test three flag.  if blank - all ok"
for var1 in -v -c -l -n -h -o
do
    for var2 in -v -c -l -n -h -o
    do
        for var3 in -v -c -l -n -h -o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then

                diff <(../../grep/s21_grep $var1 $var2 $var3 cat g_test.txt) <(grep $var1 $var2 $var3 cat g_test.txt)
                diff <(../../grep/s21_grep $var1 $var2 $var3 cat g_test.txt g_test1.txt) <(grep $var1 $var2 $var3 cat g_test.txt g_test1.txt)

            fi
        done
    done
done

echo "test three flag with -e.  if blank - all ok"
for var1 in -v -c -l -n -h -o
do
    for var2 in -v -c -l -n -h -o
    do
        for var3 in -e
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then

                diff <(../../grep/s21_grep $var1 $var2 $var3 cat $var3 alla g_test.txt) <(grep $var1 $var2 $var3 cat $var3 alla g_test.txt)
                diff <(../../grep/s21_grep $var1 $var2 $var3 cat $var3 alla g_test.txt g_test1.txt) <(grep $var1 $var2 $var3 cat $var3 alla g_test.txt g_test1.txt)

            fi
        done
    done
done

echo "test three flag with -f.  if blank - all ok"
for var1 in -v -c -l -n -h
do
    for var2 in -v -c -l -n -h 
    do
        for var3 in -f
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then

                diff <(../../grep/s21_grep $var1 $var2 $var3 find.txt g_test.txt) <(grep $var1 $var2 $var3 find.txt g_test.txt)
                diff <(../../grep/s21_grep $var1 $var2 $var3 find.txt g_test.txt g_test1.txt) <(grep $var1 $var2 $var3 find.txt g_test.txt g_test1.txt)

            fi
        done
    done
done


echo "test -s flag. if blank - all ok"

diff <(../../grep/s21_grep -s home df g_test.txt) <(grep -s home df g_test.txt)