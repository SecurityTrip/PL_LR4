#include <iostream>
#include <string>
#include <vector>

class Time{
private:
    unsigned short int hour, minute, second;
public:
    Time(){
        hour=0;
        minute=0;
        second=0;
    }
    Time(int &h){
        if(h >= 0 && h <= 24) {
            hour = h;
            minute = 0;
            second = 0;
        }
    }
    Time(int &h, int &m){
        if((h >= 0 && h <= 24) && (m>=0 && m <= 60)) {
            hour = h;
            minute = m;
            second = 0;
        }
    }
    Time(int &h, int &m, int &s){
        if((h >= 0 && h <= 24) && (m>=0 && m <= 60) && (s>=0 && s <= 60)) {
            hour = h;
            minute = m;
            second = s;
        }
    }
    Time(const Time &T){

    }
    ~Time() = default;


    int time_to_seconds(){
        return this->second + this->minute*60 + this->hour*60*60;
    }


    friend std::ostream& operator<< (std::ostream&, const Time&);
    friend std::istream& operator>> (std::istream&, Time&);

};

std::vector<int> split (const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    std::vector<int> tmp;
    for(auto & re : res){
        tmp.push_back(stoi(re));
    }
    return tmp;
}

std::ostream& operator<< (std::ostream& out, const Time &T) {
    if(T.hour<10) out << "0" << T.hour << ":";
    else out << T.hour << ":";

    if(T.minute<10) out << "0" << T.minute << ":";
    else out << T.minute << ":";

    if(T.second<10) out << "0" << T.second << ":";
    else out << T.second;

    return out;
}

std::istream& operator>>(std::istream & in, Time & T) {
    std::string in_str;
    in >> in_str;

    std::string delimiter = ":";
    std::vector<int> tmp = split(in_str,delimiter);

    T = Time(tmp[0],tmp[1],tmp[2]);

}

Time operator + (Time& T1, Time& T2){
    int s,m,h;

}


int main() {

    Time a;
    int z = 9, x = 34, c = 57,v = 68;
    Time q,w,e,r;
    q = Time(z);
    w = Time(z,x);
    e = Time(z,x,c);
    r = Time(z,x,v);

    std::cout<<e;
    int zxc;
    std::cout << std::endl << e.time_to_seconds();

    Time test;
    std::string aa = "10:24:00";
    std::cout << std::endl;
    std::cin >> test;

    std::cout << test;

    return 0;
}
