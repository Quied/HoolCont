#include <iostream>
#include <concepts>
#include <coroutine>
#include <vector>
#include <deque>


template <typename T>
concept EightByte = sizeof(T) == 8;

template <EightByte T, typename D> class iterator {
public:
	typedef typename std::vector<std::pair<T, D>> iter;

	iterator(T* p_data) : _mData(p_data) {
		_mIt = _mData->_Datas.begin();
	}

	iter Curr() {
		return _mIt;
	}

	void First() {
		_mIt = _mData->_Datas.begin();
	}

	void Next() { 
		_mIt++; 
	}

	bool End() {
		return (_mIt == _mData->_Datas.end());
	}

	
	iterator& operator++() {
		return(this->Next());
	}
	
private:
	T _mData;
	iter _mIt;

};


template <EightByte T, typename D> class Hool {

	friend class iterator<T, Hool>;

	std::vector<std::pair<T, D>> _Datas;

public:

	void push(T &&a, D &&b)  {
		_Datas.emplace_back(a, b);
	}

	int size() {
		return _Datas.size();
	}

	iterator <T, Hool>* Iterator() {
		return new iterator<T, Hool>(this);
	}

};

int main() {

	Hool<double, int> hl;
	hl.push(777, 4.16);

	std::vector<void*> Vec;
	Vec.push_back(&hl);


	std::cout << hl.size() << std::endl;
	std::cout << static_cast<Hool<double, int>*>(Vec[0])->size() << std::endl;


	iterator<double, Hool<double, int>>* it = hl.Iterator();

	//for (it->First(); it->End(); it->Next()) {
	//	std::cout << *it->Curr() << std::endl;
	// }

}