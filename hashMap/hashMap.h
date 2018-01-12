#pragma once

#include <vector>
#include <functional>

#include <iostream>

template <class KeyType, class ValueType>
using pair = std::pair<KeyType, ValueType>;

#define initialHashMapSize 8

#define increaseFactor 10
#define decreaseFactor 2

template <class KeyType, class ValueType>
using container = std::vector< std::vector< pair<KeyType, ValueType> > >;

template <class KeyType>
using hashFunction = std::function<unsigned int(const KeyType&)>;

template <class KeyType, class ValueType>
using bucketsIterator = typename std::vector< std::vector < pair <KeyType, ValueType> > >::iterator;

template <class KeyType, class ValueType>
using bucketIterator = typename std::vector< pair <KeyType, ValueType> >::iterator;

template <class KeyType, class ValueType>
class hashMap{
private:
	container<KeyType, ValueType> buckets;
	hashFunction<KeyType> hf;
	size_t capacity, size;

	size_t biggestBucket;

	void expand(){
		container<KeyType, ValueType> newBuckets;
		newBuckets.assign(capacity * increaseFactor, std::vector< pair<KeyType, ValueType > >());
		biggestBucket = 0;
		size = 0;
		capacity *= increaseFactor;
		container<KeyType, ValueType> oldBuckets = buckets;
		buckets = newBuckets;
		Rehash(oldBuckets);
	}

	void shrink(){
		if(capacity < 2)
			return;
		container<KeyType, ValueType> newBuckets;
		newBuckets.assign(capacity / decreaseFactor, std::vector< pair<KeyType, ValueType > >());
		biggestBucket = 0;
		size = 0;
		capacity /= decreaseFactor;
		container<KeyType, ValueType> oldBuckets = buckets;
		buckets = newBuckets;
		Rehash(oldBuckets);
	}

	void Rehash(container<KeyType, ValueType> &oldBuckets){
		for(bucketsIterator<KeyType, ValueType> bucket = oldBuckets.begin() ; bucket != oldBuckets.end() ; ++bucket){
			for(bucketIterator<KeyType, ValueType> element = bucket->begin() ; element != bucket->end() ; ++element){
				(*this)[element->first] = element->second;
			}
		}
	}

public:
	hashMap(const hashFunction<KeyType> hf_) : hf(hf_), size(0), biggestBucket(0) {
		buckets.assign(initialHashMapSize, std::vector< pair<KeyType, ValueType > >());
		capacity = initialHashMapSize;
	}

	ValueType& operator[](const KeyType &key){
		if (size >= capacity) 
			expand();
		size_t containerIdx = hf(key) % capacity;
		for(auto& it : buckets[containerIdx])
			if(it.first == key)
				return it.second;
		buckets[containerIdx].push_back(pair<KeyType, ValueType>(key, ValueType()));
		++size;
		biggestBucket = std::max (biggestBucket, buckets[containerIdx].size());

		return buckets[containerIdx][buckets[containerIdx].size() - 1].second;
	}

	bool find(const KeyType &key) const{
		size_t containerIdx = hf(key) % capacity;
		for(auto it : buckets[containerIdx])
			if(it.first == key)
				return true;
		return false;
	}

	void remove(const KeyType &key){
		if (size <= (capacity / 2))
			shrink();
		size_t containerIdx = hf(key) % capacity;
		for(bucketIterator<KeyType, ValueType> it = buckets[containerIdx].begin() ; it != buckets[containerIdx].end() ; ++it){
			if(it->first == key){
				buckets[containerIdx].erase(it);
				--size;
				return;
			}
		}
	}

	size_t inline getSize() const{
		return size;
	}

	size_t inline getCap() const{
		return capacity;
	}

	size_t inline getBiggestBucket() const{
		return biggestBucket;
	}

	std::vector<size_t> bucketsSizes(){
		std::vector<size_t> res;
		for(bucketsIterator<KeyType, ValueType> bucket = buckets.begin() ; bucket != buckets.end() ; ++bucket){
			res.push_back(bucket->size());
		}
		return res;
	}

	double efficiency(){
		unsigned int colliding = 0;
		for(bucketsIterator<KeyType, ValueType> bucket = buckets.begin() ; bucket != buckets.end() ; ++bucket){
			unsigned int tmpsize = bucket->size();
			if(tmpsize >= 1)
				colliding += tmpsize - 1;
		}
		return (double)(size - colliding) / (double)size;
	}
};
