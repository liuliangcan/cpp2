/* 
 * File:   main.cpp
 * Author: LIU
 *
 * Created on 2016年1月11日, 下午3:49
 */

#include <cstdlib>
#include <stdio.h>
#include <tr1/unordered_set>
#include <fstream>
#include <string>
#include <string.h>
#include <limits.h>
#include <fstream>
#include <iostream>
using namespace std;

#define LOG printf
/*
 * 
 */

tr1::unordered_set<string> done_set;
tr1::unordered_set<string> true_done_set;
tr1::unordered_set<string> new_set;
char done_list[PATH_MAX]="";
char true_new_list[PATH_MAX]="";
char new_list[PATH_MAX]="";


void readonefile(char* file, tr1::unordered_set<string>& set)
{
    set.clear();
    ifstream infile(file, ios::in);
     if(!infile.is_open())
    {
        LOG("打开文件失败%s\n",file);
        return ;
    }
    char line[1028];
    while(!infile.eof())
    {
        infile.getline(line, 1024);
        if(line[0]!=0)
            set.insert(line);
    }
    if(infile.is_open())
    {
        infile.close();
    }
    printf("read from %s:%d\n",file,set.size());
}
void readfiles()
{
    readonefile(done_list, done_set);
    readonefile(new_list,new_set);
}
void choose()
{
    true_done_set.clear();
    tr1::unordered_set<string>::iterator it_set = done_set.begin();
    tr1::unordered_set<string>::iterator it_set_end = done_set.end();
    tr1::unordered_set<string>::iterator it_set_find;
    for(;it_set!=it_set_end;++it_set)
    {
        it_set_find = new_set.find(*it_set);
        if(it_set_find != new_set.end())
        {
            new_set.erase(it_set_find);
            true_done_set.insert(*it_set);
        }
    }
}
void writeonefile(char* file, tr1::unordered_set<string>& set)
{
    if(set.size()>0)
    {
        ofstream outfile(file, ios::out);
        if(!outfile.is_open())
       {
           LOG("打开文件失败%s\n",file);
           return ;
       }
       tr1::unordered_set<string>::iterator it_set = set.begin();
       tr1::unordered_set<string>::iterator it_set_end = set.end();
       for(;it_set != it_set_end;++it_set)
       {
           outfile<<*it_set<<endl;
       }
       if(outfile.is_open())
       {
           outfile.close();
       }
   }
    printf("write to %s:%d\n",file,set.size());
}
void writefiles()
{
    writeonefile(done_list,true_done_set);
    writeonefile(true_new_list,new_set);     
}
void f_main()
{
    //读列表文件
    readfiles();
    //筛选
    choose();
    //写文件
    writefiles();
    
}
#define clock() time(0)
void test_write()
{	
	const int TEST_SIZE = 1000000 ;
	const char* c_plus_write_file = "c_plus_write_file.txt";
	const char* c_write_file = "c_write_file.txt";
	
		char tmp[80]="1253850wyherohnds.cmnfi[e'fqpwr[]z.}depekvmeiqj2940-=+ienvnjaq`di1";
	cout<<"Test size :" << TEST_SIZE <<endl;
	//c++ style writing file
	ofstream of(c_plus_write_file);
	
	time_t start, end;
	start =  clock();
	for(int i=0; i < TEST_SIZE; ++i)
	{
		of << tmp <<"\n";
                
	}
	end = clock();
	of.close();
	cout<<"C++ style: "<<end - start <<" ms"<<endl;
	//c style writing file
	FILE* fp = fopen(c_write_file, "w");
	start =  clock();
	for(int i=0; i < TEST_SIZE; ++i)
	{
            fprintf(fp, "%s\n", tmp);
		//fwrite( tmp, 1, 1, fp);
            
	}
	end = clock();
	fclose(fp);
	cout<<"C style: "<<end - start <<" ms"<<endl;
	cin.get();
}

int main(int argc, char** argv)
{
    test_write();
//    tr1::unordered_set<string> set1;
//     if(argc > 3)
//    {
//        strcpy(done_list, argv[1]);
//        strcpy(true_new_list, argv[2]);
//        strcpy(new_list, argv[3]);
//    }
//     else
//     {
//         printf("error param\n");
//         return -1;
//     }
//    
//    f_main();
//    printf("done\n");
    return 0;
}

