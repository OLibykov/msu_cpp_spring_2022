#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>

std::string encode(std::vector <int32_t> arr){
	std::string tmp = "";
	std::sort(arr.begin(), arr.end());
	auto tmp_it = arr.begin();
	auto tmp2_it = arr.begin();
	for (auto it = arr.begin(); it != arr.end();){
		tmp2_it = it;
		it++;
		if (it == arr.end()){
			tmp += std::to_string(*tmp_it); 
			if (*tmp_it == *tmp2_it){
				break;
			}
			tmp += '-';
			tmp += std::to_string(*tmp2_it); 
			break;
		}
		if ((*it) - (*tmp2_it) != 1 && (*it) - (*tmp2_it) != 0){
			tmp += std::to_string(*tmp_it);
			if (tmp_it != tmp2_it){
				tmp += "-";
				tmp += std::to_string(*tmp2_it); 
				tmp += " ";
			}
			else{
				tmp += " ";
			}
			tmp_it = it;
		}
	}
	return tmp;
}

int main()
{
	std::vector<int32_t> arr = {1, 4, 2, 3, 9, 8, 11, 0};
	std::vector<int32_t> arr2 = {1, 4, 3, 2};
	std::vector<int32_t> arr3 = {1, 4};

    std::cout << encode(arr) << std::endl;
	std::cout << encode(arr2) << std::endl;
	std::cout << encode(arr3) << std::endl;
    return 0;
}
