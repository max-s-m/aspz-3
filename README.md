# Завдання 1

## Умова:

Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Для цього виконайте команди у вказаному порядку:
- $ ulimit -n
- $ ulimit -aS | grep "open files"
- $ ulimit -aH | grep "open files"
- $ ulimit -n 3000
- $ ulimit -aS | grep "open files"
- $ ulimit -aH | grep "open files"
- $ ulimit -n 3001
- $ ulimit -n 2000
- $ ulimit -n
- $ ulimit -aS | grep "open files"
- $ ulimit -aH | grep "open files"
- $ ulimit -n 3000

Як наступне вправу, повторіть перераховані команди з root-правами.

## Опис:

Було прописано у консолі запропоновані команди. Для цього запущено ubuntu Docker-контейнер у інтерактивному режимі (-it) з шеллом bash.
Перший раз команди прописано у непривілейованому режимі, а вдруге - з флагом --privileged, тобто з root-правами.
У другому випадку спостерігалося успішне виконання команд, які були не дозволені (operation not permitted) у першому.

## Результат виконання:

### Непривілейований режим

```
max@ASPZ:~$ sudo docker run -it ubuntu bash 
Unable to find image 'ubuntu: latest locally 
latest: Pulling from library/ubuntu 
5a7813e071bf: Pull complete 
Digest: sha256:72297848456d5d37d1262630108ab308d3e9ec7ed1c3286a32fe09856619a782 
Status: Downloaded newer image for ubuntu: latest 
root@800500e84d71:/# ulimit -n 
1048576 
root@800500e84d71:/# ulimit -as | grep "open files" 
open files 
(-n) 1048576 
root@800500e84d71:/# ulimit -aH | grep "open files" 
open files 
(-n) 1048576 
root@800500e84d71:/# ulimit -n 3000 
root@800500e84d71:/# ulimit -as | grep "open files" 
open files 
(-n) 3000 
root@800500e84d71:/# ulimit -aH | grep "open files" 
open files 
(-n) 3000 
root@800500e84d71:/# ulimit -n 3001 
bash: ulimit: open files: cannot modify limit: Operation not permitted 
root@800500e84d71:/# ulimit -n 2000 
root@800500e84d71:/# ulimit -n 
2000 
root@800500e84d71:/# ulimit -as | grep "open files" 
open files 
(-n) 2000 
root@800500e84d71:/# ulimit -aH | grep "open files" 
open files 
(-n) 2000 
root@800500e84d71:/# ulimit -n 3000 
bash: ulimit: open files: cannot modify limit: Operation not permitted 
root@800500e84d71:/# sudo ulimit -n 
bash: sudo: command not found 
root@800500e84d71:/# exit 
exit
```

### Привілейований режим (root-права):

```
max@ASPZ:~$ sudo docker run -privileged -it ubuntu bash 
root@88651dcebf4a:/# ulimit -n 
1048576 root@88651dcebf4a:/# ulimit -as | grep "open files" (-n) 1048576 
open files 
root@88651dcebf4a:/# ulimit -aH | grep "open files" (-n) 1048576 
open files 
root@88651dcebf4a:/# ulimit -n 3000 
root@88651dcebf4a:/# ulimit -as | grep "open files" (-n) 3000 
open files 
root@88651dcebf4a:/# ulimit -aH | grep "open files" (-n) 3000 
open files 
root@88651dcebf4a:/# ulimit -n 3001 
root@88651dcebf4a:/# ulimit -n 2000 
root@88651dcebf4a:/# ulimit -n 
2000 
root@88651dcebf4a:/# ulimit -as | grep "open files" (-n) 2000 
open files 
root@88651dcebf4a:/# ulimit -aH | grep "open files" (-n) 2000 
open files 
root@88651dcebf4a:/# ulimit -n 3000 
root@88651dcebf4a:/# exit 
exit
```

# Завдання 2

## Умова:

У Docker-контейнері встановіть утиліту perf(1). Поекспериментуйте з досягненням процесом встановленого ліміту.

## [Програмний код](2.c)

## Опис:

Встановлено утиліту perf(1) та перевірено її наявність.
Написано програму для досягнення заданого користувачем ліміту ulimit -n, що обмежує кількість одночасно відкритих файлів.
Програма досить проста і нескінченним циклом while відкриває багато разів один і той же файл "empty", церез що швидко досягається ліміт.
При незмозі програмою відкрити ще один файл, повідомляється число вже відкритих (i), що рахувалися у циклі.

## Результат виконання:

```
root@fe7c9996b432:/# gcc -Wall 2.c -o 2 
root@fe7c9996b432:/# ulimit -n 
1048576 
root@fe7c9996b432:/# ulimit -n 1000 
root@fe7c9996b432:/# ulimit -n 
1000 
root@fe7c9996b432:/# ./2 
Limit reached. Opened 997 files 
root@fe7c9996b432:/# ulimit -n 100 
root@fe7c9996b432:/# ulimit -n 
100 
root@fe7c9996b432:/# ./2 
Limit reached. Opened 97 files 
root@fe7c9996b432:/# perf-version 
perf version 6.8.12 
root@fe7c9996b432:/# 
```

# Завдання 3

## Умова:

Напишіть програму, що імітує кидання шестигранного кубика. Імітуйте кидки, результати записуйте у файл,
для якого попередньо встановлено обмеження на його максимальний розмір (max file size). Коректно обробіть ситуацію перевищення ліміту.

## [Програмний код](3.c)

## Опис:

Написано програму, що за допомогою rand() симулює та записує у файл [rolls.txt](rolls.txt) кидки шестигранного кубика.
При досягненні ліміту розміру нового файлу (ulimit -f) система надсилає сигнал SIGXFSZ (SIGnal eXceeded File SiZe) за допомогою signal().
Оброблюється досягнення ліміту викликом користувацької функції limit_reached(), що надсилає відповідне повідомлення та зупиняє програму.

## Результат виконання:

```
max@aspz:~/c/3 $ ulimit -f 1
max@aspz:~/c/3 $ ulimit -f
1
max@aspz:~/c/3 $ ./3
I'm gonna stop you right there'
max@aspz:~/c/3 $ ls -l
total 36
-rwxr-xr-x  1 max max 8624 Mar 28 15:54 2
-rw-r--r--  1 max max  315 Mar 28 15:23 2.c
-rwxr-xr-x  1 max max 9696 Mar 29 12:29 3
-rw-r--r--  1 max max  735 Mar 29 12:28 3.c
-rw-r--r--  1 max max  512 Mar 29 12:29 rolls.txt
```

# Завдання 4

## Умова:

Напишіть програму, що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36.
Встановіть обмеження на час ЦП (max CPU time) і генеруйте результати вибору чисел (7 із 49, 6 із 36).
Обробіть ситуацію, коли ліміт ресурсу вичерпано.

## [Програмний код](4.c)

## Опис:

Створено програму для імітації лотереї і вибору 6 з 36 і 7 з 49 різних чисел. Для обмеження часу ЦПУ використано ulimit -t.
Запуск цього коду є дуже легким для процесора, ulimit -t 1 (1 - найменше значення) обмежує до 1 секунди виконання, через що
програма вибору кількох випадкових чисел такого ліміту не досягне, проте обробку досягнення ліміту у коді реалізовано.
signal() з параметром SIGXCPU (SIGnal eXceeded CPU time) викликає функцію limit_reached(), що закриває програму, при отриманні сигналу
про досягенння ліміту на час роботи ЦП.

## Результат виконання:

```
max@aspz:~/c/3 $ ulimit -t 1
max@aspz:~/c/3 $ ulimit -t
1
max@aspz:~/c/3 $ ./4
7 із 49: 32 38 36 24 7 28 34
6 із 36: 1 28 23 21 24 30
```

# Завдання 5

## Умова:

Напишіть програму для копіювання одного іменованого файлу в інший. Імена файлів передаються у вигляді аргументів.
Програма має:
- перевіряти, чи передано два аргументи, інакше виводити "Program need two arguments";
- перевіряти доступність першого файлу для читання, інакше виводити "Cannot open file .... for reading";
- перевіряти доступність другого файлу для запису, інакше виводити "Cannot open file .... for writing";
- обробляти ситуацію перевищення обмеження на розмір файлу.

## [Програмний код](5.c)

## Опис:

Програма відкриває файли [from.txt](from.txt) як файл з якого копіюється, та [to.txt](to.txt) як файл у який копіюється текст.
При незмозі відкрити файл (!from чи !to) видається вказане умовою відповідне повідомлення про помилку та закривається програма.
Назви файлів передаються як аргументи у консолі, наявність яких перевіряється та про неправильну кількість аргументів повідомляється.
Обробка досягнення ulimit -f подібна до [завдання 3](#Опис-2), а через побуквенне копіювання момент досягнення ліміту видно у [тексті](to.txt).

## Результат виконання:

```
max@aspz:~/c/3 $ ulimit -f 1
max@aspz:~/c/3 $ ulimit -f
1
max@aspz:~/c/3 $ ./5
Program need two arguments
max@aspz:~/c/3 $ ./5 from.txt
Program need two arguments
max@aspz:~/c/3 $ ./5 from.txt to.txt

I'm gonna stop you right there
max@aspz:~/c/3 $ ls -l
total 76
-rwxr-xr-x  1 max max 8624 Mar 28 15:54 2
-rw-r--r--  1 max max  315 Mar 28 15:23 2.c
-rwxr-xr-x  1 max max 9696 Mar 29 14:47 3
-rw-r--r--  1 max max  734 Mar 29 14:54 3.c
-rwxr-xr-x  1 max max 9808 Mar 29 14:45 4
-rw-r--r--  1 max max  882 Mar 29 14:54 4.c
-rwxr-xr-x  1 max max 9624 Mar 29 15:57 5
-rw-r--r--  1 max max  915 Mar 29 15:56 5.c
-rw-r--r--  1 max max  581 Mar 29 15:58 from.txt
-rw-r--r--  1 max max  512 Mar 29 14:48 rolls.txt
-rw-r--r--  1 max max  512 Mar 29 15:57 to.txt
```

# Завдання 6

# Умова:

Напишіть програму, що демонструє використання обмеження (max stack segment size). Підказка: рекурсивна програма активно використовує стек.

## [Програмний код](6.c)

## Опис:

Написано програму, яка використовує рекурсивну функцію rec() для забивання стеку (досягнення ліміту ulimit -s).
В якості аргумента передається кількість рекурсій, що при успішному виконанні всіх рекурсій виводить повідомлення "Recursion finished".
У випадку ж перевищення ліміту розміру stack сегменту, система "викидує" стек процесу, через що використання signal для обробки цього неможливе.
Обробку випадку досягнення ліміту не реалізовано це не передбачено умовою.

## Результат виконання:

```
max@aspz:~/c/3 $ ulimit -s
524288
max@aspz:~/c/3 $ ./6 100000
Recursing 100000 times...
Recursion finished
max@aspz:~/c/3 $ ./6 1000000
Recursing 1000000 times...
Recursion finished
max@aspz:~/c/3 $ ./6 10000000
Recursing 10000000 times...
Recursion finished
max@aspz:~/c/3 $ ./6 100000000
Recursing 100000000 times...
pid 1192 comm 6 has trashed its stack, killing
Illegal instruction (core dumped)
max@aspz:~/c/3 $ ulimit -s 1000
max@aspz:~/c/3 $ ulimit -s
1000
max@aspz:~/c/3 $ ./6 10000
Recursing 10000 times...
Recursion finished
max@aspz:~/c/3 $ ./6 100000
Recursing 100000 times...
pid 1194 comm 6 has trashed its stack, killing
Illegal instruction (core dumped)
```

# Завдання 7 за варіантом 18

## Умова:

Написати багатопотокову програму, яка перевіряє вплив ulimit -u.

## [Програмний код](7.c)

## Опис:

Написано програму, яка за допомогою fork() у циклі дублює поточний процес кількість разів, яка передана у вигляді аргументу.
fork() окрім дублікації процесу також повертає елемент типу pid_t, значення якого каже про вид поточного процесу:
- >0: батьківський процес
- 0: дочірній процес
- <0: процес не створився
Кожний дочірній (дуплікований) процес "спить" 1 секунду, що дає змогу іншим процесам створюватися і таким чином накопичуватися.
Це призводить до заповнення списку поточних процесів і досягенення ліміту ulimit -u, що визначається якщо pid < 0 (новий процес не створився).

## Результат виконання:

```
max@aspz:~/c/3 $ ulimit -u
12186
max@aspz:~/c/3 $ ./7 100
fork'd well
max@aspz:~/c/3 $ ./7 1000
fork'd well
max@aspz:~/c/3 $ ulimit -u 500
max@aspz:~/c/3 $ ulimit -u
500
max@aspz:~/c/3 $ ./7 100
fork'd well
max@aspz:~/c/3 $ ./7 1000
forkn't
```
