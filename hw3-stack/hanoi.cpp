#include <stack>
#include <iostream>

using std::stack;

void printStack(stack<int> s, stack<int> t, stack<int> d)
{
	size_t size = std::max(s.size(), std::max(t.size(), d.size()));
	for(int i = 0 ; i < size ; ++i)
	{
		if(!s.empty()){
			std::cout << "  " << s.top() << "\t";
			s.pop();
		}
		else{
			std::cout << " \t";
		}
		if(!t.empty()){
			std::cout << "\t" << t.top() << "\t";
			t.pop();
		}
		else{
			std::cout << " \t";
		}
		if(!d.empty()){
			std::cout << "   " << d.top() << "\t";
			d.pop();
		}
		else{
			std::cout << " \t";
		}
		std::cout << std::endl;
	}
	std::cout << "source " << "\ttemp\t" << " dest \n";
}

class HanoyState
{
private:
	stack<int>* source;
	stack<int>* dest;
	stack<int>* temp;
	int k;

public:
	HanoyState( stack<int>& source_arg,  stack<int>& dest_arg,  stack<int>& temp_arg, int k_arg) : source(&source_arg),
																											   	   dest(&dest_arg),
																											       temp(&temp_arg),
																											   	   k(k_arg) {}

	stack<int>& getSource()
	{
		return *source;
	}

	stack<int>& getDest()
	{
		return *dest;
	}

	stack<int>& getTemp()
	{
		return *temp;
	}

	int& getK()
	{
		return k;
	}

	void makeStep()
	{
		dest->push(source->top());
		source->pop();

	}
};

void move(stack<int>& source, stack<int>& dest, stack<int>& temp, int k)
{
	if(k == 1)
	{
		std::cout << std::endl;
		printStack(source,temp, dest);
		std::cout << std::endl;
		dest.push(source.top());
		source.pop();
		return;
	}
	else{
		move(source, temp, dest, k - 1);
		move(source, dest, temp, 1);
		move(temp,dest, source, k - 1);
	} 
}

void moveIter(stack<int>& source, stack<int>& dest, stack<int>& temp, int k)
{
	stack<HanoyState> ss;
	ss.push(HanoyState(source, dest, temp, k));
	while(!ss.empty())
	{
		HanoyState state = ss.top();
		ss.pop();
		if(state.getK() == 1)
		{
			state.makeStep();
		}
		else
		{
			ss.push(HanoyState(state.getTemp(), state.getDest(), state.getSource(), k - 1));
			ss.push(HanoyState(state.getSource(), state.getDest(), state.getTemp(), 1));
			ss.push(HanoyState(state.getSource(), state.getTemp(), state.getDest(), k - 1));
		}
	}
}

int main()
{
	stack<int> source;
	stack<int> temp; 
	stack<int> dest;
	for(int i = 2 ; i >= 1 ; --i)
		source.push(i);
		std::cout << std::endl;
	printStack(source,temp, dest);
	std::cout << std::endl;
	move(source,dest,temp, source.size());
	std::cout << std::endl;
	printStack(source,temp, dest);
	std::cout << std::endl;

	return 0;
}
