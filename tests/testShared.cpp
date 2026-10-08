#include <gtest/gtest.h>
#include <vector>
#include "../SharedPtr.h"

TEST(SharedTests, EmptyPointer) {
    SharedPtr<int> ptr;

    EXPECT_TRUE(ptr.Empty());
    EXPECT_EQ(ptr.GetReferenceCount(), 0u);
}

TEST(SharedTests, CreateObject) {
    SharedPtr<int> ptr(new int(10));

    EXPECT_FALSE(ptr.Empty());
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(ptr.GetReferenceCount(), 1u);
}

TEST(SharedTests, CopyConstructor) {
    SharedPtr<int> a(new int(10));
    EXPECT_EQ(a.GetReferenceCount(), 1u);

    SharedPtr<int> b(a);
    EXPECT_EQ(*a, 10);
    EXPECT_EQ(*b, 10);
    EXPECT_EQ(a.GetReferenceCount(), 2u);
    EXPECT_EQ(b.GetReferenceCount(), 2u);

    *b = 20;
    EXPECT_EQ(*a, 20);
    EXPECT_EQ(a.GetReferenceCount(), 2u);
    EXPECT_EQ(b.GetReferenceCount(), 2u);
}

TEST(SharedTests, CopyQual) {
    SharedPtr<int> first(new int(10));
    SharedPtr<int> second(new int(20));

    second = first;

    EXPECT_EQ(*first, 10);
    EXPECT_EQ(*second, 10);
    EXPECT_EQ(first.GetReferenceCount(), 2u);
    EXPECT_EQ(second.GetReferenceCount(), 2u);
}

TEST(SharedTests, MoveConstructor) {
    SharedPtr<int> first(new int(10));
    SharedPtr<int> second(std::move(first));

    EXPECT_TRUE(first.Empty());
    EXPECT_EQ(first.GetReferenceCount(), 0u);
    EXPECT_EQ(*second, 10);
    EXPECT_EQ(second.GetReferenceCount(), 1u);
}

TEST(SharedTests, MoveQual) {
    SharedPtr<int> first(new int(10));
    SharedPtr<int> second(new int(20));

    second = std::move(first);

    EXPECT_TRUE(first.Empty());
    EXPECT_EQ(first.GetReferenceCount(), 0u);
    EXPECT_EQ(*second, 10);
    EXPECT_EQ(second.GetReferenceCount(), 1u);
}

TEST(SharedTests, Reset) {
    SharedPtr<int> first(new int(10));
    SharedPtr<int> second = first;

    first.Reset(new int(30));

    EXPECT_EQ(*first, 30);
    EXPECT_EQ(first.GetReferenceCount(), 1u);
    EXPECT_EQ(*second, 10);
    EXPECT_EQ(second.GetReferenceCount(), 1u);

    first.Reset();
    EXPECT_TRUE(first.Empty());
    EXPECT_EQ(first.GetReferenceCount(), 0u);
}


TEST(SharedTests, Pointers10000) {
    SharedPtr<int> pointers[10000];
    SharedPtr<int> original(new int(67));
    pointers[0] = original;

    for (int i = 1; i < 10000; i++)
        pointers[i] = pointers[i - 1];

    EXPECT_EQ(original.GetReferenceCount(), 10001u);

    for (int i = 0; i < 10000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr);
        EXPECT_EQ(*pointers[i], 67);
    }

    for (int i = 0; i < 10000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 10000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr);
        else {
            EXPECT_NE(pointers[i].Get(), nullptr);
            EXPECT_EQ(*pointers[i], 67);
        }
    }
}

TEST(SharedTests, Pointers100000) {
    SharedPtr<int> pointers[100000];
    SharedPtr<int> original(new int(67));
    pointers[0] = original;

    for (int i = 1; i < 100000; i++)
        pointers[i] = pointers[i - 1];

    EXPECT_EQ(original.GetReferenceCount(), 100001u);

    for (int i = 0; i < 100000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr);
        EXPECT_EQ(*pointers[i], 67);
    }

    for (int i = 0; i < 100000; i += 2)
        pointers[i].Reset();

    for (int i = 0; i < 100000; i++) {
        if (i % 2 == 0)
            EXPECT_EQ(pointers[i].Get(), nullptr);
        else {
            EXPECT_NE(pointers[i].Get(), nullptr);
            EXPECT_EQ(*pointers[i], 67);
        }
    }
}

TEST(SharedTests, Pointers1000000) {
    std::vector<SharedPtr<int>> pointers(1000000);
    SharedPtr<int> original(new int(67));

    pointers[0] = original;

    for (std::size_t i = 1; i < 1000000; ++i) {
        pointers[i] = pointers[i - 1];
    }

    EXPECT_EQ(original.GetReferenceCount(), 1000000 + 1);

    for (std::size_t i = 0; i < 1000000; i++) {
        EXPECT_NE(pointers[i].Get(), nullptr) << "Индекс: " << i;
        EXPECT_EQ(*pointers[i], 67) << "Индекс: " << i;
    }

    for (std::size_t i = 0; i < 1000000; i += 2) {
        pointers[i].Reset();
    }

    for (std::size_t i = 0; i < 1000000; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(pointers[i].Get(), nullptr) << "Индекс: " << i;
        } else {
            EXPECT_NE(pointers[i].Get(), nullptr)  << "Индекс: " << i;
            EXPECT_EQ(*pointers[i], 67)  << "Индекс: " << i;
        }
    }

    pointers.clear();

    EXPECT_EQ(original.GetReferenceCount(), 1u);
    EXPECT_EQ(*original, 67);
}