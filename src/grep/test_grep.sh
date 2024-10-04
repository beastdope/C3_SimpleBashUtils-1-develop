#!/bin/bash
success=0
fail=0
# Список флагов для тестирования
flags=(
  "-i"
  "-v"
  "-c"
  "-l"
  "-n"
  "-h"
  "-s"
  "-o"
  "-e"
)

# Список файлов для тестирования
files=(
  "text.txt"
)

# Список строк для поиска
patterns=(
  "qwe"
)

# Функция для тестирования одного флага
# Функция для тестирования одного флага
function test_flag() {
  flag=$1
  pattern=$2
  file=$3

  # Запускаем оригинальный grep и сохраняем результат в файл
  grep $flag $pattern $file > system_grep_testing.log

  # Запускаем вашу программу и сохраняем результат в файл
  ./s21_grep $flag $pattern $file > s21_grep_testing.log

  # Преобразуем оба файла в UTF-8 перед сравнением
  iconv -f UTF-8 -t UTF-8 system_grep_testing.log >> system_grep_testing_utf8.log
  iconv -f UTF-8 -t UTF-8 s21_grep_testing.log >> s21_grep_testing_utf8.log

  # Сравниваем результаты
  if diff -q system_grep_testing_utf8.log s21_grep_testing_utf8.log >/dev/null ; then
    (( success++ ))
    echo "SUCCESS: $flag $pattern $file SUCCESS: $success"
  else
    (( fail++ ))
    echo "FAIL: $flag $pattern $file FAIL: $fail"
  fi

  # Удаляем временные файлы
   rm system_grep_testing.log s21_grep_testing.log system_grep_testing_utf8.log s21_grep_testing_utf8.log
}

# Проходим по всем комбинациям флагов, файлов и строк для поиска
for flag in "${flags[@]}"
do
  for file in "${files[@]}"
  do
    for pattern in "${patterns[@]}"
    do
      test_flag $flag $pattern $file
    done
  done
done
