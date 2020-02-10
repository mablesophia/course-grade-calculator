//
//  main.cpp
//  Letter Never Sent
//
//  Created by Sophia Lee on 2/7/20.
//  Copyright © 2020 Sophia Lee. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

/* **********************************************************************************************
   read_input: function that to read text files
               returns vector<string> input_array
* *********************************************************************************************** */
vector<string> read_input(){
    //declare variables
    string line;                     //each line in input file
    vector<string> input_array(50);  //input array from input file
    int i=0;                         //loop count

    //open input file
    ifstream input_file ("input.txt");

    //read input file
    if(input_file.is_open()){
        while (! input_file.eof()){
            getline (input_file, line);          //get one line from file
            input_array[i]=line;                 //put each line into the input_array
            i++;
        }
        input_file.close();
    }
    else cout << "unable to open the file" << endl;  //error handling
    
    return input_array;
}

/* **********************************************************************************************
  parse_possible_points: function that parse possible points from graded artifacts
                         returns vector<int> pp_array
* *********************************************************************************************** */
vector<int> parse_possible_points(int input1, string input2){
    //declare variables
    vector<int> pp_array(input1);
    int j=0;
    
    // subtract input2[i] by 48 to convert it to integer
    // Generate number by multiplying 10 and adding (int)(input2[i])
    for (int i=0; input2[i] != '\0'; i++){
        if (input2[i]==' ') j++;         //skip space
        else pp_array[j]=pp_array[j]*10+(input2[i]-48);
    }
    
    return pp_array;
}

/* **********************************************************************************************
  parse_relative_weights: function that parse relative weights from graded artifacts
                          returns vector<int> rw_array
* *********************************************************************************************** */
vector<int> parse_relative_weights(int input1, string input3){
    //declare variables
    vector<int> rw_array(input1);
    int j=0;
    
    //subtract input3[i] by 48 to convert it to integer
    //generate number by multiplying 10 and adding (int)(input3[i])
    for (int i=0; input3[i] != '\0'; i++){
        if (input3[i]==' ') j++;         //skip space
        else rw_array[j]=rw_array[j]*10+(input3[i]-48);
    }
    
    return rw_array;
}

/* **********************************************************************************************
 parse_student_info: function that parse student id, grade options & student names from students
                     returns vector<tuple<int, char, string>> si_tuple
* *********************************************************************************************** */
vector<tuple<int, char, string>> parse_student_info(string input4){
    //declare variables
    vector<tuple<int, char, string>> si_tuple;
    vector<int> sid_array(1);
    vector<char> gp_array;
    string sname_temp;
    int j=0;
    
    //read student id and put it into sid_array
    for (int i=0; input4[i] != '\0'; i++){
        if (input4[i]==' ') j++;                        //skip space
        if (input4[i]=='G' || input4[i]=='P') break;    //read until grade option
        sid_array[j]=sid_array[j]*10+(input4[i]-48);    //convert student id string into integer
    }
    
    //read starting from grade option
    for (int i=0; input4[i] != '\0'; i++){
        if (input4[i]=='G' || input4[i]=='P'){
            gp_array.push_back(input4[i]);
            for (int x=i+2; x<input4.size(); x++){
                sname_temp += input4[x];                //append the rest of student name into string
            }
        }
    }
    auto sid_count = sid_array.cbegin();
    auto gp_count = gp_array.cbegin();
    
    //put the student info into the tuple
    for (; sid_count != sid_array.end() && gp_count != gp_array.end(); ++sid_count, ++gp_count){
        si_tuple.push_back({*sid_count, *gp_count, sname_temp});
    }
    
    return si_tuple;
}

/* **********************************************************************************************
 parse_raw_scores: function that parse raw scores for each graded artifacts
                   returns vector<tuple<int,vector<int>>> rs_tuple
* *********************************************************************************************** */
vector<tuple<int,vector<int>>> parse_raw_scores(int input1, string input5){
    //declare variables
    vector<int> rs_array(input1+1);
    int sid;
    vector<tuple<int,vector<int>>> rs_tuple;
    int j=0;
    
    //subtract input5[i] by 48 to convert it to integer
    //generate number by multiplying 10 and adding (int)(input5[i])
    for (int i=0; input5[i] != '\0'; i++){
        if (input5[i]==' ') j++;         //skip space
        else rs_array[j]=rs_array[j]*10+(input5[i]-48);
    }
    
    //assign the first value(student id) to integer sid
    for (auto i = rs_array.begin(); i != rs_array.begin()+1; ++i) sid=*i;
    
    //erase the first value(student id) from rs_array
    rs_array.erase(rs_array.begin());
    
    //put the student id & raw scores into the tuple
    rs_tuple.push_back({sid, rs_array});
    
    return rs_tuple;
}

/* **********************************************************************************************
 parse_cutpoint_sets: function that parse cutpoint sets
                      returns vector<tuple<char, double>> cp_tuple
* *********************************************************************************************** */
vector<tuple<char, double>> parse_cutpoint_sets(string input6){
    //define variables
    vector<tuple<char, double>> cp_tuple;
    double num;
    istringstream iss(input6);
    vector<string> cp_array{istream_iterator<string>{iss}, istream_iterator<string>{}};
    
    //convert string of decimals(input6) to double
    for (int i=0; i < cp_array.size(); i++) {
        num = stod(cp_array[i]);
    }
    
    //assign each cutpoint to each grade(A, B, C, D) respectively
    cp_tuple.push_back({'A', stod(*(cp_array.begin()))});
    cp_tuple.push_back({'B', stod(*(cp_array.begin()+1))});
    cp_tuple.push_back({'C', stod(*(cp_array.begin()+2))});
    cp_tuple.push_back({'D', stod(*(cp_array.begin()+3))});
    
    return cp_tuple;
}

/* **********************************************************************************************
 calculate_total_points: function that calculate total scores for all students
                         returns vector<tuple<int, double>> total_score
* *********************************************************************************************** */
vector<tuple<int, double>> calculate_total_points(vector<int> result1, vector<int> result2, vector<tuple<int,vector<int>>> result3){
    //declare variables
    double total_score=0;
    vector<tuple<int, double>> ts_tuple;
    
    for(const auto &i : result3){
        auto k = get<1>(i).begin();
        auto pp_count = result1.cbegin();
        auto rw_count = result2.cbegin();
        
        for (; k != get<1>(i).end() && pp_count != result1.end() && rw_count != result2.end(); ++k, ++pp_count, ++rw_count){
            total_score += ((double)(*k) / (double)(*pp_count)) * (double)(*rw_count);
        }
        ts_tuple.push_back({get<0>(i), total_score});
        total_score=0;
    }
        
    return ts_tuple;
}

/* **********************************************************************************************
  print_student_roster: function that print total scores & student info for all students
                        returns vector<tuple<int, string, double, char>> sr_tuple
* *********************************************************************************************** */
vector<tuple<int, string, double, char>> print_student_roster(vector<tuple<int, double>> result4, vector<tuple<int, char, string>> result5){
    //print header
    cout << "TOTAL SCORES" << endl;
    
    //sort the total score tuple(result4) in ascending order based on the first element(sid)
    sort(result4.begin(), result4.end());
    
    //sort the student info tuple(result5) in ascending order based on the first element(sid)
    sort(result5.begin(), result5.end());
    
    //declare variables
    auto pp_count = result4.cbegin();
    auto rw_count = result5.cbegin();
    vector<tuple<int, string, double, char>> sr_tuple;
    
    //store the total scores & student info into tuple
    for(;pp_count != result4.end() && rw_count != result5.end(); ++pp_count, ++rw_count){
        if (get<0>(*pp_count)==get<0>(*rw_count)){
            sr_tuple.push_back({get<0>(*pp_count), get<2>(*rw_count), get<1>(*pp_count), get<1>(*rw_count)});
        }
    }
    //print info from tuple
    for(const auto &i : sr_tuple)
        cout<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<<endl;
    
    return sr_tuple;
}
/* **********************************************************************************************
  print_cutpoint_sets: function that print cutpoint sets & student info for all students
                       returns nothing
* *********************************************************************************************** */
void print_cutpoint_sets (int set, vector<tuple<int, string, double, char>> result6, vector<tuple<char, double>> result7){
    //print header
    cout << "CUTPOINT SET " << set << endl;
    
    for (auto i = result6.cbegin(); i != result6.end(); ++i){
        for (auto k = result7.cbegin(); k != result7.end(); ++k){
            
            //grade option
            if (get<3>(*i) == 'G'){
                if (get<2>(*i) >= get<1>(*k)){
                    cout << get<0>(*i) << " " << get<1>(*i) << " " << get<0>(*k) << endl;
                    break;
                }
                if (get<2>(*i) < get<1>(*k) && get<0>(*k) == 'D')
                    cout << get<0>(*i) << " " << get<1>(*i) << " F" << endl;
            }
            //pass no-pass option
            else if (get<3>(*i) == 'P'){
                if (get<2>(*i) >= get<1>(*k)){
                    cout << get<0>(*i) << " " << get<1>(*i) << " P" << endl;
                    break;
                }
                if (get<2>(*i) < get<1>(*k) && get<0>(*k) == 'D')
                    cout << get<0>(*i) << " " << get<1>(*i) << " NP" << endl;
            }
            //error handling
            else
                cout << "grade option input error" << endl;
        }
    }
}
/* **********************************************************************************************
  main: main function
* *********************************************************************************************** */
int main(int argc, const char * argv[]) {
    //declare variables
    vector<string> input_array;
    vector<int> pp_array;
    vector<int> rw_array;
    int ga_count, se_count, si_count, rs_count, cp_count;
    
    //call read_input function
    input_array=read_input();
    
    //convert number of possible points into integer
    ga_count = stoi(input_array[0]);
    
    //call parse_possible_points function
    pp_array=parse_possible_points(ga_count, input_array[1]);
    
    //call parse_relative_weights function
    rw_array=parse_relative_weights(ga_count, input_array[2]);
    
    //convert number of students enrolled into integer
    se_count = stoi(input_array[3]);
    vector<tuple<int, char, string>> si_array;
    vector<tuple<int, char, string>> sa_array;
    si_count = 4;
    
    //call parse_student_info function recursively based on number of students enrolled
    for (int i=0; i<se_count; i++){
        si_array = parse_student_info(input_array[si_count]);
        sa_array.insert(sa_array.end(), si_array.begin(), si_array.end());
        si_count++;
    }
    
    //convert number of possible points into integer
    rs_count = stoi(input_array[si_count]);
    vector<tuple<int,vector<int>>> rs_array;
    vector<tuple<int,vector<int>>> rt_array;
    
    //call parse_raw_scores function recursively based on number of students of which raw scores listed
    for (int i=0; i<rs_count; i++){
        rs_array = parse_raw_scores(ga_count, input_array[si_count+1]);
        rt_array.insert(rt_array.end(), rs_array.begin(), rs_array.end());
        si_count++;
    }
    
    //call calculate_total_points function
    vector<tuple<int, double>> ts_array;
    ts_array=calculate_total_points(pp_array, rw_array, rt_array);
    
    //call print_student_roster function
    vector<tuple<int, string, double, char>> sr_array;
    sr_array=print_student_roster(ts_array, sa_array);
    
    //convert number of cutpoint sets into integer
    cp_count = stoi(input_array[si_count+1]);
    vector<tuple<char, double>> cp_array;
    vector<tuple<char, double>> cs_array;
    
    for (int i=0; i<cp_count; i++){
        cp_array = parse_cutpoint_sets(input_array[si_count+2]);
        print_cutpoint_sets(i+1, sr_array, cp_array);
        cs_array.insert(cs_array.end(), cp_array.begin(), cp_array.end());
        si_count++;
    }
    return 0;
}
