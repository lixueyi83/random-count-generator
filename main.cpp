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
#include <thread>
#include <mutex>
#include <boost/circular_buffer.hpp>


typedef struct
{
    int count;
    std::string timestamp;
}COUNT_TIME_T;


using namespace std;


class RandomCountGenerator
{
    public:
        RandomCountGenerator();
        virtual ~RandomCountGenerator();
        
        void generate_count_loop();
        void write_count_loop();
        
        double get_frequency(int num); 
        
    private:
        std::thread generator_th;   
        std::thread writer_th;
        std::mutex m_queue_mutex;
        boost::circular_buffer<string> m_count_queue;
        std::ofstream output_tream;
};

RandomCountGenerator::RandomCountGenerator(): 
                                          m_count_queue(100)
{
    generator_th = std::thread(&RandomCountGenerator::generate_count_loop, this);
    writer_th = std::thread(&RandomCountGenerator::write_count_loop, this);
}


RandomCountGenerator::~RandomCountGenerator()
{
    /*free allocated memoroes from heap if allocated previously*/
    generator_th.join();
    writer_th.join();
}

void RandomCountGenerator::generate_count_loop()
{
	int count;
	
	while(true)
	{
	    string count_time_str;
	    std::time_t timestamp_;
	    
	    int random = rand() % 100;
	
	    if(random < 5)
	        count = 5;
	    else if(random < 10)
	        count = 4;
	    else if(random < 25)
	        count = 3;
	    else if(random < 50)
	        count = 2;
	    else
	        count = 1;
	        
	    timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	    count_time_str = std::to_string(count) + ": " + std::ctime(&timestamp_);
	
	    {
	        std::unique_lock<std::mutex> lk(m_queue_mutex);
	        m_count_queue.push_back(count_time_str);
	    }

	    cout << "generate_count_loop: " << count_time_str << endl;
	    sleep(1);
	}
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

void RandomCountGenerator::write_count_loop()
{   
    while(true)
    {
        string count_time_str;
        
        {
            std::unique_lock<std::mutex> lk(m_queue_mutex);
            if(0 == m_count_queue.size()) 
                continue;
            count_time_str = m_count_queue[m_count_queue.size()-1];
        }
               
        
        std::ofstream outfile;
        outfile.open("count-timestamp.txt", std::ios_base::app);
        outfile << count_time_str; 
        
        cout << "write_count_loop: " << count_time_str << endl;
        sleep(1);
    }
}


int main()
{
    RandomCountGenerator obj;
}
