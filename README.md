# 3sem-Algorithms
Репозиторий с решением задач 3 семестра по предмету "Алгоритмы и структуры данных" МФТИ ФИВТ(2019)  
## Условия задач

### task1

#### problem A  
Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
p <= 30000, n <= 300000.

Использовать один из методов:
- С помощью префикс-функции;
- С помощью z-функции.

#### problem B1  
Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.

#### problem B2  
Найти лексикографически-минимальную строку, построенную по z-функции, в алфавите a-z.

#### problem C  
Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”. 
Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает, что все обычные символы 
совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ. 
Гарантируется, что сам “?” в тексте не встречается.

Время работы - O(n + m + Z), где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте. 
m ≤ 5000, n ≤ 2000000.

### task2

#### problem A  
Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.  
Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).

#### problem C  
Заданы две строки s, t и целое число k. Рассмотрим множество всех таких непустых строк, которые встречаются как 
подстроки в s и t одновременно. Найдите k-ую в лексикографическом порядке строку из этого множества.  

### task3

#### problem A  
Даны два отрезка в пространстве (x1, y1, z1) - (x2, y2, z2) и (x3, y3, z3) - (x4, y4, z4).  
Найдите расстояние между отрезками.

#### problem B  
Даны n точек в пространстве. Никакие 4 точки не лежат в одной плоскости. Найдите выпуклую оболочку этих точек за O(n*log(n)). 

#### problem C  
Даны два выпуклых многоугольника на плоскости. В первом n точек, во втором m. Определите, пересекаются ли они за O(n + m)

#### problem D
Даны точки, никакие 3 из которых не лежат на одной прямой. Никакие 4 точки не лежат на одной окружности. Кроме того, 
все точки имеют различные x-координаты. 
Определите среднее число сторон в многоугольниках диаграммы Вороного этого множества точек. Считаются только конечные 
многоугольники. Если все многоугольники неограниченны, ответ полагается равным 0. Число точек n ≤ 100000. Алгоритм должен 
иметь асимптотику O(n log n). 

[task4](https://docs.google.com/document/d/1G2ti3Vg6jXe6FLPZqwceZwYlzt8M6yA-IOrXf-AjurA/edit)




