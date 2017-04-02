#include <iostream>
#include "gtest\gtest.h"
#include "../implementation/vector.hpp"

TEST(Vector, Constructor_with_capacity)
{
	// GIVEN:
	//
	// vec_default - вектор созданный конструктором по умолчанию
	// vec - вектор созданный конструктором, принимающим величину вместимости (capacity)
	// init_capacity - вместимость вектора vec
	ava::Vector<int> vec_default;
	const size_t init_capacity = 15;
	ava::Vector<int> vec(init_capacity);

	// WHEN:
	//
	// vec_default_capacity - вместимость вектора vec_default
	// vec_default_size - размер вектора vec_default
	std::size_t vec_default_capacity = vec_default.capacity();
	std::size_t vec_default_size = vec_default.size();

	// THEN:
	//
	// вместимость и размер vec_default должны равняться 10 и 0 соответственно
	// вместимость и размер vec должны равняться 15 и 0 соответственно
	ASSERT_TRUE(vec_default_capacity == ava::default_capacity);
	ASSERT_TRUE(vec_default_size == 0);
	ASSERT_TRUE(vec.capacity() == init_capacity);
	ASSERT_TRUE(vec.size() == 0);
}

TEST(Vector, Constructor_with_size_and_value)
{
	// GIVEN:
	//
	// init_size - размер будующего вектора
	// init_value - величина, которой заполнятся элементы будующего стэка
	const size_t init_size = 2;
	const int init_value = 5;

	// WHEN:
	//
	// vec - вектор созданный конструктором который принимает размер вектора и величину, которую он присвоит всем элементам
	ava::Vector<int> vec(init_size, init_value);

	// THEN:
	//
	// размер вектора должен равняться init_size
	// элементы вектора должны равняться init_value
	ASSERT_TRUE(vec.size() == init_size);
	ASSERT_TRUE(vec[0] == init_value);
	ASSERT_TRUE(vec[1] == init_value);
}

TEST(Vector, Insert)
{
	// GIVEN:
	//
	// vec - вектор созданный конструктором по умолчанию (с вместимостью 10) и с двумя элементами (1, 2)
	ava::Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	// WHEN:
	//
	// Вставляем после первого элемента ещё два элемента равных 0
	vec.insert(1, 2, 0);

	// THEN:
	//
	// Должен получиться вектор [1, 0, 0, 2]. Проверяем
	ASSERT_TRUE( (vec[0] == 1) && (vec[1] == 0) && (vec[2] == 0) && (vec[3] == 2) );
}


TEST(Vector, Push_back)
{
	// GIVEN:
	//
	// vec - вектор созданный конструктором по умолчанию
	// value_to_push - значение, которое кладём в вектор
	ava::Vector<int> vec;
	int value_to_push = 15;

	// WHEN:
	//
	// кладём value_to_push в вектор
	vec.push_back(value_to_push);

	// THEN:
	//
	// Проверяем, что последний элемент в векторе равен тому, который мы туда положили
	ASSERT_TRUE(vec.back() == value_to_push);
}

TEST(Vector, Push_back_with_auto_incrementing_capacity)
{
	// GIVEN:
	//
	// init_capacity - начальная вместимость вектора
	// vec - вектор созданный конструктором, который принимает величину вместимости (capacity). vec содержит два элемента: 10 и 20
	std::size_t init_capacity = 2;
	ava::Vector<int> vec(init_capacity);
	vec.push_back(10);
	vec.push_back(20);

	// WHEN:
	//
	// Кладём третий элемент 30
	vec.push_back(30);

	// THEN:
	//
	// Проверяем, что вместимость (capacity) вектора увеличилась
	ASSERT_TRUE(vec.capacity() > init_capacity);
}

class Vector_Object_For_Testing_Single_Vec : public testing::Test
{
public:
	Vector_Object_For_Testing_Single_Vec() :vec_(init_capacity_) {
		vec_[0] = 10;
		vec_[1] = 20;
	}

protected:
	const size_t init_capacity_ = 3;
	const size_t init_size_ = 2;
	ava::Vector<int> vec_;
};

TEST_F(Vector_Object_For_Testing_Single_Vec, Copy_constructor)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec

	// WHEN:
	// 
	// copy_vec - вектор скопированный из vec_ (конструктором копирования)
	ava::Vector<int> copy_vec(vec_);

	// THEN:
	//
	// Размеры, вместимости (capacity) и элементы исходного и скопированного векторов должны совпадать
	ASSERT_TRUE(vec_.size() == copy_vec.size());
	ASSERT_TRUE(vec_.capacity() == copy_vec.capacity());
	ASSERT_TRUE(copy_vec[0] == vec_[0]);
	ASSERT_TRUE(copy_vec[1] == vec_[1]);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Pop_back)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)

	// WHEN:
	// 
	// Вытаскиваем элемент из вектора
	vec_.pop_back();

	// THEN:
	//
	// Размер вектора должен уменьшиться на 1
	ASSERT_TRUE(vec_.size() == (init_size_ - 1));
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Reduction)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)

	// WHEN:
	//
	// изменяем размер вектора с 2 на 1 и записываем новый размер вектора в vec_new_size
	vec_.resize(1);
	size_t vec_new_size = vec_.size();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 1 и его элемент равен 10
	ASSERT_TRUE(vec_new_size == 1);
	ASSERT_TRUE(vec_[0] == 10);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Size)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// value_for_new_elements - значение которое приписывается новым элементами при изменении размера в большую сторону
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// изменяем размер вектора с 2 на 3 и записываем новый размер вектора в vec_new_size
	vec_.resize(3, value_for_new_elements);
	size_t vec_new_size = vec_.size();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 3 и его элемент равен 10
	ASSERT_TRUE(vec_new_size == 3);
	ASSERT_TRUE(vec_[0] == 10);
	ASSERT_TRUE(vec_[1] == 20);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Resize_With_Bigger_Capacity)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// value_for_new_elements - значение которое приписывается новым элементами при изменении размера в большую сторону
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// изменяем размер вектора с 2 на 3 и записываем новый размер вектора в vec_new_size, а новую вместимость в vec_new_capacity
	vec_.resize(4, value_for_new_elements);
	size_t vec_new_size = vec_.size(), vec_new_capacity = vec_.capacity();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 4, вместимость увеличилась, а новые элементы равны value_for_new_elements
	ASSERT_TRUE(vec_new_size == 4);
	ASSERT_TRUE(vec_new_capacity > init_capacity_);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
	ASSERT_TRUE(vec_[3] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Less_Than_Size)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// value_for_new_elements - значение которое приписывается новым элементами
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// Присваиваем вектору новое содержимое: один элемент, который равен value_for_new_elements
	// Записываем новый размер вектора в vec_size, а новую вместимость в vec_capacity
	vec_.assign(1, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 1, вместимость не изменилась, а единственный элемент равен 
	ASSERT_TRUE(vec_size == 1);
	ASSERT_TRUE(vec_capacity == init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Less_Than_Capacity_And_Bigger_Than_Size)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// value_for_new_elements - значение которое приписывается новым элементами
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// Присваиваем вектору новое содержимое: три элемента, каждый из которых равен value_for_new_elements
	// Записываем новый размер вектора в vec_size, а новую вместимость в vec_capacity
	vec_.assign(3, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 3, вместимость не изменилась, а три элемента равны  value_for_new_elements
	ASSERT_TRUE(vec_size == 3);
	ASSERT_TRUE(vec_capacity == init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
	ASSERT_TRUE(vec_[1] == value_for_new_elements);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Assign_With_Count_Bigger_Than_Capacity_And_Bigger_Than_Size)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// value_for_new_elements - значение которое приписывается новым элементами
	const int value_for_new_elements = 777;

	// WHEN:
	//
	// Присваиваем вектору новое содержимое: четыре элемента, каждый из которых равен value_for_new_elements
	// Записываем новый размер вектора в vec_size, а новую вместимость в vec_capacity
	vec_.assign(4, value_for_new_elements);
	size_t vec_size = vec_.size(), vec_capacity = vec_.capacity();

	// THEN:
	//
	// Проверяем, что размер вектора стал равен 4, вместимость увеличилась, а четыре элемента равны  value_for_new_elements
	ASSERT_TRUE(vec_size == 4);
	ASSERT_TRUE(vec_capacity > init_capacity_);
	ASSERT_TRUE(vec_[0] == value_for_new_elements);
	ASSERT_TRUE(vec_[1] == value_for_new_elements);
	ASSERT_TRUE(vec_[2] == value_for_new_elements);
	ASSERT_TRUE(vec_[3] == value_for_new_elements);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve_with_less_capacity)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// new_less_capicity - новая вместимость вектора, которая меньше начальной (init_capacity_)
	const size_t new_less_capicity = 2;

	// WHEN:
	//
	// Устанавливаем вектор в состояние, в котором он способен хранить new_less_capicity элементов
	vec_.reserve(new_less_capicity);

	// THEN:
	//
	// Проверяем, что размер вектора и вместимость не изменились
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Reserve_with_bigger_capacity)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// new_less_capicity - новая вместимость вектора, которая меньше начальной (init_capacity_)
	const size_t new_bigger_capicity = 4;

	// WHEN:
	//
	// Устанавливаем вектор в состояние, в котором он способен хранить new_less_capicity элементов
	vec_.reserve(new_bigger_capicity);

	// THEN:
	//
	// Проверяем, что размер вектора не изменилась, а вместимость увеличилась
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() > init_capacity_);
}

TEST_F(Vector_Object_For_Testing_Single_Vec, Shrink_to_fit)
{
	// GIVEN:
	//
	// vec_ - вектор проинициализированный в классе Vector_Object_For_Testing_Single_Vec (vec_[0] = 10, vec_[1] = 20)
	// init_size_ = 2 - размер вектора vec_ (опеределено в классе Vector_Object_For_Testing_Single_Vec)
	// init_capacity_ - вместимость vec_ (= 3)
	// new_less_capicity - новая вместимость вектора, которая меньше начальной (init_capacity_)

	// WHEN:
	//
	// Сокращаем вместимость вектора до текущего размера
	vec_.shrink_to_fit();

	// THEN:
	//
	// Проверяем, что размер вектора не изменился, а вместимость стала равна размеру
	ASSERT_TRUE(vec_.size() == init_size_);
	ASSERT_TRUE(vec_.capacity() == init_size_);
}

//! Класс, который настраивает объект вектора, который используется в тестах оператора присваивания
class Vector_Objects_For_Cheking_Equality : public testing::Test
{
public:
	Vector_Objects_For_Cheking_Equality() :
		init_vec_(3), first_assigned_vec_(2), second_assigned_vec_(1) {
		init_vec_.push_back(val_1);
		init_vec_.push_back(val_2);
		init_vec_.push_back(val_3);
		second_assigned_vec_ = first_assigned_vec_ = init_vec_;
	}
protected:
	const int val_1 = 10, val_2 = 20, val_3 = 30;
	ava::Vector<int> init_vec_, first_assigned_vec_, second_assigned_vec_;
};

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Capacity_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - исходный вектор с параметрами: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - первый присвоеный вектор (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - второй присвоеный вектор (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// Записываем вместимости исходного вектора и двух присвоинных векторов в переменные
	// init_cap, first_assigned_cap, second_assigned_cap
	size_t init_cap = init_vec_.capacity(),
		first_assigned_cap = first_assigned_vec_.capacity(),
		second_assigned_cap = second_assigned_vec_.capacity();

	// THEN
	//
	// Проверяем, что вместимости двух присвоинных векторов равны вместимости исходного вектора
	ASSERT_TRUE(first_assigned_cap == init_cap);
	ASSERT_TRUE(second_assigned_cap == init_cap);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Size_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - исходный вектор с параметрами: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - первый присвоеный вектор (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - второй присвоеный вектор (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// Записываем размеры исходного вектора и двух присвоинных векторов в переменные
	// init_size, first_assigned_size, second_assigned_size
	size_t init_size = init_vec_.size(),
		first_assigned_size = first_assigned_vec_.size(),
		second_assigned_size = second_assigned_vec_.size();

	// THEN
	//
	// Проверяем, что размеры двух присвоинных векторов равны размеру исходного вектора
	ASSERT_TRUE(first_assigned_size == init_size);
	ASSERT_TRUE(second_assigned_size == init_size);
}

TEST_F(Vector_Objects_For_Cheking_Equality, Check_Elements_Equality)
{
	// GIVEN:
	// 
	// init_vec_ - исходный вектор с параметрами: size = 3, capacity = 3, init_vec_[0] = 10, init_vec_[1] = 20, init_vec_[2] = 30
	// first_assigned_vec_ - первый присвоеный вектор (first_assigned_vec_ = init_vec_)
	// secong_assigned_vec_ - второй присвоеный вектор (secong_assigned_vec_ = first_assigned_vec_ = init_vec_)

	// WHEN
	// 
	// Ничего не делаем: присвоение уже было в классе Vector_Objects_For_Cheking_Equality

	// THEN
	//
	// Проверяем, что элементы присвоинных массивов равны элементам исходного массива
	ASSERT_TRUE(first_assigned_vec_[0] == init_vec_[0]);
	ASSERT_TRUE(first_assigned_vec_[1] == init_vec_[1]);
	ASSERT_TRUE(first_assigned_vec_[2] == init_vec_[2]);
	ASSERT_TRUE(second_assigned_vec_[0] == init_vec_[0]);
	ASSERT_TRUE(second_assigned_vec_[1] == init_vec_[1]);
	ASSERT_TRUE(second_assigned_vec_[2] == init_vec_[2]);
}

TEST(Vector, Move_constructor)
{
	// GIVEN
	//
	// vec_size - размер вектора временного объекта, которым иницициализируется вектор vec
	// value - значения которыми инициализируется временный вектор
	std::size_t vec_size = 2;
	const int value = 777;

	// WHEN
	//
	// Создаём вектор с помощью конструктора перемещения
	ava::Vector<int> vec(ava::Vector<int>(vec_size, value));

	// THEN
	//
	// Проверяем, что временный вектор (который уже сдох) эквивалентен вектору vec
	// Проверка идёт по всем полям (размер, вместимость) и элементам
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Move_assignment)
{
	// GIVEN:
	// 
	// vec_size - размер вектора временного объекта, которым иницициализируется вектор vec
	// value - значения которыми инициализируется временный вектор
	// vec - вектор, у которого вызовится оператор присваивания - перемещения
	std::size_t vec_size = 2;
	const int value = 777;
	ava::Vector<int> vec;

	// WHEN:
	// 
	// Определяем вектор vec с помощью оператора присваивания-перемещения
	vec = ava::Vector<int>(vec_size, value);

	// THEN
	//
	// Проверяем, что временный объект (который уже сдох) эквивалентен вектору vec
	// Проверяются все поля (размер и вместимость)
	ASSERT_TRUE(vec.size() == vec_size);
	ASSERT_TRUE(vec.capacity() == vec_size);
	ASSERT_TRUE(vec[0] == value);
	ASSERT_TRUE(vec[1] == value);
}

TEST(Vector, Initializer_list)
{
	// GIVEN
	//
	// val_1, val_2 - значения которыми инициализируется вектор vi
	// vi вектор, который инициализируется с помощью листа инициализации
	const int val_1 = 1, val_2 = 3;
	ava::Vector<int> vi = { val_1, val_2 };

	// WHEN
	//
	// В переменные el_1, el_2 записываем первый и второй элемент вектора
	int el_1 = vi[0], el_2 = vi[1];

	// THEN
	//
	// Проверяем, что элементы совпадают с элементами листа инициализации
	ASSERT_TRUE(el_1 == val_1);
	ASSERT_TRUE(el_2 == val_2);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
	return 0;
}
