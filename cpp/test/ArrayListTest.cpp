#include "gtest/gtest.h"
#include "ArrayList.hpp"

void ArrayListTest_checkContents(IList& list) {
	for (int i = 0; i < list.getSize(); ++i) {
		ASSERT_EQ(i, list[i]);
	}
}

void ArrayListTest_smokeTestAdd(IList& list) {
	for (int i = 0; i < 20; ++i) {
		list.add(i);
	}
	ArrayListTest_checkContents(list);
}

void ArrayListTest_smokeTestAddRemove(IList& list) {
	ArrayListTest_smokeTestAdd(list);
	for (int i = 0; i < 20; ++i) {
		list.remove(0);
	}
}

TEST(ArrayList, TestDefaultConstructor) {
	ArrayList list = ArrayList();
	ASSERT_EQ(0, list.getSize());
	ArrayListTest_smokeTestAddRemove(list);
}

TEST(ArrayList, TestCustomConstructor) {
	ArrayList list = ArrayList(1,4,3,2);
	ASSERT_EQ(0, list.getSize());
	ArrayListTest_smokeTestAddRemove(list);
}

TEST(ArrayList, TestCustomConstructorZeroCapacity) {
	ArrayList list = ArrayList(0,4,3,2);
	ASSERT_EQ(0, list.getSize());
	ArrayListTest_smokeTestAddRemove(list);
}

TEST(ArrayList, TestCopyConstructor) {
	ArrayList list = ArrayList();
	ArrayListTest_smokeTestAdd(list);

	ArrayList other = ArrayList(list);
	ASSERT_NE(&list, &other);	

	ASSERT_EQ(list.getSize(), other.getSize());
	for (int i = 0; i < list.getSize(); ++i) {
		ASSERT_EQ(list[i], other[i]);
	}
}

TEST(ArrayList, TestIListConstructor) {
	IList* list = new ArrayList();
	ArrayListTest_smokeTestAdd(*list);

	ArrayList* other = new ArrayList(*list);

	//I have no idea if this is a valid assertion...
	ASSERT_NE(((ArrayList*)list), other);

	ASSERT_EQ(list->getSize(), other->getSize());
	for (int i = 0; i < list->getSize(); ++i) {
		ASSERT_EQ((*list)[i], (*other)[i]);
	}

	delete other;
	delete list;
}

TEST(ArrayList, TestAssignmentOperator) {
	ArrayList list = ArrayList();
	ArrayListTest_smokeTestAdd(list);

	ArrayList other = list;
	ASSERT_NE(&list, &other);	

	ASSERT_EQ(list.getSize(), other.getSize());
	for (int i = 0; i < list.getSize(); ++i) {
		ASSERT_EQ(list[i], other[i]);
	}
}

TEST(ArrayList, TestAddNoReallocation) {
	ArrayList list = ArrayList();

	int i = 0;
 	for (; i < ARRAY_LIST_INITIAL_CAPACITY; ++i) {
                list.add(i);
        }

        ASSERT_EQ(i, list.getSize());
        ArrayListTest_checkContents(list);
}

TEST(ArrayList, TestAddOneReallocation) {
	ArrayList list = ArrayList();

	int i = 0;
	for (; i < ARRAY_LIST_INITIAL_CAPACITY; ++i) {
		list.add(i);
	}
	ArrayListTest_checkContents(list);

	list.add(i++); 

	ASSERT_EQ(i, list.getSize());
	ArrayListTest_checkContents(list);

	for (; i < ARRAY_LIST_INITIAL_CAPACITY + 3; ++i) {
		list.add(i);
	}

	ASSERT_EQ(i, list.getSize());
	ArrayListTest_checkContents(list);
}

// Since I really cant test the internals here, this test
// pretty much boiled down to an arbitrary stress test
// that mimics the number of iterations done in the C tests.
TEST(ArrayList, TestAddStressTest) {
	ArrayList list = ArrayList();
	unsigned int i = 0;
	unsigned int goal = ARRAY_LIST_INITIAL_CAPACITY;
	for (int iteration = 0; iteration < 20; ++iteration) {
		for (; i < goal; ++i) {
			list.add(i);
		}
		ASSERT_EQ(i, list.getSize());
		ArrayListTest_checkContents(list);
		goal = i * ARRAY_LIST_ADD_REALLOCATION_MULTIPLIER;
	}
}
