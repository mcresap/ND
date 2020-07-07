#include <iostream>
using namespace std;

int main ()
{

int t;
int ep;
int fg;
int s;
int p;
	cout << "How many touchdowns? ";
	cin >> t;
	cout << "How many extra points? ";
	cin >> ep;
	cout << "How many field goals? ";
	cin >> fg;
	cout << "How many safeties? ";
	cin >> s;

	p = t*6 + ep + fg*3 + s*2;

	cout << "The Irish scored " << p << " points total." << endl;

return 0;
}
