/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Sep 2017 12:36:13 PM PDT
 ************************************************************************/

#include<iostream>
using namespace std;


int generate_random_num()
{
	int i = 0;
	int ret = 200;
	
	while(i++ < 100) 
	{
		int random = rand() % 100;

		if(random < 5)
		    ret = 5;
		else if(random < 10)
		    ret = 4;
		else if(random < 25)
		    ret = 3;
		else if(random < 50)
		    ret = 2;
		else
		    ret = 1;

        cout << ret << endl;
	}

    return ret;
}


int main()
{
    generate_random_num();
}
