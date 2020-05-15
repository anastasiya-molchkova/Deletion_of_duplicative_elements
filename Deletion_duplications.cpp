/* В заданном пользователем целочисленном массиве удалите элементы, которые встречаются более двух раз. */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>  // для превращения строки в число
#include <cassert>

using std::cout; using std::cin; using std::endl;

// получает от пользователя последовательность чисел и, возможно, не только числа в виде строки
const std::string get_data_from_user()
{
	cout << "Введите массив целых чисел через пробел, прочие знаки будут проигнорированы.\n"
		<< "Для окончания ввода нажмите enter: ";
	std::string input;
	std::getline(cin, input);
	return input;
}

// функция проверки, что можно превратить строку в число (выдаёт false, если не получилось)
inline bool is_number(const std::string& str, int& number)
{
	std::istringstream istream(str);
	return (istream >> number) ? true : false;
}

// создаёт целочисленный вектор из строки, введённой пользователем
std::vector<int> create_array_from_string(const std::string& users_input)
{
	std::vector<int> array{};
	std::string future_number{};                // будущее число в виде строки
	// будем собирать каждое число по символам-цифрам, каждый пробел добавляем число в массив и начинаем заново
	for (unsigned int i = 0; i < users_input.length(); i++)
	{
		// если после пробела знак минус или просто число
		if (((future_number == "") && (users_input[i] == '-')) || (isdigit(users_input[i])))
			future_number += users_input[i];
		// если пробел или конец строки
		if ((users_input[i] == ' ') || (i == (users_input.length() - 1)))
		{
			if (future_number != "")
			{
				int one_more_number{ 0 };
				if (is_number(future_number, one_more_number))
					array.push_back(one_more_number);
			}
			future_number = "";
		}
	}
	return array;
}

// удаляет из массива числа, встречающиеся больше, чем 2 раза
void delete_duplications(std::vector<int>& array)
{
	unsigned length = array.size();
	assert((length > 2) && "В массиве недостаточно данных для удаления");

	// для каждого элемента будем считать количество дублей (0 - такой элемент в массиве 1)
	std::vector<uint8_t> number_of_duplications{};
	number_of_duplications.resize(length);

	unsigned current_index{ 0 };                              // индекс рассматриваемого элемента, для которого будем искать дубли
	while (current_index < (length -1))
	{
		if (number_of_duplications[current_index] > 0)        // если этот элемент уже считали как дубль, переходим к следующему элементу
		{
			++current_index;
			continue;
		}

		// иначе идём по остатку массива в поисках дублей
		for (auto next_index = current_index + 1; next_index < length; ++next_index)
			if ((number_of_duplications[next_index] == 0) && (array[current_index] == array[next_index]))
			{
				++number_of_duplications[current_index];      // таким образом отмечаем количество дублей для рассматриваемого элемента
				if (number_of_duplications[current_index] > 1)
					break;                                    // не стоит доходить до конца массива, если уже нашли два
			}
		if (number_of_duplications[current_index] > 1)        // нашли как минимум два дубля для рассматриваемого элемента
		{
			// тогда запоминаем элемент и удаляем сам элемент и количество его дублей:
			auto element_for_deletion{ array[current_index] };
			array.erase(array.begin() + current_index);
			number_of_duplications.erase(number_of_duplications.begin() + current_index);
			--length;                                         // при удалении элемента длина массива уменьшается на 1
			// и удаляем его дубли в хвосте, рассматривая элементы, начиная с текущего индекса, т.к. после удаления там уже следующий элемент:
			unsigned next_index{ current_index };
			while (next_index < length)
			{ 
				if (array[next_index] == element_for_deletion)
				{
					array.erase(array.begin() + next_index);
					number_of_duplications.erase(number_of_duplications.begin() + next_index);
					--length;
				}
				else  // переходим к следующему элементу
					++next_index;
			}
		}

		else //  у рассмотренного элемента один дубль или нет дублей, тогда переходим к следующему
			++current_index;
	}
}

void print_result(std::vector<int>& array)
{
	for (const auto& number : array)
		cout << number << " ";
	cout << endl;
}

int main()
{
    setlocale(LC_CTYPE, "rus");

    cout << "Программа удаляет числа, встречающиеся больше двух раз.\n";
	std::vector<int> array = create_array_from_string(get_data_from_user());
	cout << "Получен массив: ";
	print_result(array);
	delete_duplications(array);
	cout << "Результат обработки: ";
	print_result(array);

	return 0;
}