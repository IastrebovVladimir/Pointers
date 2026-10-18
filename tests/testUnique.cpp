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

TEST(UniqueTests, ArrayAccess) {
    UniquePtr<int[]> numbers(new int[3]{10, 20, 30});

    ASSERT_NE(numbers.Get(), nullptr);

    EXPECT_EQ(numbers[0], 10);
    EXPECT_EQ(numbers[1], 20);
    EXPECT_EQ(numbers[2], 30);

    numbers[1] = 100;

    EXPECT_EQ(numbers[1], 100);
}

TEST(UniqueTests, ArrayMoveConstructor) {
    UniquePtr<int[]> first(new int[3]{10, 20, 30});
    int* address = first.Get();

    UniquePtr<int[]> second(std::move(first));

    EXPECT_EQ(first.Get(), nullptr);
    ASSERT_EQ(second.Get(), address);

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[2], 30);
}

TEST(UniqueTests, ArrayMoveAssignment) {
    UniquePtr<int[]> first(new int[2]{10, 20});
    UniquePtr<int[]> second(new int[3]{30, 40, 50});

    int* address = first.Get();

    second = std::move(first);

    EXPECT_EQ(first.Get(), nullptr);
    ASSERT_EQ(second.Get(), address);

    EXPECT_EQ(second[0], 10);
    EXPECT_EQ(second[1], 20);
}

TEST(UniqueTests, ArrayReset) {
    UniquePtr<int[]> numbers(new int[2]{10, 20});

    numbers.Reset(new int[3]{30, 40, 50});

    ASSERT_NE(numbers.Get(), nullptr);
    EXPECT_EQ(numbers[0], 30);
    EXPECT_EQ(numbers[2], 50);

    numbers.Reset();

    EXPECT_EQ(numbers.Get(), nullptr);
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

TEST(UniqueTests, Pointers10000000) {
    std::vector<UniquePtr<int>> pointers(10000000);

    for (int i = 0; i < 10000000; i++)
        pointers[i].Reset(new int(i));

    for (int i = 0; i < 10000000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], i) << "Индекс: " << i;
    }

    for (int i = 0; i < 10000000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 10000000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr) << "Индекс: " << i;
        else {
            EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], i) << "Индекс: " << i;
        }
    }
}

TEST(UniqueTests, Pointers100000000) {
    std::vector<UniquePtr<int>> pointers(100000000);

    for (int i = 0; i < 100000000; i++)
        pointers[i].Reset(new int(i));

    for (int i = 0; i < 100000000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], i) << "Индекс: " << i;
    }

    for (int i = 0; i < 100000000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 100000000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr) << "Индекс: " << i;
        else {
            EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], i) << "Индекс: " << i;
        }
    }
}

TEST(UniqueTests, Pointers1000000000) {
    int total = 1000000000;
    int batchSize = 1000000;

    for (int offset = 0; offset < total; offset += batchSize) {
        std::vector<UniquePtr<int>> pointers(batchSize);

        for (int i = 0; i < batchSize; ++i) {
            pointers[i].Reset(new int(offset + i));
        }

        for (int i = 0; i < batchSize; ++i) {
            EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << offset + i;
            EXPECT_EQ(*pointers[i], offset + i) << "Индекс: " << offset + i;
        }

        for (int i = 0; i < batchSize; i += 2) {
            pointers[i].Reset();
        }

        for (int i = 0; i < batchSize; ++i) {
            if (i % 2 == 0) {
                EXPECT_EQ(pointers[i].Get(), nullptr) << "Индекс: " << offset + i;
            } else {
                EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << offset + i;
                EXPECT_EQ(*pointers[i], offset + i) << "Индекс: " << offset + i;
            }
        }
    }
}
