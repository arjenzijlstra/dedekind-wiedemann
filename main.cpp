
#include "main.ih"


/*
template <typename T, typename Alloc>
std::ostream &operator<<(std::ostream &out, std::set<T, Alloc> const &rhs)
{
	out << '{';
	for (typename std::set<T>::iterator iter = rhs.begin();
			iter != rhs.end();
				++iter)
	{
		out << ((iter != rhs.begin()) ? ", " : "") << *iter;
	}
	out << '}';
	return out;
}
*/

template <typename T, size_t size>
std::ostream &operator<<(std::ostream &out, std::array<T, size> const &rhs)
{
	out << '{';
	for (auto iter = rhs.begin();
			iter != rhs.end();
				++iter)
	{
		out << ((iter != rhs.begin()) ? ", " : "") << *iter;
	}
	out << '}';
	return out;
}

bool vectorLess(set<size_t> const &lhs,
					 set<size_t> const &rhs)
{
	if (lhs.size() == rhs.size())
	{
		for (auto iter = lhs.begin(), iter2 = rhs.begin(); iter != lhs.end();
				++iter, ++iter2)
		{
			if (*iter != *iter2)
			{
				return *iter < *iter2;
			}
		}
	}

	return lhs.size() < rhs.size();
}

void powersetRec(std::vector<std::set<size_t>> &result,
					  std::set<size_t> current, size_t const n)
{
	if (n == 0)
	{
		result.push_back(current);
		return;
	}

	size_t newN(n - 1);
	powersetRec(result, current, newN);
	current.insert(newN);
	powersetRec(result, current, newN);
}

template<size_t size>
std::array<std::set<size_t>, size> powerset(size_t const n)
{
	std::vector<std::set<size_t>> resultVector;
	std::set<size_t> current;
	powersetRec(resultVector, current, n);
	sort(resultVector.begin(), resultVector.end(), vectorLess);

	std::array<std::set<size_t>, size> result;
	copy(resultVector.begin(), resultVector.end(), result.begin());

	return result;
}

template<size_t size>
std::set<size_t> permute(std::array<size_t, size> permutation, std::set<size_t> elem)
{
	std::set<size_t> result;
	for (auto iter = elem.begin(); iter != elem.end(); ++iter)
	{
		result.insert(permutation[*iter]);
	}
	return result;
}

template<size_t size, size_t size2>
std::array<size_t, size2> mbfPermutation(std::array<size_t, size> permutation,
		std::array<std::set<size_t>, size2> ps)
{
	std::array<size_t, size2> result;
	size_t idx = 0;
	for (auto iter = ps.begin(); iter != ps.end(); ++iter)
	{
		std::set<size_t> tmp = permute(permutation, *iter);
		result[idx++] = find(ps.begin(), ps.end(), tmp) - ps.begin();
	}
	return result;
}

int main(int argc, char **argv)
{

	// set<bitset<1>, BitSetLess> test({bitset<1>(1), bitset<1>(0)});
	// set<bitset<2>, BitSetLess> test2;

	// __gnu_parallel::for_each(test.begin(), test.end(),// std::inserter(test2, test2.begin()),
	//     [&](bitset<1> const &arg)
	//     {
	//         __gnu_parallel::for_each(test.begin(), test.end(),
	//         [&](bitset<1> const &arg2)
	//         {
	//             if (arg <= arg2)
	//             {
	//                 test2.insert(concatenate(arg, arg2));
	//             }
	//         });
	//     });
	// cerr << test2 << '\n';

	size_t const n = 4;
	size_t const p = pow(2, n);
	array<size_t, n> permutation;
	vector<array<size_t, n>> permutations;

	for (size_t idx = 0; idx != n; ++idx)
	{
		permutation[idx] = idx;
	}

	std::array<std::set<size_t>, p> powerSet = powerset<p>(n);

	std::set<size_t> elem({0, 2});

	cout << powerSet << '\n';

	do
	{
		permutations.push_back(permutation);
		std::cout << permutation << " -> "
					 << mbfPermutation(permutation, powerSet) << '\n';
		//cout << permutation << ": " << elem << " -> " << permute(permutation, elem) << '\n';
	}
	while (std::next_permutation(permutation.begin(), permutation.end()));



	if (argc == 2 && argv[1][0] == 'b')
	{
		// size_t const sizes[8] = {1, 2, 4, 8, 16, 32, 64, 128};
		// set<bitset<1>, BitSetLess> D0({bitset<1>(0), bitset<1>(1)});
		// set<bitset<32>, BitSetLess> result;
		// for (size_t iter = 0; iter != n; ++iter)
		// {
		//     set<bitset<sizes[iter]>, BitSetLess> tmp;
		//     if (iter == 0)
		//     {
		//         tmp = generate(D0);
		//     }
		//     else
		//     {
		//         tmp = generateD(result);
		//     }
		//     result = tmp;
		// }

		// struct bitsetWrapper {
		//     bitset<1> *bit1;
		//     bitset<2> *bit2;

		//     set(int n) {
		//         switch (n) {
		//             case 1: return bit1;
		//         }
		//     }
		// };

		DedekindBit dedekind;
		dedekind.generateMonotoneSubsets(0);
	}
	else
	{
		size_t n = 0;
		if (argc == 2)
		{
			stringstream ss(argv[1]);
			ss >> n;
			// cout << n << '\n';
		}
		DedekindInt dedekind;
		dedekind.generateMonotoneSubsets(n);

		cout << dedekind.base().size() << '\n';
		cout << dedekind.base() << '\n';


		// set<set<set<size_t>, SetLess>, SetLess> result({{ }, {{ }}});

		// size_t k = 0;
		// // cout << "Computing Dedekind number: " << n << '\n';
		// for (size_t iter = 0; iter != n; ++iter)
		// {
		//     result = generate(result, k++);
		//     size_t dn = result.size();
		//     cout << "Number of elements: " << dn << '\n';
		//     if (dn < 100)
		//     {
		//         cout << result << '\n';
		//     }
		// }
		// cout << result.size() << '\n';
	}
}
