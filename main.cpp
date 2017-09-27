/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Sep 2017 12:36:13 PM PDT
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <mutex>
#include <boost/circular_buffer.hpp>




using namespace std;


class RandomCountGenerator
{
    public:
        RandomCountGenerator();
        virtual ~RandomCountGenerator();
        
        int generate_random_num();
        double get_frequency(int num); 
        void write_num_to_file();
        
    private:
        boost::circular_buffer<int> m_last_num_queue;
};

RandomCountGenerator::RandomCountGenerator(): m_last_num_queue(100)
{
    
}


RandomCountGenerator::~RandomCountGenerator()
{
    
}

int RandomCountGenerator::generate_random_num()
{
	int ret;
	
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
	
	m_last_num_queue.push_back(ret);
	
	return ret;
}


double RandomCountGenerator::get_frequency(int num)
{
    double ret = 0;
    
    switch(num)
    {
        case 1: 
            ret = 0.5;
            break;
        case 2: 
            ret = 0.25;
            break;
        case 3: 
            ret = 0.15;
            break;
        case 4: 
        case 5:
            ret = 0.05;
            break;
        default:
            cout << "wrong input number!" << endl;
    }
    
    return ret;
}

void RandomCountGenerator::write_num_to_file()
{
    string num_time_str = "\t*** " + std::to_string(m_last_num_queue[m_last_num_queue.size()-1]);
    
    std::time_t timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::ofstream out("output.txt");
    num_time_str = num_time_str + ": @ " + std::ctime(&timestamp_);
    out << num_time_str;
    out.close();
}

int main()
{
    RandomCountGenerator obj;
    obj.generate_random_num();
}
