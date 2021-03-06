Для компиляции под линукс в консоли:
-----------------------------------
g++ -Wall -g -c AdjList.cpp -o al.o -std=c++11
g++ -Wall -g -c main.cpp -o m.o -std=c++11
g++ m.o al.o -o m
-----------------------------------

Запуск в консоли:
-----------------------------------
./m
-----------------------------------

Для вывода списка имён по задаче с номером n, ввести соответствующее число.
Для выхода ввести число 4.

###########################################################################

ФОРМАТ ФАЙЛОВ:
1) Полный список имён (ПСИ) - файл с названием "names.txt". Все непустые строки - имена. Каждая следующая непустая строка - следующее имя в упорядоченном списке. Символы в формате ASCII.
2) 2-й файл предствляет список смежности. Элементы списка - числа. Каждое число - номер имени в ПСИ, начиня с нуля. Номер строки соответствует номеру имени в ПСИ. Строка не может содержать число со своим номером. Числа в строке записываются через пробелы, и должны быть различны. Все числа не должны превышать номера последнего имени в ПСИ.
Название файла "AdjList.txt". Пустая строка, с номером не больше максимального номера имени в ПСИ, означает что соответствующему человеку никто не нравится.
Если строка не пустая, то в ней должно присутствовать число, удовлетворяющее требованиям (т.е. если ребёнку никто не нравится, то в соответствующей строке симпатий не должно быть ни каких символов).

Пример файла AdjList.txt:
-----------------------------------
1
2 0
3
0
-----------------------------------
т.е. 0-му нравится 1-й, 1-му 0-й и 2-й, 2-му 3-й, 3-му 0-й.

Пример ПСИ names.txt:
-----------------------------------
Andry
Mary
Garry
Anny
-----------------------------------
номера будут присвоены так: Andry = 0, Mary = 1, Garry = 2, Anny = 3.

###########################################################################

АНАЛИЗ ПРОГРАММЫ:
Задача представляется в виде орграфа, где дети представляются вершинами, симпатия a к b - дуга из a в b. Граф представляем в виде списка смежностей для экономии памяти.

Для хранения списка смежности используется структура - вектор неориентированных множеств, точнее массив указателей на хеш (без значений), где ключ - номер имени в ПСИ. Таким образом, проверка наличия одностороннй симпатии проверяется за константу (в среднем).
Вычисление списка "всех не любимчиков" за линейное время, пробегаясь по списку смежности по одному разу, подсчитывая количество входящих дуг (дуга - ориентированное ребро - односторонняя симпатия) создаём вспомогательный массив. На основе которого вычисляем и список "любимчиков", найдя максимальное значение в полученном массиве за один проход.
Вычисление списка "несчастных детей" происходит так же через вспомогательный массив с подсчётом количества симпатий, но при условии взаимной симпатии, что вычисляется проверкой наличия нашего человека (вершина a) в хеше на который (хеш) ссылается элемент главного массива с номером проверяемого человека (вершина b). Все обращения происходят в среднем за константу.
На основе полученных массивов можно быстро выбрать только те элементы (номера имён), которые соответствуют условию максимума или нулевого количества.

Вычисление всех списков происходит за O(N), где N - суммарный объём файлов (точнее, можно ограничиться размером списка смежностей). Требуемая память тоже O(N). Но константа из-за использования хеша (unordered_set) большая, как для памяти, так и для времени. Поэтому программа имеет преимущество на больших объёмах входных данных и разреженном графе (т.е. с малым количеством рёбер).

Если же граф будет с высокой средней степенью вершин (соизмеримой с количеством вершин), то имеет смысл заменить хеш на массив. Тогда проверка наличия дуги будет так же за константу. При этом не будет трудоёмких вычислений хеш функций и дальнейших многократных обращений к памяти. Расходы на память так же сократятся. Плюс улучшится кеширование.
Третий вариант - массив упорядоченных массивов т.е. обычный список смежности. Тогда бинарный поиск за O(log(N)) будет проверять наличие дуги. Тогда расходы на память будут всегда оптимальны, но временные затраты на вычисления O(N*log(N)) будут заметно хуже при больших объёмах данных.


Детальнее разберём функцию AdjList::CalcDegrees и AdjList::UpdateDegreesInfoByNextNode
1) В цикле
    for (AList::iterator it = adjList.begin (); it != adjList.end (); it++, idx++)
  мы пробегаем по всем именам, где *it - список (хеш) с симпатиями
  от ребёнка с номером idx в ПСИ.
2) В цикле
    for (hashid::iterator hit = (*it) -> begin (); hit != (*it) -> end (); hit++)
  пробегаем по всем номерам детей (*hit - номер в ПСИ), которые
  нравятся ребёнку с номером idx.
3) innerDegrees [*hit] - подсчитывает количество различных детей,
  которым нравится ребёнок с номером *hit. innerDegrees - вектор,
  поэтому операция [] срабатывает за константу.
4) maxInnerDegree - параллельно вычисляет максимум innerDegrees.
5) adjList [*hit] -> find (idx) - проверяет, есть ли взаимность от ребёнка
  с номером (*hid). (*adjList[*hit]) - хеш, а значит метод find(idx) в среднем,
  выполняется за константу.
6) reflectDegrees [idx] - аналогично innerDegrees, накапливает количество
   симпатий, но с условием наличия симпатии.

Таким образом, AdjList::CalcDegrees - пробегает по всем элементам
(которых всего O(N)) по одному разу, и на каждой итерации производит
константное (в среднем) число операций.

AdjList::NamesWithEmptyDegreeCount, AdjList::NamesWithEmptyReflectDegreeCount
и AdjList::NamesWithMaxDegreeCount - вычиляют нужные списки для ответов на
все 3 задачи. За O(n), где n - количество имён в ПСИ.

