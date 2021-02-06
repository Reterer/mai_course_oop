#!/bin/bash

find tests/ -name "test_??.txt" -print0 | while read -d $'\0' file
do
  resfile="${file%.*}.res.txt"
  ansfile="${file%.*}.ans.txt"
  build/oop_exercise_01 < "$file" >$resfile
  diff -qs $ansfile $resfile
  rm $resfile
done