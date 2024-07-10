## Задача

Реализовать [утилиту](https://ru.wikipedia.org/wiki/%D0%A3%D1%82%D0%B8%D0%BB%D0%B8%D1%82%D0%B0) PrintFile выводящую в стандартный  поток вывода содержимое(частичное содержимое)
для указанного файла.

Программа должна поддерживать следующие аргументы командной строки (опции):

**-l, --lines=n**   вывести только n (только положительное) первых(последних) строк файл  (необязательный аргумент, по-умолчанию выводим все)

**-t, --tail**      вывод n последний строк файла (необязательный аргумент)

**-d, --delimiter=c**  символ по которому определяется конец строки (нeобязательный, по-умолчанию '\n')

Название файла и опции передаются через аргументы командной строки в следующем формате:

_**PrintFile.exe [OPTION] filename**_

### Примеры запуска программы:

*PrintFile.exe filename*

*PrintFile.exe filename*

*PrintFile.exe --tail --lines=10 filename*

*PrintFile.exe -l 2 filename*

*PrintFile.exe -d '\t' filename*

*PrintFile.exe  filename -t -l 10*

## Рекомендации

* Стоит подумать о том, что размер файла может быть очень большим и значимо превышать размер оперативной памяти

* Стоит подумать каким образом разбить программу на логичные функции

* Не забывай про CodeStyle

## Дополнительная информация

Для реализации утилиты потребуется воспользоваться стандартной библиотекой вводы\вывода ([описание](https://en.cppreference.com/w/cpp/io/basic_ifstream)). [Пример использования](https://cplusplus.com/doc/tutorial/files/)

Пример того, как можно организовать  парсинг аргументов командной строки, можно посмотреть [здесь](http://www.cplusplus.com/articles/DEN36Up4/).

## Полезные источники

https://www.modernescpp.com/index.php/c-17-what-s-new-in-the-library/ - c++ 17 new features

https://habr.com/ru/companies/otus/articles/715608/ - string_view
