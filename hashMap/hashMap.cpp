#include "hashMap.h"

#include <string>


unsigned int hash(const std::string &str){
	unsigned int idx = 5381;
	for(int i = 0 ; i < str.length() ; ++i)
		idx = ((idx << 5) + idx) + str[i];
	return idx;
}

/*
// efficiency = 0.644606
unsigned int hashInt(int key){
	key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key;
}
*/

// efficiency = 0.64455
uint64_t hashInt(uint64_t x) {
    x = (x ^ (x >> 31) ^ (x >> 62)) * UINT64_C(0x319642b2d24d8ec3);
    x = (x ^ (x >> 27) ^ (x >> 54)) * UINT64_C(0x96de1b173f119089);
    x = x ^ (x >> 30) ^ (x >> 60);
    return x;
}

void hashMapCSTRtest(){
	hashMap<int, int> hm(hashInt);
	hashMap<std::string, std::string> hmstr(hash);
}

void hashMapADDtest(){
	// HashMap for integers test
	hashMap<int, int> hm(hashInt);
	hm[5] = 12;
	std::cout << hm[5] << std::endl;
	for(int i = 0 ; i < 10 ; ++i)
		hm[i] = i;

	for(int i = 0 ; i < 10 ; ++i)
		std::cout << hm[i] << " ";
	std::cout << std::endl;

	// HashMap for strings test
	hashMap<std::string, std::string> hmstr(hash);
	hmstr["MyHash"] = "Working";
	std::cout << hmstr["MyHash"] << std::endl;
	hmstr["MyHash"] = "Hurray";
	std::cout << hmstr["MyHash"] << std::endl;
	std::cout << "efficiency = " << hm.efficiency() << std::endl;
}

void hashMapFINDandREMOVEtest(){
	// HashMap for integers test
	hashMap<int, int> hm(hashInt);
	hm[5] = 12;
	std::cout << hm[5] << std::endl;
	for(int i = 0 ; i < 10 ; ++i)
		hm[i] = i;

	for(int i = 0 ; i < 10 ; ++i)
		std::cout << hm[i] << " ";
	std::cout << std::endl;

	hm.remove(6);
	if(!hm.find(6))
		std::cout << "Remove method working properly!\n";

	// HashMap for strings test
	hashMap<std::string, std::string> hmstr(hash);
	hmstr["MyHash"] = "Working";
	std::cout << hmstr["MyHash"] << std::endl;
	hmstr["MyHash"] = "Hurray";
	std::cout << hmstr["MyHash"] << std::endl;

	hmstr.remove("MyHash");
	if(!hmstr.find("MyHash"))
		std::cout << "Remove method working properly!\n";

	if(!hmstr.find("TestString"))
		std::cout << "Remove method working properly!\n";
	std::cout << "efficiency = " << hm.efficiency() << std::endl;
	std::cout << "efficiency = " << hmstr.efficiency() << std::endl;
}

void hashMapREHASHtest(){
	// HashMap for integers test
	hashMap<int, int> hm(hashInt);
	hm[5] = 12;
	std::cout << hm[5] << std::endl;
	for(int i = 0 ; i < 10 ; ++i)
		hm[i] = i;

	for(int i = 0 ; i < 10 ; ++i)
		std::cout << hm[i] << " ";
	std::cout << std::endl;
	std::cout << "size = " << hm.getSize() << " capacity = " << hm.getCap() << std::endl;
	std::cout << "efficiency = " << hm.efficiency() << std::endl;
	for(int i = 0 ; i < 6 ; ++i)
		hm.remove(i);
	std::cout << "size = " << hm.getSize() << " capacity = " << hm.getCap() << std::endl;
	std::cout << "efficiency = " << hm.efficiency() << std::endl;
}

#include <algorithm>

void hashMapBIGDATAtest(){
	hashMap<int, int> hm(hashInt);
	for(register int i = 0 ; i < 1e6 ; ++i)
		hm[i] = i;
	std::cout << "BIG DATA : \n";
	std::cout << "size = " << hm.getSize() << std::endl;
	std::cout << "capacity = " << hm.getCap() << std::endl;
	std::cout << "efficiency = " << hm.efficiency() << std::endl;
	std::cout << "biggest bucket size = " << hm.getBiggestBucket() << std::endl;
	std::cout << "first 50 largest buckest's sizes = ";
	std::vector<size_t> sizes = hm.bucketsSizes();
	std::sort(sizes.begin(), sizes.end(), std::greater<int>());
	for(int i = 0 ; i < 50 ; ++i)
		std::cout << sizes[i] << " ";
	std::cout << std::endl;
}

void hashMapSTRINGMATCHINGtest(){
	hashMap<std::string, unsigned int> hmstr(hash);

	std::vector < std::string > text1 = {"this", "is", "example", "for", "string", "matching"};
	std::vector < std::string > text2 = {"text", "string", "string"};

	for(auto it : text2){
		hmstr[it] += 1;
	}
	for(auto it : text1)
		std::cout << it << " = " << hmstr[it] << std::endl;
}


int main(){
	//hashMapCSTRtest();
	//hashMapADDtest();
	///hashMapFINDandREMOVEtest();
	//hashMapREHASHtest();
	//hashMapBIGDATAtest();
	//hashMapSTRINGMATCHINGtest();

	return 0;
}