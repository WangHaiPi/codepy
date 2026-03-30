#include "codepy.h"
using namespace std;
using namespace codepy;

int main() {
	// ========== Basic Execution ==========
	cout << "=== 1. Basic Python Execution ===" << endl;
	py << "print('Hello World!')";
	py << "name = 'WangHaiPi'";
	py << "print(f'My name is {name}')";
	py.run();
	
	// ========== Single Line Execution ==========
	cout << "\n=== 2. Single Line Execution ===" << endl;
	py.exec("print('Hello World!')");
	
	// ========== Multi-line Code ==========
	cout << "\n=== 3. Multi-line Code ===" << endl;
	py << "for i in range(3):";
	py << "    print(f'The {i}th loop')";
	py << "print('end')";
	py.run();
	
	// ========== Package Management ==========
	cout << "\n=== 4. Package Management ===" << endl;
	py.pipun("requests");
	py.pip("requests");
	
	// ========== List Installed Packages ==========
	cout << "\n=== 5. List Packages ===" << endl;
	py.piplist();
	
	// ========== Check Python Installation ==========
	cout << "\n=== 6. Check Python ===" << endl;
	cout << "Python installed: " << (py.has_python() ? "Yes" : "No") << endl;
	
	// ========== Check Package Installation ==========
	cout << "\n=== 7. Check Package ===" << endl;
	cout << "requests installed: " << (py.has_package("requests") ? "Yes" : "No") << endl;
	
	return 0;
}
