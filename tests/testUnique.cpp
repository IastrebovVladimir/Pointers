#include <gtest/gtest.h>
#include <stdexcept>
#include "../UniquePtr.h"


TEST(UniqueTests, EmptyPointer) {
    UniquePtr<int> ptr;

    EXPECT_EQ(ptr.Get(), nullptr);
}

TEST(UniqueTests, ChangeValue) {
    UniquePtr<int> ptr(new int(10));

    EXPECT_EQ(*ptr, 10);

    *ptr = 20;

    EXPECT_EQ(*ptr, 20);
}

TEST(UniqueTests, MoveConstructor) {
    UniquePtr<int> a(new int(10));
    EXPECT_EQ(*a, 10);

    UniquePtr<int> b(std::move(a));

    EXPECT_EQ(a.Get(), nullptr);
    EXPECT_NE(b.Get(), nullptr);
    EXPECT_EQ(*b, 10);
}

TEST(UniqueTests, MoveAssigment) {
    UniquePtr<int> a(new int(10));
    UniquePtr<int> b(new int(20));

    EXPECT_EQ(*a, 10);
    EXPECT_EQ(*b, 20);

    b = std::move(a);

    EXPECT_EQ(a.Get(), nullptr);
    EXPECT_NE(b.Get(), nullptr);
    EXPECT_EQ(*b, 10);
}

TEST(UniqueTests, Reset) {
    UniquePtr<int> ptr(new int(10));

    EXPECT_EQ(*ptr, 10);
    ptr.Reset(new int(20));

    EXPECT_NE(ptr.Get(), nullptr);
    EXPECT_EQ(*ptr, 20);
}

TEST(UniqueTests, Pointers10000) {
    UniquePtr<int> pointers[10000];

    for (int i = 0; i < 10000; i++)
        pointers[i].Reset(new int(i * 10));

    for (int i = 0; i < 10000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
    }

    for (int i = 0; i < 10000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 10000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        else {
            EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
        }
    }
}

TEST(UniqueTests, Pointers100000) {
    UniquePtr<int> pointers[100000];

    for (int i = 0; i < 100000; i++)
        pointers[i].Reset(new int(i * 10));

    for (int i = 0; i < 100000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
    }

    for (int i = 0; i < 100000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 100000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        else {
            EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
        }
    }
}

TEST(UniqueTests, Pointers1000000) {
    std::vector<UniquePtr<int>> pointers(1000000);

    for (int i = 0; i < 1000000; i++)
        pointers[i].Reset(new int(i * 10));

    for (int i = 0; i < 1000000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
    }

    for (int i = 0; i < 1000000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 1000000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr)  << "Индекс: " << i;
        else {
            EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], i * 10)  << "Индекс: " << i;
        }
    }
}