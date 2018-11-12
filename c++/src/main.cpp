#include <iostream>
#include "test_module.h"
#include "unit_4_3.h"
#include "unit_5_1.h"
#include "unit_5_2.h"
#include "unit_5_3.h"

int main(int argc, char** argv) {
	
	HelloWorld::hello_world();
	
	unit_5_1::test();
	
	unit_5_2::test();
	
	unit_5_3::test();
	
	system("PAUSE");
	return 0;
}
