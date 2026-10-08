# Pointers

## Установка
```bash
cd ~
git clone https://github.com/IastrebovVladimir/Pointers
cd Pointers
git clone https://github.com/google/googletest.git
```

## Запуск тестов

```bash
g++ -g -O0 -std=c++20 tests/testShared.cpp tests/testUnique.cpp -I. -isystem googletest/googletest/include -Igoogletest/googletest googletest/googletest/src/gtest-all.cc googletest/googletest/src/gtest_main.cc -pthread -o PtrTests
./PtrTests --gtest_print_time=1
```
