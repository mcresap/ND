#include <iostream>

using namespace std;

int add(int a, int b); //function takes 2 integers and returns an integer
void greetings(void);

int main() {
	int a, b, c;
	greetings();
	a=5;
	b=9;
	c=add(a,b);

	cout << "the sum is: " << c << endl;
	
	int x=4, y=7, z;
	z=add(x, y);
	cout << "the other sum is: " << z << endl;


return 0;
}
int add(int a, int b) {
	int c;
	c=a+b;

return c;
}

void greetings(void)
{
	cout << "hello all!" << endl;
}
