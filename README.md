# homework2 08.03.23
## Фильтрация IP-адресов

## Задание
+ Цель задания – реализовать приложение обработки списка IP-адресов.
+ Программа из стандартного ввода читает данные. Данные хранятся построчно. Каждая строка состоит из трех полей, разделенных одним символом табуляции, и завершается символом конца строки.

+ mkdir build
+ cd build
+ cmake ../
+ cmake --build . --config Release|Debug

## Install build
+ cmake --install .

## Run tests (GTest & BoostTest)
### Linux
+ cmake --build . --target test --config Release|Debug
### Windows
+ cmake --build . --target RUN_TESTS --config Release|Debug

## CPack (build ZIP & DEB)
+ cpack -C Release|Debug

## Проверка Linux
+ apt update && apt install -y ip_filter-0.0.X-Linux.deb
+ (вместо X – номер Release tag'a)
+ cat ip_filter.tsv | ip_filter | md5sum или ip_filter ip_filter.tsv | md5sum
+ появился MD5 digest: 24e7a7b2270daee89c64d3ca5fb3da1a

## Проверка Windows
+ unzip ip_filter-0.0.X-win(64|32).zip
+ (вместо X – номер Release tag'a)
+ ip_filter ip_filter.tsv >> result.txt
+ Открыть result.txt в Notepad++
+ Выбрать Правка ->  Формат Конца Строк -> Преобразовать в Unix (LF)
+ Сохранить изменения
+ Выбрать Инструменты -> MD5 -> Сгенерировать из файлов...
+ Выбрать файлы для генерации MD5... (result.txt)
+ Получить результат (MD5 digest): 24e7a7b2270daee89c64d3ca5fb3da1a  result.txt