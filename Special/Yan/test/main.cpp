#include <list>
#include <iostream>

std::list<int> l;
int num = 0;

//Function to display list of factors
void print(std::list<int> l){
    for (auto const& i: l) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

void findCombinations(int n, int product){
    //Base condition
    if(product == num){
        print(l);
        return;
    }

    for(int x=n; x<(num/2)+1; x++){
        //If product exceeds num -> return to last recursive call
        if(product*x > num)
            return;

        //Add number to product i.e. multiply
        product = product * x;
        l.push_back(x);

        //Recursive call with same number
        findCombinations(x, product);

        //Backtrack
        l.pop_back();
        product = product/x;
    }
}

int main() {
    std::cout << "Enter number: ";
    std::cin >> num;
    findCombinations(2,1);
    return 0;
}
