# Интерполяция численно-заданной функции одной переменной
Курсовая работа на тему интерполяция функций. 1 курс

## Использование
На вход программе идут 2 аргумента: первый — путь к файлу, второй — метод интерполяции.

Доступные методы интерполяции:
* fourier
* linear
* lanczos

В файле должны содержаться значения дискретной фунции разделенные новой линией.
Выходом программы является interpolated.csv в текущей директории, где храняться интерполированные данные.

Пример использования:
```shell
./intp_cli dvals.cpp fourier
```

## Сборка
Собирается как обычный CMake проект:
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

В директории ./build/ появиться файл intp_cli, что и является интструментом коммандной строки.
